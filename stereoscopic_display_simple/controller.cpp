#include "controller.h"
using namespace std;

controller::controller()
    :   cap_(0)
{
    const int heightStable = 300;
    if (!cap_.isOpened())
    {
        cout << "Fail" << endl;
        exit(-1);
    }

    string name("haarcascade_frontalface_default.xml");
    cascade_.load(name);
    if (cascade_.empty())
    {
        cout << "FUCKING ERROR" << endl;
        exit(1);
    }
    cv::namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);

    size_.height = heightStable;
    size_.width = cap_.get(CV_CAP_PROP_FRAME_WIDTH) * heightStable / cap_.get(CV_CAP_PROP_FRAME_HEIGHT);


    frameCenterX_ = size_.width / 2;
    frameCenterY_ = size_.height / 2;

    calibratedMaxSize_ = (double) size_.height / 2; //Дичайший хардкод
    calibratedMinSize_ = (double) size_.height / 3.7;

    monitorDistance_ = 100;    //Нужно подбирать

    maxAngleAlpha_ = (double)size_.width / 2 / monitorDistance_;
    maxAngleBeta_ = (double)size_.height / 2 / monitorDistance_;
}


controller::~controller()
{
    cv::destroyAllWindows();
}

void controller::update()
{
    bool isCalibrated;

    cv::Mat frame;
    cv::Mat grayFrame;
    bool bSuccess = cap_.read(frame);

    if (!bSuccess)
    {
        cout << "Cannot read a frame from video stream" << endl;
        return;
    }

    cv::resize(frame, frame, size_);
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(grayFrame, grayFrame);
    vector<cv::Rect> faces;

    cascade_.detectMultiScale(grayFrame, faces, 1.1, 3, cv::CASCADE_SCALE_IMAGE);

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

    int centerX = 0;
    int centerY = 0;

    if (!faces.empty())
    {
        cv::Point pt1(faces[biggestIndex].x, faces[biggestIndex].y);
        cv::Point pt2((faces[biggestIndex].x + faces[biggestIndex].height), (faces[biggestIndex].y + faces[biggestIndex].width));
        centerX = (pt1.x + pt2.x) / 2;
        centerY = (pt1.y + pt2.y) / 2;
        int width = pt2.x - pt1.x;

        if (width > calibratedMaxSize_)
            isCalibrated = false;
        else if (width < calibratedMinSize_)
            isCalibrated = false;
        else
            isCalibrated = true;
        if (isCalibrated)
        {
            alpha_ = (double)(centerX - frameCenterX_) / monitorDistance_ / maxAngleAlpha_;
            beta_ = (double)(centerY - frameCenterY_) / monitorDistance_ / maxAngleBeta_;
        }
        cv::rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0), 2, 8, 0);
    }
    else
    {
        isCalibrated = false;
    }

    //где-то отсюда нужно забирать углы.

    if (isCalibrated)
    {
        if (centerX || centerY)
        {
            cout << alpha_ << " " << beta_ << endl;
        }
        else
        {
            cout << "Face lost..." << endl;
        }
    }
    const string text = isCalibrated ? "CALIBRATED" : "NOT CALIBRATED";
    cv::putText(frame, text, cvPoint(size_.width / 4, 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);

    imshow("MyVideo", frame);
}

float controller::getAlpha()
{
    return alpha_;
}

float controller::getBeta()
{
    return beta_;
}

