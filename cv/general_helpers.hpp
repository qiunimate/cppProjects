#include <iostream>
#include <string>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

std::string extractFileName(const std::string path);
std::string extractDirectoryName(const std::string path);
std::string extractImageName(const std::string path);
// void callBackFunc(Rect button, Mat3b canvas, int event, int x, int y, string winName);