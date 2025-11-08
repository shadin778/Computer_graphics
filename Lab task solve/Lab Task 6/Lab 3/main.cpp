#include <windows.h>
#include <GL/glut.h>

struct Object {
    float x, y;
    float dx, dy;
    int type; // 0: rectangle, 1: triangle, 2: star, 3: diamond
};

Object objects[4] = {
    {-0.8f,  0.6f,  0.01f,  0.0f, 0},  // Rectangle → right
    { 0.8f,  0.4f, -0.01f,  0.0f, 1},  // Triangle ← left
    {-0.4f, -0.8f,  0.0f,  0.01f, 2},  // Star ↑ up
    { 0.4f,  0.8f,  0.0f, -0.01f, 3}   // Diamond ↓ down
};

void drawRectangle(float x, float y) {
    glBegin(GL_QUADS);
        glVertex2f(x - 0.05f, y - 0.03f);
        glVertex2f(x + 0.05f, y - 0.03f);
        glVertex2f(x + 0.05f, y + 0.03f);
        glVertex2f(x - 0.05f, y + 0.03f);
    glEnd();
}

void drawTriangle(float x, float y) {
    glBegin(GL_TRIANGLES);
        glVertex2f(x, y + 0.05f);
        glVertex2f(x - 0.05f, y - 0.05f);
        glVertex2f(x + 0.05f, y - 0.05f);
    glEnd();
}

void drawStar(float x, float y) {
    glBegin(GL_LINES);
        glVertex2f(x - 0.05f, y - 0.05f);
        glVertex2f(x + 0.05f, y + 0.05f);

        glVertex2f(x + 0.05f, y - 0.05f);
        glVertex2f(x - 0.05f, y + 0.05f);
    glEnd();
}

void drawDiamond(float x, float y) {
    glBegin(GL_POLYGON);
        glVertex2f(x, y + 0.05f);
        glVertex2f(x + 0.04f, y);
        glVertex2f(x, y - 0.05f);
        glVertex2f(x - 0.04f, y);
    glEnd();
}

void drawObject(Object& obj) {
    switch (obj.type) {
        case 0:
            glColor3f(0.2f, 0.6f, 1.0f); // Blue
            drawRectangle(obj.x, obj.y);
            break;
        case 1:
            glColor3f(1.0f, 0.4f, 0.2f); // Orange
            drawTriangle(obj.x, obj.y);
            break;
        case 2:
            glColor3f(0.8f, 1.0f, 0.1f); // Yellow-green
            drawStar(obj.x, obj.y);
            break;
        case 3:
            glColor3f(0.7f, 0.2f, 1.0f); // Purple
            drawDiamond(obj.x, obj.y);
            break;
    }
}

void update(int value) {
    for (int i = 0; i < 4; ++i) {
        objects[i].x += objects[i].dx;
        objects[i].y += objects[i].dy;

        // Wrap-around
        if (objects[i].x > 1.1f) objects[i].x = -1.1f;
        if (objects[i].x < -1.1f) objects[i].x = 1.1f;
        if (objects[i].y > 1.1f) objects[i].y = -1.1f;
        if (objects[i].y < -1.1f) objects[i].y = 1.1f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);  // ~60 FPS
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < 4; ++i) {
        drawObject(objects[i]);
    }

    glFlush();
}

void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Four Different Objects Moving");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
