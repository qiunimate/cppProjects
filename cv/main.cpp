#include <iostream>
#include "general_helpers.hpp"
#include "cv_functions.hpp"
#include "Button.hpp"
using namespace std;
using namespace cv;

// to pass data to the callback function
struct Userdata {
    cv::Mat img;
    vector<Button> buttons;
    cv::Mat3b canvas;
    string winName;
    string directory_name;
    int y; // number of rows of buttons
};

// global variables
int button_width = 200;
int button_height = 50;
cv::Mat processed_img;
ButtonFunction last_oper = ORIGINAL; // the last operation that is performed on the image

// On mouse event
void callBackFunc(int event, int x, int y, int flags, void* userdata)
{
    cv::Mat img = ((Userdata*)userdata)->img;
    vector<Button> buttons = ((Userdata*)userdata)->buttons;
    cv::Mat3b canvas = ((Userdata*)userdata)->canvas;
    string winName = ((Userdata*)userdata)->winName;
    string directory_name = ((Userdata*)userdata)->directory_name;
    int num_rows = ((Userdata*)userdata)->y;
    
    ButtonFunction buttonFunction; // the function of the button that is clicked

    if (event == EVENT_LBUTTONDOWN)
    {
        buttonFunction = ORIGINAL;
        for (auto button : buttons){
            if (button.getRect().contains(Point(x, y))){ // if the mouse is clicked on a button
                buttonFunction = button.getButtonFunction();
                Rect buttonRect(button.getRect());
                rectangle(canvas, buttonRect, Scalar(0, 0, 255), 1); // draw a red rectangle around the button
                break;
            }
        }
        if (buttonFunction != ORIGINAL){
            if (buttonFunction == SAVE){ // if the save button is clicked
                string path = directory_name + winName + "_" + button_functions[last_oper] + ".jpg";
                printf("Saving image to %s\n", path.c_str());
                imwrite(path, processed_img);
            } else { // if any operation button is clicked
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
                Rect buttonRect(button.getRect());
                rectangle(canvas, buttonRect, Scalar(0, 0, 0), 1); // draw a black rectangle around the button (to remove the red one)
                break;
            }
        }
    }

    imshow(winName, canvas);
    waitKey(1);
}

void main_func() 
{
    string img_path = "data/test.jpg";
    string directory_name = extractDirectoryName(img_path);
    string file_name = extractFileName(img_path);
    string image_name = extractImageName(file_name);
    cv::Mat img = imread(img_path);
    Size img_resize = Size(800, 600);
    resize(img, img, img_resize, INTER_LINEAR);

    // The buttons
    vector<Button> buttons;
    Button grayscale_button = Button(button_width, button_height, GRAYSCALE);
    Button binary_button = Button(button_width, button_height, BINARY);
    Button canny_button = Button(button_width, button_height, CANNY);
    Button sobel_button = Button(button_width, button_height, SOBEL);
    Button laplacian_button = Button(button_width, button_height, LAPLACIAN);
    Button gaussian_button = Button(button_width, button_height, GAUSSIANNOISE);
    Button salt_pepper_button = Button(button_width, button_height, SALTPEPPERNOISE);
    Button save_button = Button(button_width, button_height, SAVE);
    Button grayequal_button = Button(button_width, button_height, GRAYEQUAL);
    buttons.push_back(grayscale_button);
    buttons.push_back(grayequal_button);
    buttons.push_back(binary_button);
    buttons.push_back(canny_button);
    buttons.push_back(sobel_button);
    buttons.push_back(laplacian_button);
    buttons.push_back(gaussian_button);
    buttons.push_back(salt_pepper_button);
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
    cv::Mat3b canvas = cv::Mat3b(img.rows+(y+1)*button_height, 2*img.cols, Vec3b(255,255,255));

    // Draw the buttons
    for (int i = 0; i < buttons.size(); i++)
    {
        buttons[i].draw(canvas);
    }

    // Draw the operated image
    img.copyTo(canvas(Rect(0, (y+1)*button_height, img.cols, img.rows)));

    // Setup callback function
    string winName = image_name;
    namedWindow(winName, 0);

    Userdata data = {img, buttons, canvas, winName, directory_name, y};
    setMouseCallback(winName, callBackFunc, &data);

    imshow(winName, canvas);
    waitKey();
}

int main() {
    main_func();
    return 0;
}