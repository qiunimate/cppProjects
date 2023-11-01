#include<iostream>
#include<opencv2/opencv.hpp>
#include <windows.h>
#include"general_helpers.hpp"
#include"cv_functions.hpp"
using namespace std;
using namespace cv;

Mat3b canvas;
string buttonText("grayscale");
string winName = "My cool GUI v0.1";

Rect button;

void callBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        if (button.contains(Point(x, y)))
        {
            cout << "Clicked!" << endl;
            rectangle(canvas(button), button, Scalar(0,0,255), 2);
        }
    }
    if (event == EVENT_LBUTTONUP)
    {
        rectangle(canvas, button, Scalar(200, 200, 200), 2);
    }

    imshow(winName, canvas);
    waitKey(1);
}

int main() 
{
    // An image
    string img_name = "data/test.jpg";
    Mat3b img = imread(img_name);

    // Your button
    button = Rect(0, 0, 100, 30);

    // The canvas
    canvas = Mat3b(img.rows + button.height, img.cols, Vec3b(0,0,0));

    // Draw the button
    canvas(button) = Vec3b(200,200,200);
    Size textSize = getTextSize(buttonText, FONT_HERSHEY_PLAIN, 0.75, 1, 0);
    int x = button.x + (button.width - textSize.width) / 2;
    int y = button.y + (button.height + textSize.height) / 2;
    putText(canvas(button), buttonText, Point(x,y), FONT_HERSHEY_PLAIN, 0.75, Scalar(0,0,0));

    // Draw the image
    img.copyTo(canvas(Rect(0, button.height, img.cols, img.rows)));

    // Setup callback function
    namedWindow(winName);
    setMouseCallback(winName, callBackFunc);

    imshow(winName, canvas);
    waitKey();

    return 0;
}


// int main(){
//     //1. load image from file 
//     string img_name = "data/test.jpg";
//     // cout << "The name of the image is?" << endl;
//     // cin >> img_name;
//     Mat img = imread(img_name); // read img
//     Mat processed_img;
//     string process_name;
//     WNDCLASS wndclass ; 
//     if (img.empty()) {
//         std::cerr << "Image not found or could not be loaded." << std::endl;
//         return -1;
//     }

//     //2. display original image
//     //

//     string window_name = extractImageName(extractFileName(img_name));
//     string dir_name = extractDirectoryName(img_name);
//     imshow(window_name, img); // show img
//     waitKey(0);

//     //3. process & display image

//     cout << "How do you want to operate this image?" <<endl;
//     cout << "1. Convert to grayscale" <<endl;
//     cout << "9. Quit" <<endl;

//     int choice;
//     cin >> choice;

//     switch (choice) {
//         case 1:
//             processed_img = gray_converter(img);
//             process_name = "_grayscale";
//             break;
//         case 9:
//             return 0;
//         default:
//             printf("Invalid choice. \n");
//             return -1;
//     }

//     imshow(window_name+process_name, processed_img);
//     waitKey(0);

//     //4. save image

//     cout << "Do you want to save the processed image? (y/n)" << endl;
//     char save_choice;
//     cin >> save_choice;
//     switch (save_choice) {
//         case 'y':
//             imwrite(dir_name + window_name + process_name + ".jpg", processed_img);
//             break;
//         case 'n':
//             break;
//         default:
//             printf("Invalid choice. \n");
//             return -1;
//     }

//     return 0;
// }