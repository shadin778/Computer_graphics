#include <windows.h>
#include <GL/glut.h>
#include <cmath>

// Draw a night-time background (dark sky and ground)
void drawBackground() {
    glClearColor(0.1, 0.1, 0.2, 1.0); // Dark blue sky for night
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(34, 34, 34); // Dark ground for night
    glBegin(GL_POLYGON);
    glVertex2f(-4.0, -1.0);
    glVertex2f(4.0, -1.0);
    glVertex2f(4.0, 1.0);
    glVertex2f(-4.0, 1.0);
    glEnd();
}

// Draw a circle for tree leaves
void drawCircle(GLfloat cx, GLfloat cy, GLfloat r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Draw the 5-story building with windows
void drawBuilding() {
    glColor3ub(46, 128, 202); // Light building color
    glBegin(GL_POLYGON);
    glVertex2f(-1.5f, -1.0f);
    glVertex2f(1.5f, -1.0f);
    glVertex2f(1.5f, 7.0f);  // 5 stories building
    glVertex2f(-1.5f, 7.0f);
    glEnd();

    // Windows (5 floors of windows with dim light)
    glColor3ub(173, 216, 230); // Soft light blue for night windows
    for (float y = 1.0f; y <= 5.5f; y += 1.2f) {
        for (float x = -1.2f; x <= 1.0f; x += 1.2f) {
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + 0.5f, y);
            glVertex2f(x + 0.5f, y + 0.6f);
            glVertex2f(x, y + 0.6f);
            glEnd();
        }
    }
}

// Draw the tree with circular leaves behind the building
void drawTree() {
    // Tree trunk (placed behind the building)
    glColor3ub(139, 69, 19); // Darker trunk color for night
    glBegin(GL_POLYGON);
    glVertex2f(-2.0, -1.0);
    glVertex2f(-1.7, -1.0);
    glVertex2f(-1.7, 3.5);  // Taller trunk
    glVertex2f(-2.0, 3.5);  // Taller trunk
    glEnd();

    // Tree leaves (circle-like foliage)
    glColor3ub(0, 153, 0); // Dark green for leaves at night
    drawCircle(-2.0, 4.5, 1.5, 50);
    drawCircle(-1.5, 5.5, 1.2, 50);
    drawCircle(-2.5, 5.5, 1.2, 50);
    drawCircle(-2.0, 6.5, 1.0, 50);
    drawCircle(-1.5, 6.5, 1.0, 50);
}

// Draw the lamppost beside the bench with night-time lighting
void drawLamppost() {
    glColor3f(0.6, 0.6, 0.6); // Lamppost color
    glBegin(GL_QUADS);
    glVertex2f(1.7, 0.0);
    glVertex2f(1.8, 0.0);
    glVertex2f(1.8, 4.5);
    glVertex2f(1.7, 4.5);
    glEnd();

    glColor3f(0.6, 0.6, 0.6); // Top of lamppost
    glBegin(GL_QUADS);
    glVertex2f(1.5, 4.5);
    glVertex2f(2.0, 4.5);
    glVertex2f(2.0, 4.3);
    glVertex2f(1.5, 4.3);
    glEnd();

    // Light (circular) with bright yellow for night-time glow
    glColor3f(1.0, 1.0, 0.0); // Yellow light
    float radius = 0.3;
    int num_segments = 30;
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(num_segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(1.85f + x, 4.3f + y);
    }
    glEnd();
}

// Draw the bench on the right side of the scene
void drawBench() {
    glColor3f(0.6f, 0.6f, 0.6f); // Bench seat color
    glBegin(GL_QUADS);
    glVertex2f(0.5, -0.8);  // Moved to the right
    glVertex2f(3.5, -0.8);  // Moved to the right
    glVertex2f(3.5, -1.0);  // Moved to the right
    glVertex2f(0.5, -1.0);  // Moved to the right
    glEnd();

    glColor3f(0.4f, 0.4f, 0.4f); // Bench legs color
    glBegin(GL_QUADS);
    glVertex2f(0.6, -1.0);  // Left leg
    glVertex2f(0.7, -1.0);  // Left leg
    glVertex2f(0.7, -1.3);  // Left leg
    glVertex2f(0.6, -1.3);  // Left leg
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(3.4, -1.0);  // Right leg
    glVertex2f(3.5, -1.0);  // Right leg
    glVertex2f(3.5, -1.3);  // Right leg
    glVertex2f(3.4, -1.3);  // Right leg
    glEnd();
}

void display() {
    drawBackground();   // Dark sky and ground for night-time
    drawBuilding();     // Building with dimly lit windows
    drawTree();         // Tree with circular leaves behind the building
    drawLamppost();     // Lamppost with lighting
    drawBench();        // Bench moved to the right side
    glFlush();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-4.0, 4.0, -2.0, 8.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Night Scene");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
