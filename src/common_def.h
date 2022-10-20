#ifndef COMMON_DEF_H
#define COMMON_DEF_H

#include<opencv2/opencv.hpp>
struct CONTRASTBALUE_S
{
    int fa;
    int fb;
    int ga;
    int gb;
};
struct subValue
{
    int value;
    cv::Point f;
};
cv::Mat Rgb2GrayC(cv::Mat);

std::vector<uchar> bubble_sort(std::vector<uchar> arr);
std::vector<struct subValue> sortStruct(std::vector<struct subValue>a);
int FindMaximumElement(const std::vector<int> & vec);
#endif // COMMON_DEF_H
