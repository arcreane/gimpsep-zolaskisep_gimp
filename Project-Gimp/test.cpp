//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//vector<Mat> chooseImagesForPanorama(Mat image)
//{
//    string path;
//    vector<Mat> images;
//    images.push_back(image);
//
//    while (path != "1")
//    {
//
//        cout << "When you have finished chosen your pictures enter 1!";
//        cout << "Location of your image: ";
//        cin >> path;
//
//        Mat image = imread(path);
//
//        if (image.empty())
//        {
//            cout << "Incorrect location." << endl;
//        }
//        else {
//            images.push_back(image);
//        }
//
//        cout << endl;
//    }
//
//    return images;
//}
//
//Mat panoramaStiching(vector<Mat> images)
//{
//    Mat panorama;
//    Stitcher::Mode mode = Stitcher::PANORAMA;
//    Ptr<Stitcher> stitcher = Stitcher::create(mode);
//    Stitcher::Status status = stitcher->stitch(images, panorama);
//    return panorama;
//}
//
//
//int main()
//{
//    return 0;
//}


