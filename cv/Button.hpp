#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const string button_functions[] = {"Grayscale", "Binary", "Canny","GrayEqualize", "SaltPepper", "Save", "Original"};

enum ButtonFunction {
    GRAYSCALE,
    BINARY,
    CANNY,
    GRAYEQUAL,
    SALTPEPPER,
    SAVE,
    ORIGINAL,
};

class Button {
    public: 
        Button();
        Button(int width, int height, ButtonFunction function);
        Button(Rect button, string text);
        void setX(int x);
        void setY(int y);
        void setWidth(int width);
        void setHeight(int height);
        void setText(string text);
        void setFontFace(int fontFace);
        void setFontScale(double fontScale);
        void setThickness(int thickness);
        void setButtonFunction(ButtonFunction buttonFunction);
        Rect getRect();
        int getX();
        int getY();
        int getWidth();
        int getHeight();
        int getFontFace();
        double getFontScale();
        int getThickness();
        ButtonFunction getButtonFunction();
        string getText();
        Point getTextPosition();

        void draw(Mat3b canvas);

    private:
        Rect button;
        string text;
        ButtonFunction buttonFunction;
        int fontFace = FONT_HERSHEY_COMPLEX;
        double fontScale = 0.5;
        int thickness = 1;
};
