#include "cv_functions.hpp"

cv::Mat gray_converter(cv::Mat img){
    cv::Mat gray_img;
    cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    cv::cvtColor(gray_img, gray_img, cv::COLOR_GRAY2BGR);
    return gray_img;
}