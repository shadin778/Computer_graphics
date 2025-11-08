#include <GL/glut.h>
#include <cmath>

// Car properties
float carX = -8.0f; // Start from left
float carSpeed = 0.05f;
float wheelAngle = 0.0f;
bool moveRight = true;

void drawWheel(float x, float y) {
    // Wheel rim
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x + 0.3f * cos(angle), y + 0.3f * sin(angle));
    }
    glEnd();

    // Rotating spokes
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(wheelAngle, 0.0f, 0.0f, 1.0f);
    for(int i = 0; i < 4; i++) {
        glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.3f * cos(i * 90 * 3.14159f / 180.0f),
                  0.3f * sin(i * 90 * 3.14159f / 180.0f));
        glEnd();
    }
    glPopMatrix();
}

void drawCar() {
    // Car body
    glColor3f(0.8f, 0.2f, 0.2f); // Red color
    glBegin(GL_POLYGON);
        glVertex2f(carX - 1.5f, 0.0f);
        glVertex2f(carX + 1.5f, 0.0f);
        glVertex2f(carX + 1.5f, 0.8f);
        glVertex2f(carX - 1.5f, 0.8f);
    glEnd();

    // Car top
    glBegin(GL_POLYGON);
    for(int i = 0; i < 180; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(carX + 1.0f * cos(angle), 0.8f + 0.5f * sin(angle));
    }
    glEnd();

    // Windows
    glColor3f(0.7f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(carX - 1.0f, 0.2f);
        glVertex2f(carX + 1.0f, 0.2f);
        glVertex2f(carX + 0.8f, 0.7f);
        glVertex2f(carX - 0.8f, 0.7f);
    glEnd();

    // Wheels
    drawWheel(carX - 1.0f, 0.0f);
    drawWheel(carX + 1.0f, 0.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);


    glEnd();

    drawCar();

    glutSwapBuffers();
}

void update(int value) {
    // Move car straight only
    if(moveRight) {
        carX += carSpeed;
        if(carX > 10.0f) {
            carX = -10.0f; // Reset to left when exits right
        }
    }

    // Rotate wheels forward only
    wheelAngle += carSpeed * 50;
    if(wheelAngle > 360.0f) wheelAngle -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10.0, 10.0, -5.0, 5.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 400);
    glutCreateWindow("Straight Moving Car");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();

    return 0;
}
