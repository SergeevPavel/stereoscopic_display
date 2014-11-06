#include <memory>
#include <thread>

#include <opencv2/opencv.hpp>

#include "Controller.h"


std::shared_ptr<cv::VideoCapture> camera;
std::shared_ptr<std::thread> updaterThread;
std::shared_ptr<cv::CascadeClassifier> cascade;
bool updateIsRunning;
float verticalAngle;
float horizontalAngle;


cv::Size size;

bool isCalibrated = false;
const int heightStable = 240;

int frameCenterX = 0;
int frameCenterY = 0;

int calibratedMaxSize = 0;
int calibratedMinSize = 0;

const int monitorDistance = 200;    //Нужно подбирать

float maxAngleAlpha = 0;
float maxAngleBeta = 0;

void angleUpdater()
{
	float alpha = 0;
	float beta = 0;
	cv::Mat frame;
	cv::Mat grayFrame;
	while (updateIsRunning)
	{
		camera->read(frame);
        bool bSuccess = camera->read(frame);

        if (!bSuccess)
        {
            continue;
        }

        cv::resize(frame, frame, size);
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(grayFrame, grayFrame);
        std::vector<cv::Rect> faces;

        cascade->detectMultiScale(grayFrame, faces, 1.1, 3, cv::CASCADE_SCALE_IMAGE);

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

        const std::string text = isCalibrated ? "CALIBRATED" : "NOT CALIBRATED";
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

            alpha = (double)(centerX - frameCenterX) / monitorDistance / maxAngleAlpha;
            beta = (double)(centerY - frameCenterY) / monitorDistance / maxAngleBeta;

            cv::rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0), 2, 8, 0);
        }

        //где-то отсюда нужно забирать углы.
		if (isCalibrated)
		{
			horizontalAngle = alpha;
			verticalAngle = beta;
		}
		imshow("FaceWindow", frame);
	}
}


extern "C"
{
	int initController()
	{
		camera = std::make_shared<cv::VideoCapture>(0);
		if (!camera->isOpened())
		{
			return -1;
		}
		cv::namedWindow("FaceWindow", CV_WINDOW_AUTOSIZE);
		cascade = std::make_shared<cv::CascadeClassifier>();
		cascade->load("haarcascade_frontalface_default.xml");
		size.height = heightStable;
		size.width = camera->get(CV_CAP_PROP_FRAME_WIDTH) * heightStable / camera->get(CV_CAP_PROP_FRAME_HEIGHT);

		calibratedMaxSize = (float)size.height / 2.5;
		calibratedMinSize = (float)size.height / 3.2;
		
		frameCenterX = size.width / 2;
		frameCenterY = size.height / 2;

		maxAngleAlpha = (float)size.width / 2 / monitorDistance;
		maxAngleBeta = (float)size.height / 2 / monitorDistance;

		updateIsRunning = true;
		updaterThread = std::make_shared<std::thread>(angleUpdater);
		return 0;
	}

	int deinitController()
	{
		updateIsRunning = false;
		updaterThread->join();
		cv::destroyAllWindows();
		return 0;
	}

	float getVerticalAngle()
	{
		return verticalAngle;
	}

	float getHorizontalAngle()
	{
		return horizontalAngle;
	}
}