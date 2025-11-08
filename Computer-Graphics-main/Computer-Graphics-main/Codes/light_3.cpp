




#include<windows.h>
#include<gl/glut.h>


void display();


void DrawSphere();


void PointLight(const float x, const float y, const float z,  const float amb, const float diff, const float spec);

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



  PointLight(0,0,1, 0, 1, 1);

  glutMainLoop();

  return 0;
}



void PointLight(const float x, const float y, const float z, const float amb, const float diff, const float spec)
{
  glEnable(GL_LIGHTING);


  GLfloat light_ambient[] = { amb,amb,amb, 1.0 };
  //GLfloat light_diffuse[] = {diff, diff, diff, 1.0 };
  //GLfloat light_specular[] = {spec, spec, spec, 1.0 };

  GLfloat light_position[] = {-0.9,.9,0, 0.0 };

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  //glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHT0); //enable the light after setting the properties

}

void DrawSphere()
{
  glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
  glEnable ( GL_COLOR_MATERIAL ) ;
  glColor4f(1.0f, 0.0f, 0.0f, 0.0f);



  GLUquadricObj *quadratic;
  quadratic = gluNewQuadric();
  gluQuadricNormals(quadratic, GLU_SMOOTH);
  gluSphere(quadratic, 1, 30, 30);



}



void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  DrawSphere();


  glutSwapBuffers();//lutSwapBuffers swaps the buffers of the current window if double buffered. Buffer Objects are OpenGL Objects that store an array of unformatted memory allocated by the OpenGL context (AKA the GPU). These can be used to store vertex data, pixel data retrieved from images or the framebuffer, and a variety of other things
}








https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluSphere.xml
https://www.khronos.org/opengl/wiki/Depth_Test