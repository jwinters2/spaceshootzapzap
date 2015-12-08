#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <GL/glut.h>
#include "object.h"
//#include "graphics.h"
#include "world.h"
#include "person.h"
//#include "graphics.h"
using namespace std;

void handleKeypress(unsigned char,int,int);
void initRendering();
void handleResize(int,int);
void render();
void update(int);

WORLD new_world;
int global_frame=0;

int main(int argc, char** argv)
{
  //WORLD new_world;
  int qwerty=100;
  srand(time(NULL));

  
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600,600);

  glutCreateWindow("AAAA");
  initRendering();

  glutDisplayFunc(render);
  glutKeyboardFunc(handleKeypress);
  glutReshapeFunc(handleResize);
  

  GLint iViewport[4];
  glGetIntegerv( GL_VIEWPORT, iViewport );
  glMatrixMode( GL_PROJECTION );
  glPushMatrix();
  glLoadIdentity();
  glOrtho( iViewport[0], iViewport[0]+iViewport[2],
	   iViewport[1]+iViewport[3], iViewport[1], -1, 1 );
  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  glLoadIdentity();
  glPushAttrib( GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT );
  glDisable( GL_DEPTH_TEST );
  glDisable( GL_LIGHTING );
  
  //WORLD new_world;
  vector<OBJECT*> objects;
  for(int index=0;index<50;index++)
    {
      //objects.push_back(new OBJECT(new_world,rand()%41,rand()%41,rand()%3-1,rand()%3-1));
      objects.push_back(new PERSON(new_world,rand()%41,rand()%41,0,0,index+20));
    }
  /*
  while(true)
    {
      new_world.gamelogic();
      new_world.render();
      usleep(250000);
    }*/
  
  glutTimerFunc(250,update,0);
  glutMainLoop();
  

    //OBJECT obj(new_world,5,5,0,0);
  /* OLD CLI RENDERER
  cout<<new_world.printx()<<endl;
  new_world.render();
  for(int frame=1;frame<300;frame++)
    {
      new_world.gamelogic();
      new_world.render(frame);
    }
  */
  glPopAttrib();
  glMatrixMode( GL_PROJECTION );
  glPopMatrix();
  glMatrixMode( GL_MODELVIEW );
  glPopMatrix();
  return 0;
}

void handleKeypress(unsigned char key,int x,int y)
{
  switch(key)
    {
    case 27:
      exit(0);
    }
}

void initRendering()
{
  glEnable(GL_DEPTH_TEST);
}

void handleResize(int w,int h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0,(double)w/(double)h,1.0,200.0);
}

void render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  new_world.render(global_frame);
  
  glutSwapBuffers();
}

void update(int value)
{
  new_world.gamelogic();
  global_frame++;
  glutPostRedisplay();
  glutTimerFunc(250,update,0);
}
