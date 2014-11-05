#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main()
{
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "Fail" << endl;
        exit(-1);
    }
    double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    cout << "Frame size : " << dWidth << " x " << dHeight << endl;
    cv::CascadeClassifier cascade;
    string name("haarcascade_frontalface_default.xml");
    cascade.load("haarcascade_frontalface_default.xml");
    if (cascade.empty())
    {
        cout << "FUCKING ERROR" << endl;
        exit(1);
    }
    cv::namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);

    while (1)
    {
        cv::Mat frame;
        cv::Mat grayFrame;
        bool bSuccess = cap.read(frame);

        if (!bSuccess)
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(grayFrame, grayFrame);
        vector<cv::Rect> faces;
        cascade.detectMultiScale(grayFrame, faces, 1.1, 3, cv::CASCADE_SCALE_IMAGE);

        size_t current_index = 0;
        int current_area = 0;

        size_t biggest_index = 0;
        int biggest_area = 0;

        for (current_index = 0; current_index < faces.size(); ++current_index)

        {
            current_area = faces[current_index].width * faces[current_index].height;

            if (current_area > biggest_area)
            {
                biggest_index = current_index;
                biggest_area = current_area;
            }
        }

        if (!faces.empty())
        {
            cv::Point pt1(faces[biggest_index].x, faces[biggest_index].y);
            cv::Point pt2((faces[biggest_index].x + faces[biggest_index].height), (faces[biggest_index].y + faces[biggest_index].width));
            cv::rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0), 2, 8, 0);
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

