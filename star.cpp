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
#include "star.h"
#include "coord.h"
#include "globals.h"
using namespace std;

STAR::STAR(WORLD& world_a,int x_a,int y_a,int xvel_a,int yvel_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  hostile=0;
  layer=4;
  starSpeed=20+rand()%40;
}

void STAR::render()
{
  glPushMatrix();
  glTranslatef(x,y,0);
  glBegin(GL_QUADS);
  /*
  if(exist)
    {
      glColor3f(0.5f,0.5f,0.5f);//888888
    }
  else
    {
      glColor3f(1.0f,0.0f,1.0f);//ff00ff
    }
  
  glVertex3f(0.0f,0.0f,0.0f);
  glVertex3f(0.0f,0.1f,0.0f);
  glVertex3f(0.1f,0.1f,0.0f);
  glVertex3f(0.05f,0.0f,0.0f);
  */
  //main body
  glColor3f(1.0f,1.0f,1.0f);//FFFFFF
  glVertex3f(-1.0f,-1.0f,0.0f);
  glVertex3f(-1.0f,1.0f,0.0f);
  glVertex3f(1.0f,1.0f,0.0f);
  glVertex3f(1.0f,-1.0f,0.0f);
  
  glEnd();
  glPopMatrix();

  //OLD CLI RENDER
  /*
  cout<<"id: "<<id<<"\t";
  cout<<"x:"<<x<<"\t";
  cout<<"y:"<<y<<"\t";
  cout<<"xvel:"<<xvel<<"\t";
  cout<<"yvel:"<<yvel<<"\t";
  if(!exist)
    {
      cout<<"DESTROYED";
    }
  cout<<endl;
  */
}

bool STAR::logic(int step)
{
  switch(step)
    {
    case 0:
      xvel=-starSpeed*cos((float)globalFrame/300);
      yvel=starSpeed*sin((float)globalFrame/300);
      x+=xvel;
      if(x<0)
	{
	  x+=screen.w;
	}
      if(x>screen.w)
	{
	  x-=screen.w;
	}
      y+=yvel;
      if(y<0)
	{
	  y+=screen.h;
	}
      if(y>screen.h)
	{
	  y-=screen.h;
	}
      break;
    case 1:
      break;
    default:
      return true;
      break;
    }
  return false;
}
