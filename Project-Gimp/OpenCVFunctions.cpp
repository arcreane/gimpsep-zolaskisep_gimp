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


Mat cannyEdgeDetection(Mat image)
{
    Mat image_canny;
    int lowThreshold = 0;

    namedWindow("Controller", WINDOW_AUTOSIZE);
    namedWindow("Canny edge detection", WINDOW_AUTOSIZE);

    createTrackbar("Threshold ", "Controller", &lowThreshold, 100);

    while (true)
    {
        Mat image_BW = blackAndWhite(image);

        Mat image_blur;
        GaussianBlur(image_BW, image_blur, Size(5, 5), 1.5);

        Canny(image_blur, image_canny, lowThreshold, lowThreshold * 3, 3);
        
        imshow("Canny edge detection", image_canny);

        if (waitKey(10) == 27)
        {
            break;
        }
    }

    destroyAllWindows();
    return image_canny;
}


Mat erosionImage(Mat image)
{
    Mat image_erosion;
    int erosion_elem = 0;
    int erosion_size = 0;

    namedWindow("Controller", WINDOW_AUTOSIZE);
    namedWindow("Erosion", WINDOW_AUTOSIZE);

    createTrackbar("Element ", "Controller", &erosion_elem, 2);
    createTrackbar("Size ", "Controller", &erosion_size, 10);

    while (true)
    {
        int erosion_type;

        if (erosion_elem == 0)
        {
            erosion_type = MORPH_RECT;
        }

        else if (erosion_elem == 1)
        {
            erosion_type = MORPH_CROSS;
        }

        else if (erosion_elem == 2)
        {
            erosion_type = MORPH_ELLIPSE;
        }

        Mat element = getStructuringElement(erosion_type, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));
        erode(image, image_erosion, element);

        imshow("Erosion", image_erosion);

        if (waitKey(10) == 27)
        {
            break;
        }
    }

    destroyAllWindows();
    return image_erosion;
}


Mat dilationImage(Mat image)
{
    Mat image_dilation;
    int dilation_elem = 0;
    int dilation_size = 0;

    namedWindow("Controller", WINDOW_AUTOSIZE);
    namedWindow("Dilation", WINDOW_AUTOSIZE);

    createTrackbar("Element ", "Controller", &dilation_elem, 2);
    createTrackbar("Size ", "Controller", &dilation_size, 10);

    while (true)
    {
        int dilation_type;

        if (dilation_elem == 0)
        {
            dilation_type = MORPH_RECT;
        }

        else if (dilation_elem == 1)
        {
            dilation_type = MORPH_CROSS;
        }

        else if (dilation_elem == 2)
        {
            dilation_type = MORPH_ELLIPSE;
        }

        Mat element = getStructuringElement(dilation_type, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
        dilate(image, image_dilation, element);

        imshow("Dilation", image_dilation);

        if (waitKey(10) == 27)
        {
            break;
        }
    }

    destroyAllWindows();
    return image_dilation;
}


Mat panoramaStiching(vector<Mat> images) {
    Mat panorama;
    Stitcher::Mode mode = Stitcher::PANORAMA;
    Ptr<Stitcher> stitcher = Stitcher::create(mode);
    Stitcher::Status status = stitcher->stitch(images, panorama);
    for (int i = 0; i < 2; i++) {
        namedWindow("Display window1", WINDOW_AUTOSIZE);
        namedWindow("Display window", WINDOW_AUTOSIZE);
        imshow("Display window", images[0]);
        imshow("Display window1", images[1]);
    }

    waitKey(0);
    destroyAllWindows();
    if (status != Stitcher::OK) {
        cout << "not stitchable";
    }

    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", panorama);

    waitKey(0); // Wait for any keystroke in the window

    destroyWindow("Display window"); //destroy the created window

    return panorama;
}

vector<Mat> chooseImagesForPanorama(Mat image)
{
    string path;
    vector<Mat> images;
    images.push_back(image);



    while (path != "1")
    {

        cout << "When you have finished chosen your pictures enter 1! ";
        cout << "Location of your image: ";
        cin >> path;


        if (path != "1") {
            Mat image = imread(path);
            if (image.empty())
            {
                cout << "Incorrect location." << endl;
            }
            else {
                images.push_back(image);
            }
        }
        cout << endl;
    }
    return images;

}

bool isStitchable(vector<Mat> images) {
    Mat panorama;
    Stitcher::Mode mode = Stitcher::PANORAMA;
    Ptr<Stitcher> stitcher = Stitcher::create(mode);
    Stitcher::Status status = stitcher->stitch(images, panorama);
    if (status != Stitcher::OK) {
        cout << "not stitchable";
        return false;
    }
    return true;
}

