#include <opencv2/imgproc/imgproc.hpp>

cv::Mat gray_converter(cv::Mat img);
cv::Mat binary_converter(cv::Mat img);
cv::Mat canny_converter(cv::Mat img);


cv::Mat img_operator(cv::Mat img, int operator_type, void* other_data=NULL);