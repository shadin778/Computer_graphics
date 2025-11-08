#include <GL/glut.h>

// Define the flag dimensions
float width = 0.3f;
float height = 0.12f;
int numStripes = 6;

// Rainbow colors (RGB)
float colors[6][3] = {
    {228/255.0f, 3/255.0f, 3/255.0f},   // Red
    {255/255.0f, 140/255.0f, 0/255.0f}, // Orange
    {255/255.0f, 237/255.0f, 0/255.0f}, // Yellow
    {0/255.0f, 128/255.0f, 38/255.0f},  // Green
    {0/255.0f, 77/255.0f, 255/255.0f},  // Blue
    {117/255.0f, 7/255.0f, 135/255.0f}  // Violet
};

// Function to draw a rectangle (stripe)
void drawRectangle(float x, float y, float width, float height, float color[3]) {
    glColor3fv(color);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the flag stripes
    float stripeHeight = height / numStripes;
    for (int i = 0; i < numStripes; i++) {
        float y = i * stripeHeight;
        drawRectangle(0, y, width, stripeHeight, colors[i]);
    }

    // Draw the black border
    glColor3f(0, 0, 0);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0, 0);
    glVertex2f(width, 0);
    glVertex2f(width, height);
    glVertex2f(0, height);
    glEnd();

    glFlush();
}

// Initialize OpenGL
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 0.3, 0.0, 0.12); // Set the coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,300);
    glutCreateWindow("Rainbow Flag");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
