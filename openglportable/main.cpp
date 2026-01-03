















































































/*#include <GL/glut.h>

float zoom =3.0f;
float camera_x=3.0f;
void display()
{ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0,0.0,zoom,
            -0.7,0.6,0.0,
            0.0,1.0,0.0);

    glBegin(GL_TRIANGLES);
      glVertex3f(0.0f,0.3f,0.0f);
      glVertex3f(0.3f,-0.3f,0.0f);
      glVertex3f(-0.3f,-0.3f,0.0f);

      glEnd();
      glutSwapBuffers();


}
 void reshape (int w,int h)
 {
     glViewport(0,0,w,h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(60.0,(float)w/h,0.1,100.0);

 }

 void keyboard(unsigned char key,int x, int y)
 { if (key=='w')
 {zoom-=0.1;}
 if(key=='s')
 {
     zoom+=0.1;
 }
 if(key=='a')
 {
     camera_x = camera_x -0.1;
 }

 if(key=='d')
 {
         camera_x = camera_x +0.1;

 }


 glutPostRedisplay();
 }
/*void display()
{

     glClear(GL_COLOR_BUFFER_BIT);

 glPointSize(40);

 glBegin(GL_POINTS);
 glColor3f(1,0,0);//blank box gular red color e change korar jonno

 glVertex2f(0,0);//centre 0,0

 glColor3f(0,1,0);// green color
 glVertex2f(-0.85,-0.85);
 glVertex2f(0.85,0.85);
 glVertex2f(-0.85,0.85);
 glVertex2f(0.85,-0.85);
    /*glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(40);

    glBegin(GL_POINTS);
    glColor3f(1,0,0);//blank box gular red color e change korar jonno

    glVertex2f(0,0);//centre 0,0

    glColor3f(0,1,0);// green color
    glVertex2f(-0.85,-0.85);
    glVertex2f(0.85,0.85);
    glVertex2f(-0.85,0.85);
    glVertex2f(0.85,-0.85);

    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(20);


 glBegin(GL_TRIANGLES);

glBegin(GL_POLYGON);


    /*glBegin(GL_LINES);
    glBegin(GL_TRIANGLES);

    glVertex2f(-0.95,-0.95);
    glVertex2f(0.95,0.95);
    glColor3f(1,0,0);*/

   /* glColor3f(1,0,0);
    glVertex2f(0.0, 0.8);
    glVertex2f(0.8, 0.0);

     glColor3f(0,1,0);
    glVertex2f(0.8, 0.0);
    glVertex2f(-0.8, 0.0);

    glColor3f(0,0,1);
    glVertex2f(-0.8, 0.0);
    glVertex2f(0.0, 0.8);

      glColor3f(0,1,0);
    glVertex2f(0.8, 0.8);
    glVertex2f(-0.8, 0.8);

     glColor3f(1,0,0);
    glVertex2f(-0.8, 0.8);
    glVertex2f(-0.8, -0.8);

    glColor3f(0,0,1);
    glVertex2f(-0.8, -0.8);
    glVertex2f(0.8, -0.8);


     glColor3f(1,0,1);
    glVertex2f(0.8, -0.8);
    glVertex2f(0.8, 0.8);

//triangle:
    glColor3f(1,0,0);
    glVertex2f(0, 0.8);
    //glColor3f(0,1,0);
    glVertex2f(-0.8, 0);
   // glColor3f(1,0,0);
    glVertex2f(0.8, 0);
    // glColor3f(1,0,0);

glEnd();
glBegin(GL_POLYGON);


    glColor3f(0,0,1);
    glVertex2f(-0.8, 0);
    //glColor3f(0,1,0);
    glVertex2f(-0.8, -0.8);
    //glColor3f(1,0,0);
    glVertex2f(0.8, -0.8);
    //glColor3f(0,0,1);
    glVertex2f(0.8, 0);


     glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL ");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}*/


int main() {
    return 0;
}
