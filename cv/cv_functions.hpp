#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

cv::Mat gray_converter(cv::Mat img);
cv::Mat binary_converter(cv::Mat img);
cv::Mat canny_converter(cv::Mat img);
cv::Mat gray_equalizer(cv::Mat img);


cv::Mat img_operator(cv::Mat img, int operator_type, void* other_data=NULL);