#include "Functions.hpp";

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main()
{
	Mat image = chooseOriginalImage();
	string choice = chooseTransformation();
	Mat new_image = applyTransformation(choice, image);
	displayImages(image, new_image);
	saveImage(new_image);

	return 0;
}