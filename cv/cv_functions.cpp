#include "cv_functions.hpp"
#include "Button.hpp"

void gray_converter(const cv::Mat &img, cv::Mat &dst_img){
    cv::cvtColor(img, dst_img, cv::COLOR_BGR2GRAY);
    cv::cvtColor(dst_img, dst_img, cv::COLOR_GRAY2BGR);
}

void binary_converter(const cv::Mat &img, cv::Mat &dst_img){
    gray_converter(img, dst_img);
    cv::cvtColor(dst_img, dst_img, cv::COLOR_BGR2GRAY);
    cv::threshold(dst_img, dst_img, 127, 255, cv::THRESH_BINARY);
    cvtColor(dst_img, dst_img, COLOR_GRAY2BGR);
}

void canny_converter(const cv::Mat &img, cv::Mat &dst_img){
    gray_converter(img, dst_img);
    cv::cvtColor(dst_img, dst_img, cv::COLOR_BGR2GRAY);
    cv::Canny(dst_img, dst_img, 50, 200);
    cv::cvtColor(dst_img, dst_img, cv::COLOR_GRAY2BGR);
}

void sobel_detector(const cv::Mat &img, cv::Mat &dst_img){
    cv::cvtColor(img, dst_img, cv::COLOR_BGR2GRAY);
    cv::Sobel(dst_img, dst_img, CV_8U, 1, 1, 3, 1, 0, cv::BORDER_DEFAULT);
    cv::cvtColor(dst_img, dst_img, cv::COLOR_GRAY2BGR);
}

void laplacian_detector(const cv::Mat &img, cv::Mat &dst_img){
    cv::cvtColor(img, dst_img, cv::COLOR_BGR2GRAY);
    cv::Laplacian(dst_img, dst_img, CV_8U, 3, 1, 0, cv::BORDER_DEFAULT);
    cv::cvtColor(dst_img, dst_img, cv::COLOR_GRAY2BGR);
}

void gray_equalizer(const cv::Mat &img, cv::Mat &dst_img){
    cv::cvtColor(img, dst_img, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(dst_img, dst_img);
    cv::cvtColor(dst_img, dst_img, cv::COLOR_GRAY2BGR);
}

void Gaussian_Noise(const cv::Mat &img, cv::Mat &dst_img){
    dst_img = img.clone();
    cv::Mat noise = cv::Mat(img.size(), CV_32SC3);
    cv::randn(noise, 0, 50);
    dst_img += noise;
}

void salt_pepper_noise(const cv::Mat &img, cv::Mat &dst_img, int n/*= 1000*/) // n is the number of noise points
{
	dst_img = img.clone();
	for (int k = 0; k < n; k++)
	{
		int i = rand() % dst_img.rows;
		int j = rand() % dst_img.cols;
        dst_img.at<Vec3b>(i, j)[0] = 255;
        
        i = rand() % dst_img.rows;
        j = rand() % dst_img.cols;
        dst_img.at<Vec3b>(i, j)[1] = 255;

        i = rand() % dst_img.rows;
        j = rand() % dst_img.cols;
        dst_img.at<Vec3b>(i, j)[2] = 255;

        i = rand() % dst_img.rows;
        j = rand() % dst_img.cols;
        dst_img.at<Vec3b>(i, j)[2] = 0;

        i = rand() % dst_img.rows;
        j = rand() % dst_img.cols;
        dst_img.at<Vec3b>(i, j)[1] = 0;

        i = rand() % dst_img.rows;
        j = rand() % dst_img.cols;
        dst_img.at<Vec3b>(i, j)[0] = 0;
    }
}


void img_operator(const cv::Mat &img, cv::Mat &dst_img, int operator_type, void* other_data/*=NULL*/){
    // carry out the operations
    dst_img = img.clone();
    switch (operator_type)
    {
    case GRAYSCALE:
        gray_converter(img, dst_img);
        break;
    case BINARY:
        binary_converter(img, dst_img);
        break;
    case CANNY:
        canny_converter(img, dst_img);
        break;
    case GRAYEQUAL:
        gray_equalizer(img, dst_img);
        break;
    case SOBEL:
        sobel_detector(img, dst_img);
        break;
    case LAPLACIAN:
        laplacian_detector(img, dst_img);
        break;
    case GAUSSIANNOISE:
        Gaussian_Noise(img, dst_img);
        break;
    case SALTPEPPERNOISE:
        salt_pepper_noise(img, dst_img);
        break;
    case ORIGINAL:
        cout << "Operating the original image" << endl;
        break;
    default:
        cout << "No such operator" << endl;
        break;
    }
}