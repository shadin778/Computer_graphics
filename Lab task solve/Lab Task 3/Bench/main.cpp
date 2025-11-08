#include <windows.h>
#include <GL/glut.h>

// Adjusted Bench Coordinates (More structured)
float seat[] = {2.0, 3.0, 5.0, 3.0, 5.0, 2.7, 2.0, 2.7};  // Seat
float leftLeg[] = {2.3, 2.7, 2.5, 2.7, 2.5, 1.5, 2.3, 1.5}; // Left Leg
float rightLeg[] = {4.5, 2.7, 4.7, 2.7, 4.7, 1.5, 4.5, 1.5}; // Right Leg
float backrest[] = {2.0, 3.5, 5.0, 3.5, 5.0, 3.0, 2.0, 3.0}; // Backrest

void drawQuad(float coords[]) {
    glBegin(GL_QUADS);
    glVertex2f(coords[0], coords[1]);
    glVertex2f(coords[2], coords[3]);
    glVertex2f(coords[4], coords[5]);
    glVertex2f(coords[6], coords[7]);
    glEnd();
}

void drawBench() {
    // Draw the Bench Components
    glColor3f(0.6f, 0.6f, 0.6f); // Grey Seat
    drawQuad(seat);

    glColor3f(0.4f, 0.4f, 0.4f); // Darker Legs
    drawQuad(leftLeg);
    drawQuad(rightLeg);

    glColor3f(0.5f, 0.5f, 0.5f); // Medium Grey Backrest
    drawQuad(backrest);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBench();
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 6.0, 0.0, 6.0); // Proper Coordinate System
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Bench");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glClearColor(1.0, 1.0, 1.0, 1.0); // White Background
    glutMainLoop();
    return 0;
}
