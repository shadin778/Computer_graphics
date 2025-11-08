#include<windows.h>
#include<gl/glut.h>



void display();

void AmbientLighting();

int WindowHeight = 1000;
int WindowWidth = 1000;

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(WindowWidth, WindowHeight);
  glutInitWindowPosition(0, 0);

  glutCreateWindow("Lighting Example");

  glutDisplayFunc(display);

  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
 glEnable(GL_NORMALIZE);

AmbientLighting();

  glutMainLoop();

  return 0;
}

void AmbientLighting()
{
  glEnable(GL_LIGHTING);//Enable Light Effect

  GLfloat global_ambient[] = {0.9,0.0,0.0, 0.1};//ambient RGBA intensity of light
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);//A lighting model parameter.
}



void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glEnable ( GL_COLOR_MATERIAL ) ;
  glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
  glBegin(GL_TRIANGLES);
  glVertex2f(0.0f,0.0f);
  glVertex2f(0.4f,0.0f);
  glVertex2f(0.2f,0.2f);
  glEnd();


  glutSwapBuffers();
  glFlush();
}

