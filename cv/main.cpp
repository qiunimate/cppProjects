#include<iostream>
#include<opencv2/opencv.hpp>
#include <windows.h>
#include"general_helpers.hpp"
#include"cv_functions.hpp"
using namespace std;
using namespace cv;

int main(){
    //1. load image from file 
    string img_name = "data/test.jpg";
    // cout << "The name of the image is?" << endl;
    // cin >> img_name;
    Mat img = imread(img_name); // read img
    Mat processed_img;
    string process_name;
    WNDCLASS wndclass ; 
    if (img.empty()) {
        std::cerr << "Image not found or could not be loaded." << std::endl;
        return -1;
    }

    //2. display original image
    //

    string window_name = extractFileName(img_name);
    string dir_name = extractDirectoryName(img_name);
    imshow(window_name, img); // show img
    waitKey(0);

    //3. process & display image

    cout << "How do you want to operate this image?" <<endl;
    cout << "1. Convert to grayscale" <<endl;

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            processed_img = gray_converter(img);
            process_name = "_grayscale";
            break;
        default:
            printf("Invalid choice. \n");
            return -1;
    }

    imshow(window_name+process_name, processed_img);
    waitKey(0);

    //4. save image

    cout << "Do you want to save the processed image? (y/n)" << endl;
    char save_choice;
    cin >> save_choice;
    switch (save_choice) {
        case 'y':
            imwrite(dir_name + window_name + process_name + ".jpg", processed_img);
            break;
        case 'n':
            break;
        default:
            printf("Invalid choice. \n");
            return -1;
    }

    return 0;
}