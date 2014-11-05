#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main()
{
    bool isCalibrated = false;
    const int heightStable = 240;
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "Fail" << endl;
        exit(-1);
    }

    cv::CascadeClassifier cascade;
    string name("haarcascade_frontalface_default.xml");
    cascade.load(name);
    if (cascade.empty())
    {
        cout << "FUCKING ERROR" << endl;
        exit(1);
    }
    cv::namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);
    cv::Size size;
    size.height = heightStable;
    size.width = cap.get(CV_CAP_PROP_FRAME_WIDTH) * heightStable / cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    const int frameCenterX = size.width / 2;
    const int frameCenterY = size.height / 2;

    const int calibratedMaxSize = 80;
    const int calibratedMinSize = 60;

    cout << "Heigh: " << size.height << " " << "Width: " << size.width << endl;
    while (1)
    {
        cv::Mat frame;
        cv::Mat grayFrame;
        bool bSuccess = cap.read(frame);

        if (!bSuccess)
        {
            cout << "Cannot read a frame from video stream" << endl;
            continue;
        }

        cv::resize(frame, frame, size);
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(grayFrame, grayFrame);
        vector<cv::Rect> faces;

        cascade.detectMultiScale(grayFrame, faces, 1.1, 3, cv::CASCADE_SCALE_IMAGE);

        size_t current_index = 0;
        int current_area = 0;

        size_t biggestIndex = 0;
        int biggestArea = 0;

        for (current_index = 0; current_index < faces.size(); ++current_index)

        {
            current_area = faces[current_index].width * faces[current_index].height;

            if (current_area > biggestArea)
            {
                biggestIndex = current_index;
                biggestArea = current_area;
            }
        }

        const string text = isCalibrated ? "CALIBRATED" : "NOT CALIBRATED";
        cv::putText(frame, text, cvPoint(size.width / 4, 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);

        int centerX = 0;
        int centerY = 0;

        if (!faces.empty())
        {
            cv::Point pt1(faces[biggestIndex].x, faces[biggestIndex].y);
            cv::Point pt2((faces[biggestIndex].x + faces[biggestIndex].height), (faces[biggestIndex].y + faces[biggestIndex].width));
            centerX = (pt1.x + pt2.x) / 2;
            centerY = (pt1.y + pt2.y) / 2;
            int width = pt2.x - pt1.x;

            if (width > calibratedMaxSize)
                isCalibrated = false;
            else if (width < calibratedMinSize)
                isCalibrated = false;
            else
                isCalibrated = true;

            cv::rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0), 2, 8, 0);
        }

        if (isCalibrated)
        {
            if (centerX || centerY)
            {
                cout << centerX - frameCenterX << " " << frameCenterY - centerY << endl;
            }
            else
            {
                cout << "Face lost..." << endl;
            }
        }

        imshow("MyVideo", frame);

        if (cv::waitKey(30) == 27)
        {
           break;
        }
    }

    cv::destroyAllWindows();
    return 0;
}

