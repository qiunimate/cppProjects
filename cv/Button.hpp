#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Button {
    public: 
        Button();
        Button(int x, int y, int width, int height, string text);
        Button(Rect button, string text);
        void setX(int x);
        void setY(int y);
        void setWidth(int width);
        void setHeight(int height);
        void setText(string text);
        Rect getButton();
        int getX();
        int getY();
        int getWidth();
        int getHeight();
        std::string getText();

        void draw(Mat3b canvas, int fontFace, double fontScale, int thickness);

    private:
        Rect button;
        string text;
};
