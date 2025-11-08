//Kuwait
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
    glColor3f(0.807f,0.0667f,0.149f);
    glVertex2f(0,0);
    glVertex2f(480,0);
    glVertex2f(480,80);
    glVertex2f(0,80);



    glEnd();



     glBegin(GL_QUADS);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(0,80);
    glVertex2f(480,80);
    glVertex2f(480,160);
    glVertex2f(0,160);



    glEnd();


      glBegin(GL_QUADS);
    glColor3f(0.0f,0.478f,0.239f);
    glVertex2f(0,160);
    glVertex2f(480,160);
    glVertex2f(480,240);
    glVertex2f(0,240);


    glEnd();


     glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(0,0);
    glVertex2f(120,80);
    glVertex2f(120,160);
    glVertex2f(0,240);



    glEnd();


    glFlush();

}
void myInit (void){
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    //glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 480.0, 0.0, 240.0);
}
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (430, 200);
    glutInitWindowPosition (80, 30);
    glutCreateWindow ("my first attempt");
    glutDisplayFunc(display);
    myInit ();
    glutMainLoop();
}
