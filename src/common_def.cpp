#include"common_def.h"
cv::Mat Rgb2GrayC(cv::Mat image)
{
    //enhance_image = image;
    /*
    Description: Image grayscaling
    Note：Y = 0.2162*R+0.7152*G+0.0722*B
    */
    int width = image.cols;  // get the width of the image
    int height = image.rows; // get the height of the image

    cv::Mat dst = cv::Mat::zeros(height, width, CV_8UC1);  // create a zero image of as same as the original image to prepare output

    for (int y = 0; y < height; y++) {     // loop through each pixel point
        for(int x = 0; x < width; x++){
            dst.at<uchar>(y, x) = 0.2162 * image.at<cv::Vec3b>(y, x)[2]
                + 0.7152 * image.at<cv::Vec3b>(y, x)[1]
                + 0.0722 * image.at<cv::Vec3b>(y, x)[0];
        }
    }
    return dst;
}

std::vector<uchar> bubble_sort(std::vector<uchar> arr)
{
    int len = arr.size();
    for (int i = 1; i < len; i++)
    {
        for (int j = 0; j < len - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp;
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }

    }
    return arr;
}

std::vector<struct subValue> sortStruct(std::vector<struct subValue>a)
{
    struct subValue b;
    for (int i = 0; i < a.size() - 1; i++)
    {
        for (int j = 0; j < a.size() - 1 - i; j++)
        {
            if (a[j].value > a[j + 1].value)
            {
                b = a[j];
                a[j] = a[j + 1];
                a[j + 1] = b;
            }
        }
    }
    return a;
}

int FindMaximumElement(const std::vector<int> & vec)
{
    int size = vec.size();
    int Number = vec[0];
    int j = 0;
    for (int i = 1; i < size; i++)
    {
        if (vec[i] > Number) {
            Number = vec[i];
            j = i;
        }
    }
    return j;
}
