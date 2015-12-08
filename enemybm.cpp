#define PI 3.14159265658
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "person.h"
#include "object.h"
#include "world.h"
#include "enemybm.h"
#include "coord.h"
#include "globals.h"
using namespace std;

/*ENEMYBM::ENEMYBM(WORLD& world_a,int x_a,int y_a,int xvel_a,int yvel_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  radius=12;
  health=1;
  hostile=1;
}
*/

ENEMYBM::ENEMYBM(WORLD& world_a,float x_a,float y_a,float xvel_a,float yvel_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  type="ENEMYBM";
  radius=9;
  health=1;
  hostile=1;
}

void ENEMYBM::render()
{
  glPushMatrix();
  glTranslatef(x,y,0);
  glRotatef(getDir(xvel,yvel)+180,0,0,1);
  //glScalef(1.0f,1.0f,1.0f);

  glBegin(GL_TRIANGLE_FAN);
  //glColor3f((1+cos(countdown*2*PI/15))/2,0.0f,0.0f);
  glColor3f(1.0f,0.0f,0.0f);
  glVertex3f(0.0f,0.0f,0.0f);
  glColor3f(1.0f,0.3f,0.0f);
  for(int index=0;index<=6;index++)
    {
      glVertex3f(9*cos((float)index*PI/3),9*sin((float)index*PI/3),0.0f);
    }
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

bool ENEMYBM::logic(int step)
{
  switch(step)
    {
    case 0:
      x+=xvel;
      y+=yvel;
      break;
    case 1:
      if(!((x>0)&&(x<screen.w)&&(y>0)&&(y<screen.h))&&dotProduct(xvel,yvel,x-screen.w/2,y+screen.h/2)>0)
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

void ENEMYBM::addToScore()
{
  globalScore+=20;
}
