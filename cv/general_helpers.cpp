#include "general_helpers.hpp"

std::string extractFileName(const std::string path) {
    size_t found = path.find_last_of("/\\"); // Find the last directory separator
    if (found != std::string::npos) {
        return path.substr(found + 1); // Extract the substring after the separator
    }
    return path; // No separator found, return the original path
}

std::string extractDirectoryName(const std::string path) {
    size_t found = path.find_last_of("/\\"); // Find the last directory separator
    if (found != std::string::npos) {
        return path.substr(0, found + 1); // Extract the substring before the separator
    }
    return ""; // No separator found
}

std::string extractImageName(const std::string path) {
    size_t found = path.find_last_of(".\\"); 
    if (found != std::string::npos) {
        return path.substr(0, found);
    }
    return path;
}


// void callBackFunc(Rect button, Mat3b canvas, int event, int x, int y, string winName) {
//     if (event == EVENT_LBUTTONDOWN)
//     {
//         if (button.contains(Point(x, y)))
//         {
//             cout << "Clicked!" << endl;
//             rectangle(canvas(button), button, Scalar(0,0,255), 2);
//         }
//     }
//     if (event == EVENT_LBUTTONUP)
//     {
//         rectangle(canvas, button, Scalar(200, 200, 200), 2);
//     }

//     imshow(winName, canvas);
//     waitKey(1);
// }
