#include "OpenCVFunctions.hpp"
#include "Functions.hpp"

using namespace cv;
using namespace std;


Mat blackAndWhite(Mat image)
{
	Mat image_BW;
	cvtColor(image, image_BW, COLOR_BGR2GRAY);

	return image_BW;
}


Mat rotateImage(Mat image)
{
	int angle = 180;
    Mat image_rotate;

    namedWindow("Controller", WINDOW_AUTOSIZE);
    namedWindow("Rotation", WINDOW_AUTOSIZE);

	createTrackbar("Rotation", "Controller", &angle, 360);
	
    while (true)
    {
        Point2f center(image.cols / 2, image.rows / 2);
        Mat M = getRotationMatrix2D(center, angle, 1);

        Rect2f bbox = RotatedRect(Point2f(), image.size(), angle).boundingRect2f();
        M.at<double>(0, 2) += bbox.width / 2.0 - image.cols / 2.0;
        M.at<double>(1, 2) += bbox.height / 2.0 - image.rows / 2.0;

        warpAffine(image, image_rotate, M, bbox.size());

        imshow("Rotation", image_rotate);

        if (waitKey(10) == 27)
        {
            break;
        }
    }

    destroyAllWindows();
    return image_rotate;
}


Mat resizeImage(Mat image)
{
    int size = 100;
    Mat image_resize;

    namedWindow("Controller", WINDOW_AUTOSIZE);
    namedWindow("Resize", WINDOW_AUTOSIZE);
    createTrackbar("Size(%) ", "Controller", &size, 500);

    while (true)
    {
        double scale = (double) size / 100;

        if (scale < 0.01)
        {
            scale = 0.01;
        }

        resize(image, image_resize, Size(), scale, scale, INTER_LINEAR);
        imshow("Resize", image_resize);

        if (waitKey(10) == 27)
        {
            break;
        }
    }

    destroyAllWindows();
    return image_resize;
}


Mat deformationImage(Mat image)
{
    int sizeX = 100;
    int sizeY = 100;
    Mat image_resize;

    namedWindow("Controller", WINDOW_AUTOSIZE);
    namedWindow("Deformation", WINDOW_AUTOSIZE);

    createTrackbar("SizeX(%) ", "Controller", &sizeX, 500);
    createTrackbar("SizeY(%) ", "Controller", &sizeY, 500);

    while (true)
    {
        double scaleX = (double) sizeX / 100;
        double scaleY = (double)sizeY / 100;

        if (scaleX < 0.01)
        {
            scaleX = 0.01;
        }

        if (scaleY < 0.01)
        {
            scaleY = 0.01;
        }

        resize(image, image_resize, Size(), scaleX, scaleY, INTER_LINEAR);
        imshow("Deformation", image_resize);

        if (waitKey(10) == 27)
        {
            break;
        }
    }

    destroyAllWindows();
    return image_resize;
}


Mat cropImage(Mat image)
{
    Mat image_crop;
    int height = image.size().height;
    int width = image.size().width;

    int top = 0;
    int bottom = height;
    int right = width;
    int left = 0;

    namedWindow("Controller", WINDOW_AUTOSIZE);
    namedWindow("Crop", WINDOW_AUTOSIZE);

    createTrackbar("Top(px) ", "Controller", &top, height);
    createTrackbar("Bottom(px) ", "Controller", &bottom, height);
    createTrackbar("Right(px) ", "Controller", &right, width);
    createTrackbar("Left(px) ", "Controller", &left, width);

    while (true)
    {
        if (top == bottom || top > bottom || bottom < top)
        {
            top = bottom - 1;
            bottom = top + 2;

            if (top < 0)
            {
                top = 0;
            }

            if (bottom > height)
            {
                bottom = height;
            }
        }

        if (left == right || left > right || right < left)
        {
            left = right - 1;
            right = left + 2;

            if (left < 0)
            {
                left = 0;
            }

            if (right > width)
            {
                right = width;
            }
        }

        image_crop = image(Range(top, bottom), Range(left, right));
        imshow("Crop", image_crop);

        if (waitKey(10) == 27)
        {
            break;
        }
    }

    destroyAllWindows();
    return image_crop;
}


Mat brightnessAndContrast(Mat image)
{
    Mat image_BC;
    int brightness = 255;
    int contrast100 = 100;
    
    namedWindow("Controller", WINDOW_AUTOSIZE);
    namedWindow("Brightness & Contrast", WINDOW_AUTOSIZE);

    createTrackbar("Brightness ", "Controller", &brightness, 510);
    createTrackbar("Contrast(%) ", "Controller", &contrast100, 1000);


    while (true)
    {
        double contrast = (double)contrast100 / 100;

        image_BC = image.clone();
        image_BC.Mat::convertTo(image_BC, image_BC.type(), contrast, brightness - 255);
        imshow("Brightness & Contrast", image_BC);

        if (waitKey(10) == 27)
        {
            break;
        }
    }

    destroyAllWindows();
    return image_BC;
}