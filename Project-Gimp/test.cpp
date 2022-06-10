//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//
//int main()
//{
//	//VideoCapture cap(0);
//	//Mat img;
//
//	//while (true)
//	//{
//	//	cap.read(img);
//	//	imshow("Image", img);
//	//	waitKey(1);
//	//}
//
//    // open the video file for reading
//    Mat img = imread("malo.jpg");;
//
//    // if not success, exit program
//
//    //define original and rotate window name
//    namedWindow("original", WINDOW_AUTOSIZE);
//    namedWindow("rotate", WINDOW_AUTOSIZE);
//
//    int iAngle = 180;
//
//    //create track bar
//    createTrackbar("Rotation", "rotate", &iAngle, 360);
//    Mat frame_rotate;
//
//    while (true)
//    {
//        //rotate
//        Point2f center(img.cols / 2, img.rows / 2);
//        double rotationAngle = iAngle;
//        double scale = 1;
//
//        Mat M = getRotationMatrix2D(center, rotationAngle, scale);
//        warpAffine(img, frame_rotate, M, img.size());
//
//
//        //show the two video
//        imshow("original", img);
//        imshow("rotate", frame_rotate);
//
//
//
//        //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
//        if (waitKey(30) == 27)
//        {
//            cout << "Esc key is pressed by user. Stoppig the video" << endl;
//            break;
//        }
//
//    }
//
//        imwrite("HappyFishGrey.jpg", frame_rotate);
//
//
//
//	return 0;
//}