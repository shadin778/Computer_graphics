//Norway
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
    glColor3f(0.729f,0.047f,0.184f);
    glVertex2f(0,0);
    glVertex2f(880,0);
    glVertex2f(880,640);
    glVertex2f(0,640);

    glEnd();


    glBegin(GL_QUADS);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(0,240);
    glVertex2f(880,240);
    glVertex2f(880,400);
    glVertex2f(0,400);




    glEnd();


     glBegin(GL_QUADS);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(240,0);
    glVertex2f(400,0);
    glVertex2f(400,640);
    glVertex2f(240,640);




    glEnd();


     glBegin(GL_QUADS);
    glColor3f(0.0f,0.125f,0.356f);
    glVertex2f(280,0);
    glVertex2f(360,0);
    glVertex2f(360,640);
    glVertex2f(280,640);




    glEnd();


     glBegin(GL_QUADS);
    glColor3f(0.0f,0.125f,0.356f);
    glVertex2f(0,280);
    glVertex2f(880,280);
    glVertex2f(880,360);
    glVertex2f(0,360);




    glEnd();


    glFlush();

}
void myInit (void){
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    //glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 880.0, 0.0, 640.0);
}
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (400, 250);
    glutInitWindowPosition (80, 30);
    glutCreateWindow ("my first attempt");
    glutDisplayFunc(display);
    myInit ();
    glutMainLoop();
}
