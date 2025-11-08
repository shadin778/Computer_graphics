#include <windows.h>
#include <GL/glut.h>


void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // XY Axis
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);

    // X-Axis
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);

    // Y-Axis
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();

    //  2nd Shape: Square

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2f(-0.8f, 0.8f);  // Bottom-left
    glVertex2f(-0.2f, 0.8f);  // Bottom-right
    glVertex2f(-0.2f, 0.2f);  // Top-right
    glVertex2f(-0.8f, 0.2f);  // Top-left
    glEnd();

        //3rd Shape: TRIANGLES

    glBegin(GL_TRIANGLES);
    glColor3f(0.56f, 0.0f, 1.0f); // Violet
	glVertex2f(-0.2f, -0.2f);    // x, y
	glVertex2f(-0.804f, -0.501f);
	glVertex2f(-0.2f, -0.8f);

	glEnd();


	//  4th Shape: TRIANGLES

	glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
 	glVertex2f(0.8f, -0.8f);    // x, y
	glVertex2f(0.2f, -0.8f);
	glVertex2f(0.510f, -0.406f);

	glEnd();


	//  1st Shape: Arrow
	glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex2f(0.8f, 0.4f);  //P
    glVertex2f(0.6f, 0.2f); //Q
    glVertex2f(0.6f, 0.3f); //R
    glVertex2f(0.2f, 0.3f); //S
    glVertex2f(0.2f, 0.5f); //V
    glVertex2f(0.6f, 0.5f); //U
    glVertex2f(0.6f, 0.6f); //T

    glEnd();





    glFlush();  // Render now
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Vertex, Primitive & Color");
    glutInitWindowSize(320, 320);
    glutDisplayFunc(display);
    initGL();
    glutMainLoop();
    return 0;
}
