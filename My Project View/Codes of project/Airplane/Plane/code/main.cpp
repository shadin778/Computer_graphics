#include <GL/glut.h>

float airplaneX = -1.2f;
float rotationAngle = 0.0f;

void update(int value) {
    airplaneX += 0.005f;
    if (airplaneX > 1.5f)
        airplaneX = -1.2f;

    rotationAngle += 1.0f;
    if (rotationAngle >= 360.0f)
        rotationAngle -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void drawSky() {
    glBegin(GL_QUADS);
        glColor3f(0.4f, 0.7f, 1.0f); // Sky blue
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();
}

void drawAirplane() {
    glPushMatrix();

    glTranslatef(airplaneX, 0.3f, 0.0f);   // Move position
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis
    glScalef(1.2f, 1.2f, 1.0f); // Scale up a bit

    // Body (fuselage)
    glColor3f(0.8f, 0.0f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.15f, 0.02f);
        glVertex2f(0.18f, 0.02f);
        glVertex2f(0.2f, 0.0f);
        glVertex2f(0.18f, -0.02f);
        glVertex2f(-0.15f, -0.02f);
        glVertex2f(-0.17f, 0.0f);
    glEnd();

    // Cockpit Window
    glColor3f(0.7f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.12f, 0.015f);
        glVertex2f(0.17f, 0.015f);
        glVertex2f(0.18f, 0.0f);
        glVertex2f(0.17f, -0.015f);
        glVertex2f(0.12f, -0.015f);
    glEnd();

    // Main Wing
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.05f, 0.02f);
        glVertex2f(0.02f, 0.10f);
        glVertex2f(0.08f, 0.10f);
        glVertex2f(0.02f, 0.02f);
    glEnd();

    // Left Wing (bottom)
    glBegin(GL_POLYGON);
        glVertex2f(-0.05f, -0.02f);
        glVertex2f(0.02f, -0.10f);
        glVertex2f(0.08f, -0.10f);
        glVertex2f(0.02f, -0.02f);
    glEnd();

    // Tail vertical stabilizer
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.14f, 0.02f);
        glVertex2f(-0.18f, 0.06f);
        glVertex2f(-0.12f, 0.02f);
    glEnd();

    // Tail horizontal stabilizer
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.01f);
        glVertex2f(-0.12f, 0.04f);
        glVertex2f(-0.08f, 0.04f);
        glVertex2f(-0.11f, 0.01f);
    glEnd();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawSky();
    drawAirplane();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // black clear color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rotating Airplane in Sky");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}

