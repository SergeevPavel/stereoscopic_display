#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "common_header.h"

struct controller{
    controller();
    ~controller();

    float getAlpha();
    float getBeta();
    void update();

private:
    float alpha_;
    float beta_;

    int frameCenterX_;
    int frameCenterY_;

    int calibratedMaxSize_;
    int calibratedMinSize_;

    int monitorDistance_;

    double maxAngleAlpha_;
    double maxAngleBeta_;

    cv::CascadeClassifier cascade_;

    cv::Size size_;

    cv::VideoCapture cap_;
};

#endif
