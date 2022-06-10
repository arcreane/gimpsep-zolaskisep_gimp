#include "Functions.hpp"
#include "OpenCVFunctions.hpp"

#include <iostream>

using namespace std;
using namespace cv;


Mat chooseOriginalImage()
{
	Mat image;

	while (image.empty())
	{
		string path;
		cout << "Location of your image: ";
		cin >> path;

		image = imread(path);

		if (image.empty())
		{
			cout << "Incorrect location." << endl;
		}

		cout << endl;
	}

	return image;
}


string chooseTransformation()
{
	string correct_values[6];
	correct_values[0] = "1";
	correct_values[1] = "2";
	correct_values[2] = "3";
	correct_values[3] = "4";
	correct_values[4] = "5";
	correct_values[5] = "6";

	string choice;
	
	while (!(find(correct_values, correct_values + sizeof(correct_values) / sizeof(*correct_values), choice) != correct_values + sizeof(correct_values) / sizeof(*correct_values)))
	{
		cout << "What transformation do you want?" << endl;
		cout << "1- Black & White" << endl;
		cout << "2- Rotation" << endl;
		cout << "3- Resize" << endl;
		cout << "4- Deformation" << endl;
		cout << "5- Crop" << endl;
		cout << "6- Brightness & Contrast" << endl;
		cout << "Choice: ";
		cin >> choice;

		if (!(find(correct_values, correct_values + sizeof(correct_values) / sizeof(*correct_values), choice) != correct_values + sizeof(correct_values) / sizeof(*correct_values)))
		{
			cout << "Incorrect choice." << endl;
		}

		cout << endl;
	}
	
	return choice;
}


Mat applyTransformation(string choice, Mat image)
{
	int choice_int = stoi(choice);
	Mat new_image;

	switch (choice_int)
	{
		case 1:
			new_image = blackAndWhite(image);
			break;

		case 2:
			new_image = rotateImage(image);
			break;

		case 3:
			new_image = resizeImage(image);
			break;

		case 4:
			new_image = deformationImage(image);
			break;

		case 5:
			new_image = cropImage(image);
			break;

		case 6:
			new_image = brightnessAndContrast(image);
			break;

		default:
			cout << "Error" << endl;
			break;
	}

	return new_image;
}


void displayImages(Mat image, Mat new_image)
{
	namedWindow("Original image", WINDOW_AUTOSIZE);
	namedWindow("New image", WINDOW_AUTOSIZE);

	while (true)
	{
		imshow("Original image", image);
		imshow("New image", new_image);

		if (waitKey(10) == 27)
		{
			break;
		}
	}

	destroyAllWindows();
}


void saveImage(Mat new_image)
{
	string correct_values[4];
	correct_values[0] = "Y";
	correct_values[1] = "y";
	correct_values[2] = "N";
	correct_values[3] = "n";

	string choice;

	while (!(find(correct_values, correct_values + sizeof(correct_values) / sizeof(*correct_values), choice) != correct_values + sizeof(correct_values) / sizeof(*correct_values)))
	{
		cout << endl <<"Do you want to save the new image? (Y/N): ";
		cin >> choice;

		if (!(find(correct_values, correct_values + sizeof(correct_values) / sizeof(*correct_values), choice) != correct_values + sizeof(correct_values) / sizeof(*correct_values)))
		{
			cout << "Incorrect value (Y/N)." << endl;
		}

		cout << endl;
	}

	if (choice == "Y" || choice == "y")
	{
		string name;
		cout << "Choose the name of the new image: ";
		cin >> name;

		imwrite(name + ".png", new_image);
		cout << "Image saved." << endl;
	}
}