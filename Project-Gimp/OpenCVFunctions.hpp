#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

cv::Mat blackAndWhite(cv::Mat image);
cv::Mat rotateImage(cv::Mat image);
cv::Mat resizeImage(cv::Mat image);
cv::Mat deformationImage(cv::Mat image);
cv::Mat cropImage(cv::Mat image);
cv::Mat brightnessAndContrast(cv::Mat image);
cv::Mat cannyEdgeDetection(cv::Mat image);
cv::Mat erosionImage(cv::Mat image);
cv::Mat dilationImage(cv::Mat image);
std::vector<cv::Mat> chooseImagesForPanorama(cv::Mat image);
cv::Mat panoramaStiching(std::vector<cv::Mat> images);
bool isStitchable(std::vector<cv::Mat> images);