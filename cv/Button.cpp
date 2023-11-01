#include "Button.hpp"

Button::Button() {
    button = Rect(0, 0, 0, 0);
    text = "";
}

Button::Button(int x, int y, int width, int height, string text) {
    button = Rect(x, y, width, height);
    this->text = text;
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

Rect Button::getButton() {
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

void Button::draw(Mat3b canvas, int fontFace, double fontScale, int thickness) {
    rectangle(canvas(button), button, Scalar(200,200,200), 2);
    int baseline = 0;
    Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
    Point textOrg((button.width - textSize.width)/2, (button.height + textSize.height)/2);
    putText(canvas(button), text, textOrg, fontFace, fontScale, Scalar(0,0,0), thickness);
}