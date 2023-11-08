#include <iostream>
#include <opencv2/opencv.hpp>
#include "general_helpers.hpp"
#include "cv_functions.hpp"
#include "Button.hpp"
using namespace std;
using namespace cv;

struct Userdata {
    Mat img;
    vector<Button> buttons;
    Mat3b canvas;
    string winName;
    string directory_name;
    int y; // number of rows of buttons
};

int button_width = 100;
int button_height = 30;
Mat processed_img;
ButtonFunction last_oper = ORIGINAL;


void callBackFunc(int event, int x, int y, int flags, void* userdata)
{
    Mat img = ((Userdata*)userdata)->img;
    vector<Button> buttons = ((Userdata*)userdata)->buttons;
    Mat3b canvas = ((Userdata*)userdata)->canvas;
    string winName = ((Userdata*)userdata)->winName;
    string directory_name = ((Userdata*)userdata)->directory_name;
    int num_rows = ((Userdata*)userdata)->y;
    
    ButtonFunction buttonFunction;

    if (event == EVENT_LBUTTONDOWN)
    {
        buttonFunction = ORIGINAL;
        for (auto button : buttons){
            if (button.getRect().contains(Point(x, y))){
                buttonFunction = button.getButtonFunction();
                cv::Rect buttonRect(button.getRect());
                rectangle(canvas, buttonRect, Scalar(0, 0, 255), 1);
                break;
            }
        }
        if (buttonFunction != ORIGINAL){
            if (buttonFunction == SAVE){
                string path = directory_name + winName + "_" + button_functions[last_oper] + ".jpg";
                printf("Saving image to %s\n", path.c_str());
                imwrite(path, processed_img);
            } else {
                last_oper = buttonFunction;
                img_operator(img, processed_img, last_oper);
                processed_img.copyTo(canvas(Rect(processed_img.cols, (num_rows+1)*button_height, processed_img.cols, processed_img.rows)));
            }
        }
    }
    if (event == EVENT_LBUTTONUP) {
        for (auto button : buttons){
            if (button.getRect().contains(Point(x, y))){
                buttonFunction = button.getButtonFunction();
                cv::Rect buttonRect(button.getRect());
                rectangle(canvas, buttonRect, Scalar(0, 0, 0), 1);
                break;
            }
        }
    }


    imshow(winName, canvas);
    waitKey(1);
}

void main_func() 
{
    // An image
    string img_path = "data/test.jpg";
    string directory_name = extractDirectoryName(img_path);
    string file_name = extractFileName(img_path);
    string image_name = extractImageName(file_name);

    Mat img = imread(img_path);
    Size img_resize = Size(800, 600);
    resize(img, img, img_resize, INTER_LINEAR);

    // The buttons
    vector<Button> buttons;
    Button grayscale_button = Button(button_width, button_height, GRAYSCALE);
    Button binary_button = Button(button_width, button_height, BINARY);
    Button canny_button = Button(button_width, button_height, CANNY);
    Button save_button = Button(button_width, button_height, SAVE);
    Button grayequal_button = Button(button_width, button_height, GRAYEQUAL);
    Button graypepper_button = Button(button_width, button_height, SALTPEPPER);
    grayequal_button.setFontScale(0.4);
    buttons.push_back(grayscale_button);
    buttons.push_back(grayequal_button);
    buttons.push_back(binary_button);
    buttons.push_back(canny_button);
    buttons.push_back(graypepper_button);
    buttons.push_back(save_button);

    // Set the button positions
    int x = 0;
    int y = 0;
    int counter = 0;
    while (counter < buttons.size())
    {
        buttons[counter].setX(x*button_width);
        buttons[counter].setY(y*button_height);
        counter++;
        x += 1;
        if ((x+1) * button_width > 2 * img.cols)
        {
            x = 0;
            y += 1;
        }
    }

    // The canvas
    Mat3b canvas = Mat3b(img.rows+(y+1)*button_height, 2*img.cols, Vec3b(255,255,255));

    // Draw the buttons
    for (int i = 0; i < buttons.size(); i++)
    {
        buttons[i].draw(canvas);
    }

    // Draw the image
    img.copyTo(canvas(Rect(0, (y+1)*button_height, img.cols, img.rows)));

    // Setup callback function
    string winName = image_name;
    namedWindow(winName, 0);

    Userdata data = {img, buttons, canvas, winName, directory_name, y};
    setMouseCallback(winName, callBackFunc, &data);

    imshow(winName, canvas);
    waitKey();
}

// void test() {
//     string img_name = "data/test.jpg";
//     Mat img = imread(img_name);
//     img_operator(img, processed_img, GRAYSCALE);

//     imshow("ori", img);
//     waitKey(0);
//     printf("The size of the processed image is %d x %d \n", processed_img.cols, processed_img.rows);
// }

int main() {
    main_func();
    return 0;
}