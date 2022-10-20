#include "enhance_menu.h"
#include <QDebug>
#include <QMessageBox>
cv::Mat EnhanceMenu::image;
EnhanceMenu::EnhanceMenu(const QString &title,QWidget *parent):
                        QMenu(title,parent)
{
    rgb2Gray_ = new QAction(tr("gray"),this);
    this->addAction(rgb2Gray_);
    //connect(open_Image_,SIGNAL(triggered()),this,SLOT(ImreadImage()));
    connect(rgb2Gray_,SIGNAL(triggered()),this,SLOT(Rgb2Gray()));
    contrast_spread_ = new QAction("contrast spreda",this);
    this->addAction(contrast_spread_);
    connect(contrast_spread_,SIGNAL(triggered()),this,SLOT(ContrastSpread()));

    histogram_ = new QAction(tr("hist"),this);
    this->addAction(histogram_);
    connect(histogram_,SIGNAL(triggered()),this,SLOT(HistBarStastics()));

    hist_bar_ = new HistBar;
    connect(this,SIGNAL(HistStatistics(QVector<double>)),hist_bar_,SLOT(PlotBar(QVector<double>)));

    histogram_equalisation_ = new QAction("hist eq",this);
    this->addAction(histogram_equalisation_);
    connect(histogram_equalisation_,SIGNAL(triggered()),this,SLOT(HistogramEqualisation()));
}

void EnhanceMenu::Rgb2Gray()
{
    //enhance_image = image;
    /*
    Description: Image grayscaling
    Note：Y = 0.2162*R+0.7152*G+0.0722*B
    */
    if(image.empty())
    {
        QMessageBox mesg;
        mesg.warning(this,"Warning","Please input a image!");
        return;
    }
    int width = image.cols;  // get the width of the image
    int height = image.rows; // get the height of the image

    enhance_image_ = cv::Mat::zeros(height, width, CV_8UC1);  // create a zero image of as same as the original image to prepare output

    for (int y = 0; y < height; y++) {     // loop through each pixel point
        for(int x = 0; x < width; x++){
            enhance_image_.at<uchar>(y, x) = 0.2162 * image.at<cv::Vec3b>(y, x)[2]
                + 0.7152 * image.at<cv::Vec3b>(y, x)[1]
                + 0.0722 * image.at<cv::Vec3b>(y, x)[0];
        }
    }
    emit ChangeRightImage(enhance_image_);
}

void EnhanceMenu::ContrastSpread()
{
    enhance_image_.release();
    contrast_dialog_ = new ContrastDialog;
    //contrast_dialog_->show();
    if(contrast_dialog_->exec() == QDialog::Accepted)
    {
        CONTRASTBALUE_S value = contrast_dialog_->contrast_value_;
//        cv::Mat image = cv::imread("Lena.bmp");
//        cv::Mat grayImage(image.size(), CV_8UC1);
//        cv::Mat dstImage(grayImage.size(), CV_8UC1);
//        cv::cvtColor(image, grayImage, CV_BGR2GRAY);

        cv::Mat gray_image = Rgb2GrayC(image);
        enhance_image_ = cv::Mat::zeros(gray_image.size(), CV_8UC1);


        float fa = value.fa, fb = value.fb;
        float ga = value.ga, gb = value.gb;
        qDebug()<<value.ga<<value.gb;
        qDebug()<<fa<<fb<<ga<<gb;

        for (int row = 0; row < gray_image.rows; row++)
        {
            uchar *currentData = gray_image.ptr<uchar>(row);
            for (int col = 0; col < gray_image.cols; col++)
            {
                if (*(currentData + col) >= 0 && *(currentData + col) < fa)
                {
                    enhance_image_.at<uchar>(row, col) = uchar(ga / fa * (*(currentData + col)));
                }
                if (*(currentData + col) >= fa && *(currentData + col) < fb)
                {
                    enhance_image_.at<uchar>(row, col) = uchar((gb-ga) / (fb-fa) * (*(currentData + col)-fa)+ga);
                }
                if (*(currentData + col) >= fb && *(currentData + col) < 255)
                {
                    enhance_image_.at<uchar>(row, col) = uchar((255-gb) / (255-fb) * (*(currentData + col)-fb)+gb);
                }
                if(*(currentData + col)==255)
                {
                    enhance_image_.at<uchar>(row, col)=uchar(255);
                }
            }
        }

    }
    emit ChangeRightImage(enhance_image_);
}

void EnhanceMenu::HistBarStastics()
{



    QVector<double> histogram(256,0);
    cv::Mat gray_image = Rgb2GrayC(image);
    int rows = image.rows;
    int cols = image.cols;
    for(int r=0;r<rows;r++)
    {
        for (int c = 0; c < cols; c++)
        {
            int index = int(gray_image.at<uchar>(r, c));
            histogram[index] +=1;
        }
    }
    hist_bar_->hist_ = histogram;

    emit HistStatistics(histogram);
    qDebug()<<"111";
    hist_bar_->show();
}

void EnhanceMenu::HistogramEqualisation()
{
    enhance_image_.release();
    int grayHist[256] = {0};
    double gray_prob[256] = { 0 };
    double gray_distribution[256] = { 0 };
    int outHist[256] = { 0 };
    cv::Mat gray_image = Rgb2GrayC(image);

        //cv::cvtColor(image, image, COLOR_BGR2GRAY);
        enhance_image_ = gray_image.clone();
        int col = gray_image.cols;
        int row = gray_image.rows;
        int total = col * row;
        for (int i = 0; i < row; i++)
        {
            uchar* data = gray_image.ptr<uchar>(i);
            for (int j = 0; j < col; j++)
            {
                grayHist[data[j]]++;
            }
        }
        for (int i = 0; i < 256; i++)
        {
            gray_prob[i] =(double(grayHist[i]) / total);
        }
        gray_distribution[0] = gray_prob[0];
        for (int i = 0; i < 255; i++)
        {
            gray_distribution[i + 1] = gray_distribution[i] + gray_prob[i + 1];
        }
        for (int i = 0; i < 256; i++)
        {
            outHist[i] = uchar(255 * gray_distribution[i] + 0.5);
        }
        for (int i = 0; i < enhance_image_.rows; i++)
        {
            uchar* p = enhance_image_.ptr<uchar>(i);
            for (int j = 0; j < enhance_image_.cols; j++)
            {
                p[j] = outHist[p[j]];
            }
        }
        //return output;
        emit ChangeRightImage(enhance_image_);
}
