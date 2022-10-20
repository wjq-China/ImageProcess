#include "segment_menu.h"
#include "common_def.h"
#include <QMessageBox>

cv::Mat SegmentMenu::image;
SegmentMenu::SegmentMenu(const QString &title,QWidget *parent):
                        QMenu(title,parent)
{
    binary_ = new QAction("Binarisation",this);
    this->addAction(binary_);
    connect(binary_,SIGNAL(triggered()),this,SLOT(InputBinarisation()));
    ostu_ = new QAction("Ostu",this);
    this->addAction(ostu_);
    connect(ostu_,SIGNAL(triggered()),this,SLOT(OstuBinarization()));
}



void SegmentMenu::InputBinarisation()
{
    threshold_dialog_ = new ThresholdDialog;
    //threshold_dialog_->show();
    if(threshold_dialog_->exec() == QDialog::Accepted)
    {
        int thresh_value = threshold_dialog_->thresh_value_;
        segment_image_ = Binarisation(thresh_value);
//        int width = image.cols;
//        int height = image.rows;

//        cv::Mat gray_image = Rgb2GrayC(image);
//        segment_image_ = cv::Mat::zeros(height, width, CV_8UC1);

//        for (int y = 0; y < height; y++)
//        {
//            for (int x = 0; x < width; x++)
//            {
//                if (gray_image.at<uchar>(y, x) < thresh_value)
//                {
//                    segment_image_.at<uchar>(y, x) = 0;
//                }
//                else
//                {
//                    segment_image_.at<uchar>(y, x) = 255;
//                }
//            }
//        }
        emit ChangeRightImage(segment_image_);

    }
}

cv::Mat SegmentMenu::Binarisation(int thresh_value)
{

    int width = image.cols;
    int height = image.rows;

    cv::Mat gray_image = Rgb2GrayC(image);
    cv::Mat dst = cv::Mat::zeros(height, width, CV_8UC1);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (gray_image.at<uchar>(y, x) < thresh_value)
            {
                dst.at<uchar>(y, x) = 0;
            }
            else
            {
                dst.at<uchar>(y, x) = 255;
            }
        }
    }
    return dst;
}


void SegmentMenu::OstuBinarization()
{
    /*
    Description:
    Notes:方差越大，相关性越低，黑白越分明
    */
    segment_image_.release();
    cv::Mat grayScale_img = Rgb2GrayC(image);

    int width = grayScale_img.cols;
    int height = grayScale_img.rows;

    int t = 0; //uchar
    std::vector<int>g(256);
    for (int j = 0; j <= 255; j++) {
        double n0 = 0, n1 = 0;
        double w0 = 0, w1 = 0;
        double u0 = 0, u1 = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (grayScale_img.at<uchar>(y, x) < j) {
                    n0++;
                    u0 = u0 + grayScale_img.at<uchar>(y, x);
                }
                else {
                    n1++;
                    u1= u1 + grayScale_img.at<uchar>(y, x);
                }
            }
        }
        w0 = n0 / (height * width);
        w1 = n1 / (height * width);
        u0 /= n0;
        u1 /= n1;
        g[j] = w0 * w1 * pow((u0 - u1), 2);
    }
    t = FindMaximumElement(g);
    //cout << "阈值是：" << t << endl;
    segment_image_ = Binarisation(t);

    emit ChangeRightImage(segment_image_);
    QMessageBox::about(this, "Threshold", QString::number(t));

}
