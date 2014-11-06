#include "camera.h"
#include "common_header.h"

camera::camera(float horizontalLimit, float verticalLimit)
    :   horizontalLimit_(horizontalLimit)
    ,   verticalLimit_(verticalLimit)
{

}


camera::~camera()
{

}


void camera::rotateTo(float horizontalAngle, float verticalAngle)
{
    horizontalAngle_ = horizontalAngle * horizontalLimit_;
    verticalAngle_   = verticalAngle   * verticalLimit_;
}


void camera::apply()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 60, GLfloat(1.33), 1, 20 );
    // установка вектора обзора
    // (0,0,5) камера; (0,0,0) центр сцены, верхом будет ось Y
//    float g_z = cos(cam.h_angle / 180 * M_PI);
//    std::cerr << g_z << std::endl;
//    float g_x = sin(cam.h_angle / 180 * M_PI);
//    std::cerr << g_x << std::endl;
//    gluLookAt(0, 0, 5, 5 * g_x, 0, 5 - 5 * g_z, 0, 1, 0);
}


