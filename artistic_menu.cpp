#include "artistic_menu.h"
#include "common_def.h"
cv::Mat ArtisticMenu::image;
ArtisticMenu::ArtisticMenu(const QString &title,QWidget *parent)
                              :QMenu(title,parent)
{
    white_balance_ = new QAction("while balance",this);
    this->addAction(white_balance_);
    connect(white_balance_,SIGNAL(triggered()),this,SLOT(WhiteBalance()));

    color_offset_ = new QAction("color offset",this);
    this->addAction(color_offset_);
    connect(color_offset_,SIGNAL(triggered()),this,SLOT(ColorOffset()));

    rotate_ = new QAction("rotation",this);
    this->addAction(rotate_);
    connect(rotate_,SIGNAL(triggered()),this,SLOT(RotationImage()));
}

void ArtisticMenu::RotationImage()
{
    artistic_image_.release();
    angle_dialog = new GaussDialog;
    angle_dialog->HideGaussLabel();
    if(angle_dialog->exec()==QDialog::Accepted)
    {
           int k = angle_dialog->k;
        cv::Mat gray_img = Rgb2GrayC(image);

         float theta = k;
            float curvature = theta / 180 * CV_PI;

            cv::Mat x = cv::Mat::zeros(gray_img.size(), CV_32FC1);
            cv::Mat y = cv::Mat::zeros(gray_img.size(), CV_32FC1);

            for (int row = 0; row < gray_img.rows; row++)
            {
                for (int col = 0; col < gray_img.cols; col++)
                {

                    x.at<float>(row, col) = round(row * cos(curvature) - col * sin(curvature));
                    y.at<float>(row, col) = round(row * sin(curvature) + col * cos(curvature));
                }
            }
            double x_min, x_max;
            double y_min, y_max;

            cv::minMaxLoc(x, &x_min, &x_max);
            cv::minMaxLoc(y, &y_min, &y_max);
            x = x - x_min;
            y = y - y_min;

            cv::minMaxLoc(x, &x_min, &x_max);
            cv::minMaxLoc(y, &y_min, &y_max);

            artistic_image_ = cv::Mat::zeros(x_max+1, y_max+1, CV_8UC1);
            cv::Mat flag = cv::Mat::zeros(x_max + 1, y_max + 1, CV_8UC1);
            for (int row = 0; row < gray_img.rows; row++)
            {
                for (int col = 0; col < gray_img.cols; col++)
                {
                    int i = (int)x.at<float>(row, col);
                    int j = (int)y.at<float>(row, col);
                    artistic_image_.at<uchar>(i, j) = gray_img.at<uchar>(row, col);
                    flag.at<uchar>(i, j) = 1;
                }
            }
            //均值插值法
            for (int row = 1; row < artistic_image_.rows-1; row++)
               {
                   for (int col = 1; col < artistic_image_.cols-1; col++)
                   {
                       if (flag.at<uchar>(row, col - 1) == 1 && flag.at<uchar>(row, col + 1) == 1 &&
                           flag.at<uchar>(row - 1, col) == 1 && flag.at<uchar>(row + 1, col) == 1
                           && flag.at<uchar>(row, col) == 0)
                       {
                           artistic_image_.at<uchar>(row, col) = uchar((artistic_image_.at<uchar>(row, col - 1) + artistic_image_.at<uchar>(row, col + 1) +
                               artistic_image_.at<uchar>(row - 1, col) + artistic_image_.at<uchar>(row + 1, col)) / 4);
                       }
                   }
               }
    }
    emit ChangeRightImage(artistic_image_);
}

void ArtisticMenu::ColorOffset()
{
    artistic_image_.release();
        cv::Mat r_mat(image.size(), CV_8UC1);
        cv::Mat g_mat(image.size(), CV_8UC1);
        cv::Mat b_mat(image.size(), CV_8UC1);

        cv::Mat error_r(image.size(), CV_32SC1);
        cv::Mat error_g(image.size(), CV_32SC1);
        cv::Mat error_b(image.size(), CV_32SC1);



        for (int row = 0; row < image.rows; row++)
        {
            cv::Vec3b *currentData = image.ptr<cv::Vec3b>(row);
            for (int col = 0; col < image.cols; col++)
            {
                r_mat.at<uchar>(row, col) = (*(currentData + col))[2];
                g_mat.at<uchar>(row, col) = (*(currentData + col))[1];
                b_mat.at<uchar>(row, col) = (*(currentData + col))[0];
                error_r.at<int>(row, col) = (*(currentData + col))[2] - (*(currentData + col))[0] + (*(currentData + col))[2] - (*(currentData + col))[1];
                error_g.at<int>(row, col) = (*(currentData + col))[1] - (*(currentData + col))[0] + (*(currentData + col))[1] - (*(currentData + col))[2];
                error_b.at<int>(row, col) = (*(currentData + col))[0] - (*(currentData + col))[2] + (*(currentData + col))[0] - (*(currentData + col))[1];
            }
        }
        double error_r_max, error_g_max, error_b_max;
        double error_r_min, error_g_min, error_b_min;

        cv::minMaxLoc(error_r, &error_r_min, &error_r_max);
        cv::minMaxLoc(error_g, &error_g_min, &error_g_max);
        cv::minMaxLoc(error_b, &error_b_min, &error_b_max);

        //cout << error_r_max;

        cv::Mat rgb_average = cv::Mat::zeros(3, 3, CV_32FC1);

        int num[3] = { 0 };
        for (int row = 0; row < error_r.rows; row++)
        {
            int *error_r_data = error_r.ptr<int>(row);
            int *error_g_data = error_g.ptr<int>(row);
            int *error_b_data = error_b.ptr<int>(row);

            uchar *r_data = r_mat.ptr<uchar>(row);
            uchar *g_data = g_mat.ptr<uchar>(row);
            uchar *b_data = b_mat.ptr<uchar>(row);
            for (int col = 0; col< error_r.cols; col++)
            {
                if ((*(error_r_data + col)) == int(error_r_max))
                {
                    num[0] += 1;
                    rgb_average.at<float>(0, 0) = rgb_average.at<float>(0, 0) + (*(r_data + col));
                    rgb_average.at<float>(1, 0) = rgb_average.at<float>(1, 0) + (*(g_data + col));
                    rgb_average.at<float>(2, 0) = rgb_average.at<float>(2, 0) + (*(b_data + col));
                }

                if ((*(error_g_data + col)) == int(error_g_max))
                {
                    num[1] += 1;
                    rgb_average.at<float>(0, 1) = rgb_average.at<float>(0, 1) + (*(r_data + col));
                    rgb_average.at<float>(1, 1) = rgb_average.at<float>(1, 1) + (*(g_data + col));
                    rgb_average.at<float>(2, 1) = rgb_average.at<float>(2, 1) + (*(b_data + col));
                }
                if ((*(error_b_data + col)) == int(error_b_max))
                {
                    num[2] += 1;
                    rgb_average.at<float>(0, 2) = rgb_average.at<float>(0, 2) + (*(r_data + col));
                    rgb_average.at<float>(1, 2) = rgb_average.at<float>(1, 2) + (*(g_data + col));
                    rgb_average.at<float>(2, 2) = rgb_average.at<float>(2, 2) + (*(b_data + col));
                }
            }
        }
        rgb_average.at<float>(0, 0) = rgb_average.at<float>(0, 0) / num[0];
        rgb_average.at<float>(1, 0) = rgb_average.at<float>(1, 0) / num[0];
        rgb_average.at<float>(2, 0) = rgb_average.at<float>(2, 0) / num[0];
        rgb_average.at<float>(0, 1) = rgb_average.at<float>(0, 1) / num[1];
        rgb_average.at<float>(1, 1) = rgb_average.at<float>(1, 1) / num[1];
        rgb_average.at<float>(2, 1) = rgb_average.at<float>(2, 1) / num[1];
        rgb_average.at<float>(0, 2) = rgb_average.at<float>(0, 2) / num[2];
        rgb_average.at<float>(1, 2) = rgb_average.at<float>(1, 2) / num[2];
        rgb_average.at<float>(2, 2) = rgb_average.at<float>(2, 2) / num[2];

        //cout << rgb_average.at<float>(2, 1) << endl;
        cv::Mat rgb_average_inv;

        cv::invert(rgb_average, rgb_average_inv);

        cv::Mat rgb_average_a = (cv::Mat_<float>(3, 3) <<0.299, 0, 0, 0, 0.587, 0, 0, 0, 0.114);

        //cv::Mat dst(image.size(),CV_32FC3);
        //cv::Mat dst(image.size(),CV_8UC3);
        artistic_image_ = cv::Mat(image.size(),CV_32FC3);
        for (int row = 0; row < image.rows; row++)
        {
            //cv::Vec3f * data = artistic_image_.ptr<cv::Vec3f>(row);
            for (int col = 0; col < image.cols; col++)
            {

                cv::Mat y = (cv::Mat_<float>(3, 1) << float(image.at<cv::Vec3b>(row, col)[2]),
                    float(image.at<cv::Vec3b>(row, col)[1]),
                    float(image.at<cv::Vec3b>(row, col)[0]));
                cv::Mat a = (rgb_average_a * rgb_average_inv)*y;
                //dst.at<cv::Vec3f>(row, col)[2] = a.at<float>(0,0);
                //dst.at<cv::Vec3f>(row, col)[1] = a.at<float>(1,0);
                //dst.at<cv::Vec3f>(row, col)[0] = a.at<float>(2,0);
                artistic_image_.at<cv::Vec3f>(row, col)[2] = 255*a.at<float>(0, 0);
                artistic_image_.at<cv::Vec3f>(row, col)[1] = 255*a.at<float>(1, 0);
                artistic_image_.at<cv::Vec3f>(row, col)[0] = 255*a.at<float>(2, 0);
            }
        }
        //cv::normalize(dst, dst, 0, 255);
        artistic_image_.convertTo(artistic_image_, CV_8UC3);
//        Mat dst_r_mat(image.size(),CV_8UC1);
//        for (int i = 0; i < image.rows; i++)
//        {
//            for (int j = 0; j < image.cols; j++)
//            {
//                dst_r_mat.at<uchar>(i, j) = dst.at<cv::Vec3b>(i, j)[2];
//            }
////        }
//        imshow("input", image);
//        imshow("output", dst);
//        cv::waitKey(0);
//        return 0;
        emit ChangeRightImage(artistic_image_);
}

void ArtisticMenu::WhiteBalance()
{
    artistic_image_.release();
        int width1 = image.cols;
        int height1 = image.rows;
        cv::Mat matRgb1 = cv::Mat::zeros(image.size(), CV_8UC1);
        int x, y; //
        float sum_Y = 0, avg_Y = 0, Y = 0, Y_MAX = 0;
        for (y = 0; y < height1; y++)
            for (x = 0; x < width1; x++)
            {
                float B = image.at<cv::Vec3b>(y, x)[0];
                float G = image.at<cv::Vec3b>(y, x)[1];
                float R = image.at<cv::Vec3b>(y, x)[2];
                Y = 0.299 * R + 0.587 * G + 0.114 * B;
                matRgb1.at<uchar>(y, x) = Y;
                sum_Y = sum_Y + Y;
                if (Y > Y_MAX)
                    Y_MAX = Y;
            }
        avg_Y = sum_Y / (height1 * width1);

        int k = 0;
        float avg_R = 0, avg_G = 0, avg_B = 0;;
        float judge_Y = 0.95 * Y_MAX;
        for (y = 0; y < height1; y++)
        {
            for (x = 0; x < width1; x++)
            {
                if (matRgb1.at<uchar>(y, x) < judge_Y || matRgb1.at<uchar>(y, x) == judge_Y)
                {
                    avg_B = avg_B + image.at<cv::Vec3b>(y, x)[0];
                    avg_G = avg_G + image.at<cv::Vec3b>(y, x)[1];
                    avg_R = avg_R + image.at<cv::Vec3b>(y, x)[2];
                    k++;
                }
            }
        }
        avg_B = avg_B / k;
        avg_G = avg_G / k;
        avg_R = avg_R / k;
        float k_r, k_g, k_b;
        k_r = avg_Y / avg_R;
        k_g = avg_Y / avg_G;
        k_b = avg_Y / avg_B;

        artistic_image_ = cv::Mat::zeros(image.size(),CV_8UC3);
        int B_1, G_1, R_1;
        for (y = 0; y < height1; y++)
        {
            for (x = 0; x < width1; x++)
            {
                B_1 = k_b * (image.at<cv::Vec3b>(y, x)[0]);
                G_1 = k_g * image.at<cv::Vec3b>(y, x)[1];
                R_1 = k_r * image.at<cv::Vec3b>(y, x)[2];
                if (B_1 > 255)
                    artistic_image_.at<cv::Vec3b>(y, x)[0] = 255;
                else
                    artistic_image_.at<cv::Vec3b>(y, x)[0] = B_1;
                if (G_1 > 255)
                    artistic_image_.at<cv::Vec3b>(y, x)[1] = 255;
                else
                    artistic_image_.at<cv::Vec3b>(y, x)[1] = G_1;
                if (R_1 > 255)
                    artistic_image_.at<cv::Vec3b>(y, x)[2] = 255;
                else
                    artistic_image_.at<cv::Vec3b>(y, x)[2] = R_1;
            }
        }
     emit ChangeRightImage(artistic_image_);
}
