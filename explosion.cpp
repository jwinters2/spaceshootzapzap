#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "person.h"
#include "object.h"
#include "world.h"
#include "explosion.h"
#include "coord.h"
#include "globals.h"
using namespace std;

const double pi=3.14159265358979323;

EXPLOSION::EXPLOSION(WORLD& world_a,int x_a,int y_a,float red_a,float green_a,float blue_a)
  :OBJECT(world_a,x_a,y_a,0,0)
{
  red=red_a;
  green=green_a;
  blue=blue_a;
  hostile=0;
}

void EXPLOSION::render()
{
  glPushMatrix();
  glTranslatef(x,y,0);
  //glRotatef(getDir(xvel,yvel)+180,0,0,1);
  glScalef((float)age,(float)age,0);
  
  glBegin(GL_TRIANGLE_FAN);
  glColor4f(red,green,blue,0.0f);
  glVertex3f(0.0f,0.0f,0.0f);
  glColor4f(red,green,blue,1.0f-((float)age/30));
  //glColor3f((1+cos(countdown*2*PI/15))/2,0.0f,0.0f);
  //glColor4f(1.0f,0.5f,0.0f,(1+cos((float)jndex+countdown*2*PI/15))/3);
  float spike;
  for(int index=0;index<=12;index++)
    {
      spike=1.5f-(index%2);
      glVertex3f(spike*cos((float)index*pi/6),spike*sin((float)index*pi/6),0.0f);
    }
  glEnd();  
  glPopMatrix();
}

bool EXPLOSION::logic(int step)
{
  switch(step)
    {
    case 0:
      age++;
      break;
    case 1:
      if(age>30)
	{
	  world->deleteobject(id);
	}
      break;
    default:
      return true;
      break;
    }
  return false;
}
