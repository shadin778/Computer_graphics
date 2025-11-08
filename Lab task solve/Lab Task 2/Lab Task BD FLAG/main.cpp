#include <GL/glut.h>
#include <cmath>

// Define flag dimensions
float flagWidth = 0.6f;
float flagHeight = 0.4f;
float circleRadius = 0.085f;  // Adjusted for proper scaling
float circleCenterX = 0.3f;   // Center of the circle
float circleCenterY = 0.2f;   // Center of the circle

// Function to draw a filled circle
void drawCircle(float cx, float cy, float r, int numSegments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * 3.1416f * float(i) / float(numSegments);
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the green rectangle (flag background)
    glColor3f(0.0f, 0.42f, 0.24f);  // Dark green color
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(flagWidth, 0.0f);
    glVertex2f(flagWidth, flagHeight);
    glVertex2f(0.0f, flagHeight);
    glEnd();

    // Draw the red circle
    glColor3f(0.84f, 0.0f, 0.0f);  // Red color
    drawCircle(circleCenterX, circleCenterY, circleRadius, 100);

    glFlush();
}

// Initialize OpenGL
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 0.6, 0.0, 0.4);  // Set the coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 250);
    glutCreateWindow("Bangladesh Flag");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
