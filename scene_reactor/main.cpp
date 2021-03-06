/* Программа отрисовки вращающегося чайника с одним источником света
компиляция: g++ -o ./имя_готовой_программы ./имя_этого_файла.cpp -lGL -lGLU -lglut
site:  http://flank1er.blogspot.ru
*/

#include "common_header.h"

int angle=0; // угол вращения

bool flag=false; // флаг статуса отрисовки

struct camera{
    float h_angle;
    float v_angle;
    float d_angle;
    camera()
        :   h_angle()
        ,   v_angle()
        ,   d_angle()
    {

    }
};

camera cam;

// подготовка сцены
void init() {
        glClearColor(0.0, 0.0, 0.0, 1.0); // цвет очистки буферов - черный
        glEnable(GL_DEPTH_TEST); // включаем сортировку по глубине

        glShadeModel(GL_SMOOTH); // режим закрашивания: интерполируемые значения

        // ставим источник света
        float lightAmb[4] = {0.0, 0.0, 1.0, 1}; // фоновый цвет синий
        float lightDif[4] = {1.0, 0.0, 0.0, 1}; // отраженный цвет красный
        float lightPos[4] = {0.0, 3.0, 3.0, 1};  // положение в пространстве
        glLightfv (GL_LIGHT0, GL_AMBIENT, lightAmb);
        glLightfv (GL_LIGHT0, GL_DIFFUSE, lightDif);
        glLightfv (GL_LIGHT0, GL_POSITION, lightPos);
        glEnable (GL_LIGHT0 ); // включаем источник света
        glEnable (GL_LIGHTING); // включаем освещение
}

// рисование
void display() {
        flag=true; // мы еще рисуем
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT); // очистка рабочих буферов

        glPushMatrix(); // начинаем матричные преобразования
        glRotatef(angle, 1, 1, 0); // матрица вращения
        glutSolidTeapot(1);       //  наш чайник
        glPopMatrix();          // завершаем матричные преобразования

        glutSwapBuffers();    // выводим на экран
        flag=false;         // все, нарисовали!
}

// перекалибровка при изменении размеров окна
void reshape(int w, int h) {
        // область видимости в соответствии с новыми координатами
        glViewport( 0, 0, (GLsizei)w, (GLsizei)h);
        // загружаем единичные матрицы в стеки MODELVIEW, PROJECTION
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity();
        // установка перспективы: угол обзора 60 градусов, аспект,
        // глубина пространства 20 единиц
        gluPerspective( 60, GLfloat(1.33), 1, 20 );
        // установка вектора обзора
        // (0,0,5) камера; (0,0,0) центр сцены, верхом будет ось Y
        float g_z = cos(cam.h_angle / 180 * M_PI);
        std::cerr << g_z << std::endl;
        float g_x = sin(cam.h_angle / 180 * M_PI);
        std::cerr << g_x << std::endl;
        gluLookAt(0, 0, 5, 5 * g_x, 0, 5 - 5 * g_z, 0, 1, 0);
}



void key(unsigned char key, int  x, int y) {
    std::cerr << (int)key << std::endl;
    // если была нажата клавиша ESC, Q, q, то завершаем программу
    if ( key == 27 || key == 'q' || key == 'Q' ) {
            glutLeaveMainLoop();
    }
    if (key == 97)
    {
        cam.h_angle = ((int)cam.h_angle - 2) % 360;
    }
    if (key == 100)
    {
        cam.h_angle = ((int)cam.h_angle + 2) % 360;
    }
}



void mytime(int value) // таймер
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    // установка перспективы: угол обзора 60 градусов, аспект,
    // глубина пространства 20 единиц
    gluPerspective( 60, GLfloat(1.33), 1, 20 );
    // установка вектора обзора
    // (0,0,5) камера; (0,0,0) центр сцены, верхом будет ось Y
    float g_z = cos(cam.h_angle / 180 * M_PI);
    std::cerr << g_z << std::endl;
    float g_x = sin(cam.h_angle / 180 * M_PI);
    std::cerr << g_x << std::endl;
    gluLookAt(0, 0, 5, 5 * g_x, 0, 5 - 5 * g_z, 0, 1, 0);
    // Если предыдущий кадр все еще рисуется, то ругаемся
    if (!flag) {
            glutPostRedisplay();
    } else {
            std::cerr << "Your system is VERY SLOW!" << std::endl;
    }
    glutTimerFunc(40, mytime, 0); // следующий вызов
}


int main(int argc, char** argv) {
        glutInit (&argc,argv); // инициализация glut
        // будем использовать двойную буферизацию, цветовое пространство RGB,
        // сортировку по глубине aka Z-буфер
        glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
        // размер окна пусть будет 800 на 600
        glutInitWindowSize( 800,600);
        // создаем окно, на выходе получаем идентификатор созданного окна
        int glWin=glutCreateWindow("My program");
        init(); // подготовка к рисованию
        glutDisplayFunc(display); // рисование
        glutReshapeFunc(reshape); // действия при изменении окна
        glutKeyboardFunc(key);   // обработка нажатий клавиш
        // запускаем таймер м периодичностью 40ms т.е. 25 раз в секунду
        glutTimerFunc(40, mytime, 0);
        glutMainLoop(); // главный цикл glut

        return 0;
}
