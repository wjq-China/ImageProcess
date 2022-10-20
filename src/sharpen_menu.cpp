#include "sharpen_menu.h"
#include "common_def.h"
cv::Mat SharpenMenu::image;
SharpenMenu::SharpenMenu(const QString &title,QWidget *parent):
                         QMenu(title,parent)
{
    sobel_ = new QAction("sobel",this);
    this->addAction(sobel_);
    connect(sobel_,SIGNAL(triggered()),this,SLOT(SobelSharpen()));
    laplacian_ = new QAction("laplacian",this);
    this->addAction(laplacian_);
    connect(laplacian_,SIGNAL(triggered()),this,SLOT(LaplacianSharpen()));
    wallis_ = new QAction("wallis",this);
    this->addAction(wallis_);
    connect(wallis_,SIGNAL(triggered()),this,SLOT(WallisSharpen()));
}

void SharpenMenu::SobelSharpen()
{
    sharpen_mat_.release();
    int w = image.cols; //image 的列数
    int h = image.rows;

    cv::Mat gray_image = Rgb2GrayC(image);

    sharpen_mat_  = gray_image.clone();
    for (int i = 1; i <= w - 2; i++)
        for (int j = 1; j <= h - 2; j++)
           {
                int Dx = gray_image.at<uchar>(j + 1, i - 1) - gray_image.at<uchar>(j - 1, i - 1) + 2 * (gray_image.at<uchar>(j + 1, i) - gray_image.at<uchar>(j - 1, i)) + gray_image.at<uchar>(j + 1, i + 1) - gray_image.at<uchar>(j - 1, i + 1);
                int Dy = gray_image.at<uchar>(j - 1, i + 1) - gray_image.at<uchar>(j - 1, i - 1) + 2 * (gray_image.at<uchar>(j, i + 1) - gray_image.at<uchar>(j, i - 1)) + gray_image.at<uchar>(j + 1, i + 1) - gray_image.at<uchar>(j + 1, i - 1);
                sharpen_mat_.at<uchar>(j, i) = 255 - sqrt(pow(Dx, 2) + pow(Dy, 2));
           }
    emit ChangeRightImage(sharpen_mat_);
}

void SharpenMenu::LaplacianSharpen()
{
    sharpen_mat_.release();
    int w = image.cols; //image 的列数
    int h = image.rows;
    cv::Mat gray_image = Rgb2GrayC(image);
    sharpen_mat_  = gray_image.clone();
    for (int i = 1; i <= w - 2; i++)
    {
            for (int j = 1; j <= h - 2; j++)
            {
                int H = 4 * gray_image.at<uchar>(j, i)-gray_image.at<uchar>(j -1, i ) - gray_image.at<uchar>(j + 1, i) - gray_image.at<uchar>(j , i - 1) - gray_image.at<uchar>(j, i+1);
                sharpen_mat_.at<uchar>(j, i) = 255-sqrt(pow(H, 2));
            }
    }
    emit ChangeRightImage(sharpen_mat_);
}

void SharpenMenu::WallisSharpen()
{
    sharpen_mat_.release();
    int w = image.cols; //image 的列数
    int h = image.rows;
    cv::Mat gray_image = Rgb2GrayC(image);
    sharpen_mat_  = gray_image.clone();
    for (int i = 2; i <= w - 2; i++)
    {
            for (int j = 1; j <= h - 2; j++)
            {
                int W = gray_image.at<uchar>(j, i) - 0.25* gray_image.at<uchar>(j - 1, i) - 0.25 * gray_image.at<uchar>(j + 1, i) - 0.25 * gray_image.at<uchar>(j, i - 1) - 0.25 * gray_image.at<uchar>(j, i + 1);
                sharpen_mat_.at<uchar>(j, i) = 255 - sqrt(pow(W, 2));
            }
    }
    emit ChangeRightImage(sharpen_mat_);
}
