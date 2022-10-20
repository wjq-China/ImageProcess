#include "filter_menu.h"
#include "common_def.h"
#include <QDebug>
cv::Mat FilterMenu::image;
FilterMenu::FilterMenu(const QString &title,QWidget *parent):
                        QMenu(title,parent)

{
    knn_filter_ = new QAction("KNN",this);
    this->addAction(knn_filter_);
    connect(knn_filter_,SIGNAL(triggered()),this,SLOT(KnnFilter()));

    mean_filter_ = new QAction("mean",this);
    this->addAction(mean_filter_);
    connect(mean_filter_,SIGNAL(triggered()),this,SLOT(MeanFilter()));

    median_filter_ = new QAction("median",this);
    this->addAction(median_filter_);
    connect(median_filter_,SIGNAL(triggered()),this,SLOT(MedianFilter()));

    gauss_filter_ = new QAction("gauss",this);
    this->addAction(gauss_filter_);
    connect(gauss_filter_,SIGNAL(triggered()),this,SLOT(GaussFilter()));

}

void FilterMenu::MeanFilter()
{
    filter_mat_.release();
        cv::Mat gray_image =Rgb2GrayC(image);
        filter_mat_ = gray_image.clone();
        int row = image.rows;
        int col = image.cols;
        int k = 3;
        for (int i = ((k - 1) / 2); i < row -( (k - 1) / 2); i++)
        {
            for (int j = ((k - 1) / 2); j <col- ((k - 1) / 2); j++)
            {
                int sum = 0;
                for (int m = i - ((k - 1) / 2); m <= ((k - 1) / 2 )+ i; m++)
                {
                    for (int n = j - ((k - 1) / 2); n <= ((k - 1) / 2 )+ j; n++)
                    {
                        sum += gray_image.at<uchar>(m, n);
                    }
                }
                filter_mat_.at<uchar>(i, j) = uchar(sum /( k*k));
            }
        }
        emit ChangeRightImage(filter_mat_);
}

void FilterMenu::MedianFilter()
{
    filter_mat_.release();
        cv::Mat gray_image =Rgb2GrayC(image);
        filter_mat_ = gray_image.clone();
        int row = image.rows;
        int col = image.cols;

        std::vector<uchar> index;
        int k=3;
        for (int i = ((k - 1) / 2); i < row - ((k - 1) / 2); i++)
        {
            for (int j = ((k - 1) / 2); j < col - ((k - 1) / 2); j++)
            {
                //int sum = 0;
                for (int m = i - ((k - 1) / 2); m <= ((k - 1) / 2) + i; m++)
                {
                    for (int n = j - ((k - 1) / 2); n <= ((k - 1) / 2) + j; n++)
                    {
                        index.push_back(gray_image.at<uchar>(m, n));
                    }
                }
                index=bubble_sort(index);
                filter_mat_.at<uchar>(i, j) = index[index.size() / 2];
                index.clear();
            }
        }
        emit ChangeRightImage(filter_mat_);
}

void FilterMenu::KnnFilter()
{
    filter_mat_.release();
    cv::Mat src =Rgb2GrayC(image);
    filter_mat_ = src.clone();
    int N = 3, K = 5;

    for (int row = 1; row < src.rows - 1; ++row)
    {
        for (int col = 1; col < src.cols - 1; ++col)
        {
            double v = 0.0;
            std::vector<struct subValue>c;
            struct subValue b;
            for (int dy = -1; dy < N - 1; ++dy)
            {
                for (int dx = -1; dx < N - 1; ++dx)
                {
                    if (!(dx == 0 && dy == 0))
                    {
                        b.value = abs(src.at<uchar>(row + dy, col + dx) - src.at<uchar>(row, col));
                        b.f.x = dx;
                        b.f.y = dy;
                        c.push_back(b);
                    }
                }
            }
            //进行排序
            std::vector<struct subValue> sortValue = sortStruct(c);
           // v = src.at<uchar>(row + sortValue[2].f.y, col + sortValue[2].f.x);
            // dst.at<uchar>(row, col) = uchar(v);
            for (int i = 0; i < K;++i)
            {
                v += src.at<uchar>(row + sortValue[i].f.y, col + sortValue[i].f.x);
            }
            filter_mat_.at<uchar>(row, col) = uchar(v/K);

        }
    }
    emit ChangeRightImage(filter_mat_);
}

void FilterMenu::GaussFilter()
{
    filter_mat_.release();
    gauss_dialog_ = new GaussDialog;
    gauss_dialog_->HideRotationLabel();
    if(gauss_dialog_->exec() == QDialog::Accepted)
    {
        int k = gauss_dialog_->k;
        int a = k / 2;
        qDebug()<<a;
        double sigma = 0.5;
        cv::Mat imga =Rgb2GrayC(image);
        cv::Mat imgb = imga.clone();
        int kz = 0;
        filter_mat_ = imga.clone();
        //cv::Mat filter_mat_(imga.size(),CV_8UC1);
        cv::Mat gauss_k(k, k,CV_8U);
        for (int i = -a; i <= k - a - 1; i++)
        {
            for (int j = -a; j <= k - a - 1; j++)
            {
                gauss_k.at<uchar>(i + a, j + a) = int(exp((pow(i, 2) + pow(j, 2)) / (2 * pow(sigma, 2))));
                kz = kz + gauss_k.at<uchar>(i + a, j + a);
            }
        }
        int w = imga.cols;
        int h = imga.rows;
        for (int i1 = a; i1 <= h - a - 1; i1++)
        {
            for (int j1 = a; j1 <= w - a - 1; j1++)
            {
                int t = 0;
                for (int i2 = -a; i2 <= k - a - 1; i2++)
                {
                    for (int j2 = -a; j2 <= k - a - 1; j2++)
                    {
                        t = t + imga.at<uchar>(i1 + i2, j1 + j2) * gauss_k.at<uchar>(i2 + a, j2 + a);
                    }
                }
                filter_mat_.at<uchar>(i1, j1) = uchar(t / kz);
            }
        }

    }
    emit ChangeRightImage(filter_mat_);
}
