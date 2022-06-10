#pragma once

#include <string>
#include <opencv2/opencv.hpp>

cv::Mat chooseOriginalImage();
std::string chooseTransformation();
cv::Mat applyTransformation(std::string choice, cv::Mat image);
void displayImages(cv::Mat image, cv::Mat new_image);
void saveImage(cv::Mat new_image);