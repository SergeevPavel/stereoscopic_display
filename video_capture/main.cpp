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
    cv::CascadeClassifier cascade("haarcascade_frontalface_default.xml");

    cv::namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);

    while (1)
    {
       cv::Mat frame;
       cascade.detectMultiScale(frame, );
       bool bSuccess = cap.read(frame);

        if (!bSuccess)
       {
            cout << "Cannot read a frame from video stream" << endl;
            break;
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

