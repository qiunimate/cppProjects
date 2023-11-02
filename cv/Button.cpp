#include "Button.hpp"

Button::Button() {
    button = Rect(0, 0, 0, 0);
    text = "";
}

Button::Button(int width, int height, ButtonFunction function) {
    button = Rect(0, 0, width, height);
    this->buttonFunction = function;
    this->text = button_functions[function];
}

Button::Button(Rect button, string text) {
    this->button = button;
    this->text = text;
}

void Button::setX(int x) {
    button.x = x;
}

void Button::setY(int y) {
    button.y = y;
}

void Button::setWidth(int width) {
    button.width = width;
}

void Button::setHeight(int height) {
    button.height = height;
}

void Button::setText(string text) {
    this->text = text;
}

Rect Button::getRect() {
    return button;
}

int Button::getX() {
    return button.x;
}

int Button::getY() {
    return button.y;
}

int Button::getWidth() {
    return button.width;
}

int Button::getHeight() {
    return button.height;
}

std::string Button::getText() {
    return text;
}

void Button::setFontFace(int fontFace) {
    this->fontFace = fontFace;
}

void Button::setFontScale(double fontScale) {
    this->fontScale = fontScale;
}

void Button::setThickness(int thickness) {
    this->thickness = thickness;
}

int Button::getFontFace() {
    return fontFace;
}

double Button::getFontScale() {
    return fontScale;
}

int Button::getThickness() {
    return thickness;
}

void Button::setButtonFunction(ButtonFunction buttonFunction) {
    this->buttonFunction = buttonFunction;
}

ButtonFunction Button::getButtonFunction() {
    return buttonFunction;
}


Point Button::getTextPosition() {
    int baseline = 0;
    Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
    Point textOrg((button.width - textSize.width)/2, (button.height + textSize.height)/2);
    return textOrg;
}

void Button::draw(Mat3b canvas) {
    cv::Rect buttonRect(button); // Create a Rect object from button's coordinates
    rectangle(canvas, buttonRect, Scalar(0, 0, 0), 1);
    int baseline = 0;
    Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
    Point textOrg((button.width - textSize.width)/2, (button.height + textSize.height)/2);
    putText(canvas(button), text, textOrg, fontFace, fontScale, Scalar(0,0,0), thickness);
}