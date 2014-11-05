#ifndef CAMERA_H
#define CAMERA_H

struct camera
{
    camera(float horizontalLimit = 60.0f, float verticalLimit = 60.0f);
    ~camera();

    void rotateTo(float horizontalAngle, float verticalAngle);
    void apply();

private:
    float horizontalAngle_;
    float verticalAngle_;
    float horizontalLimit_;
    float verticalLimit_;
};

#endif
