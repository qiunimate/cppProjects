#include "cv_functions.hpp"
#include "Button.hpp"

cv::Mat gray_converter(cv::Mat img){
    cv::Mat gray_img;
    cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    cv::cvtColor(gray_img, gray_img, cv::COLOR_GRAY2BGR);
    return gray_img;
}

cv::Mat binary_converter(cv::Mat img){
    cv::Mat gray_img = gray_converter(img);
    cv::Mat binary_img;
    cv::cvtColor(gray_img, binary_img, cv::COLOR_BGR2GRAY);
    cv::threshold(binary_img, binary_img, 127, 255, cv::THRESH_BINARY);
    cv::cvtColor(binary_img, binary_img, cv::COLOR_GRAY2BGR);
    return binary_img;
}

cv::Mat canny_converter(cv::Mat img){
    cv::Mat gray_img = gray_converter(img);
    cv::Mat canny_img;
    cv::cvtColor(gray_img, canny_img, cv::COLOR_BGR2GRAY);
    cv::Canny(canny_img, canny_img, 50, 200);
    cv::cvtColor(canny_img, canny_img, cv::COLOR_GRAY2BGR);
    return canny_img;
}

cv::Mat gray_equalizer(cv::Mat img){
    cv::Mat gray_img;
    cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    cv::Mat equalized_img;
    cv::equalizeHist(gray_img, equalized_img);
    cv::cvtColor(equalized_img, equalized_img, cv::COLOR_GRAY2BGR);
    return equalized_img;
}

Mat salt_pepper_noise(const Mat &srcImage, int n/*= 1000*/)
{
	Mat dstImage = srcImage.clone();
	for (int k = 0; k < n; k++)
	{
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;

        dstImage.at<Vec3b>(i, j)[0] = 255;
        dstImage.at<Vec3b>(i, j)[1] = 255;
        dstImage.at<Vec3b>(i, j)[2] = 255;
		
		i = rand() % dstImage.rows;
		j = rand() % dstImage.cols;
		
        dstImage.at<Vec3b>(i, j)[0] = 0;
        dstImage.at<Vec3b>(i, j)[1] = 0;
        dstImage.at<Vec3b>(i, j)[2] = 0;
	}

    return dstImage;
}


cv::Mat img_operator(cv::Mat img, int operator_type, void* other_data/*=NULL*/){
    switch (operator_type)
    {
    case GRAYSCALE:
        return gray_converter(img);
    case BINARY:
        return binary_converter(img);
    case CANNY:
        return canny_converter(img);
    case GRAYEQUAL:
        return gray_equalizer(img);
    case SALTPEPPER:
        return salt_pepper_noise(img);
    default:
        cerr << "Error: Invalid operator type" << endl;
        return img;
    }
}