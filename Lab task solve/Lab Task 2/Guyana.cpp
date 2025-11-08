//Guyana
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

void display()
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(1);

    glBegin(GL_QUADS);
    glColor3f(0.0f,0.592f,0.22f);
    glVertex2f(0,0);
    glVertex2f(400,0);
    glVertex2f(480,240);
    glVertex2f(0,240);
    glEnd();


     glBegin(GL_TRIANGLES);
    glColor3f(1,1,1);
    glVertex2f(0,0);
    glVertex2f(400,120);
    glVertex2f(0,240);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1,0.82,0);
    glVertex2f(0,15);
    glVertex2f(360,120);
    glVertex2f(0,225);

    glEnd();


        glBegin(GL_TRIANGLES);
    glColor3f(0,0.0,0);
    glVertex2f(0,0);
    glVertex2f(200,120);
    glVertex2f(0,240);

    glEnd();


        glBegin(GL_TRIANGLES);
    glColor3f(0.93,0.2,0.25);
    glVertex2f(0,15);
    glVertex2f(160,120);
    glVertex2f(0,225);

    glEnd();










    glFlush();

}
void myInit (void){
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    //glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 240.0);
}
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (400, 240);
    glutInitWindowPosition (80, 30);
    glutCreateWindow ("my first attempt");
    glutDisplayFunc(display);
    myInit ();
    glutMainLoop();
}
