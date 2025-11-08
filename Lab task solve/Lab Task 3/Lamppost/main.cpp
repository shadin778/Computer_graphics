#include <GL/glut.h>
#include <GL/glu.h>

// Function to draw the lamppost
void drawLamppost() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Pole color (Gray)
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_QUADS);
    glVertex2f(2.4, 0.0);
    glVertex2f(2.6, 0.0);
    glVertex2f(2.6, 4.5);
    glVertex2f(2.4, 4.5);
    glEnd();

    // Base color (Dark Gray)
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_QUADS);
    glVertex2f(2.0, -0.2);
    glVertex2f(3.0, -0.2);
    glVertex2f(3.0, 0.0);
    glVertex2f(2.0, 0.0);
    glEnd();

    // Top horizontal bar
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_QUADS);
    glVertex2f(2.0, 4.5);
    glVertex2f(3.8, 4.5);
    glVertex2f(3.8, 4.3);
    glVertex2f(2.0, 4.3);
    glEnd();

    // Lamp light (Circular)
    glColor3f(1.0, 1.0, 0.0); // Yellow color
    glPushMatrix();
    glTranslatef(3.7, 3.9, 0.0); // Positioning the light
    GLUquadric *quad = gluNewQuadric();
    gluDisk(quad, 0.0, 0.3, 50, 1); // Circular light with radius 0.3
    gluDeleteQuadric(quad);
    glPopMatrix();

    glFlush();
}

// Initialize OpenGL settings
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 6.0, -1.0, 6.0); // Adjusted coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lamppost with Circular Light");
    init();
    glutDisplayFunc(drawLamppost);
    glutMainLoop();
    return 0;
}
