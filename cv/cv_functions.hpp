#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

void gray_converter(const cv::Mat &img, cv::Mat &dst_img);
void binary_converter(const cv::Mat &img, cv::Mat &dst_img);
void canny_detector(cv::Mat img);
void sobel_detector(cv::Mat img);
void laplacian_detector(const cv::Mat &img, cv::Mat &dst_img);
void gray_equalizer(const cv::Mat &img, cv::Mat &dst_img);
void Gaussian_Noise(const cv::Mat &img, cv::Mat &dst_img);
void Salt_and_pepper_Noise(const cv::Mat &img, cv::Mat &dst_img);
void salt_pepper_noise(const cv::Mat &img, cv::Mat &dst_img, int n=1000);
void img_operator(const cv::Mat &img, cv::Mat &dst_img, int operator_type, void* other_data=NULL);