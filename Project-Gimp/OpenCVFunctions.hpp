#pragma once

#include <opencv2/opencv.hpp>

cv::Mat blackAndWhite(cv::Mat image);
cv::Mat rotateImage(cv::Mat image);
cv::Mat resizeImage(cv::Mat image);
cv::Mat deformationImage(cv::Mat image);
cv::Mat cropImage(cv::Mat image);
cv::Mat brightnessAndContrast(cv::Mat image);