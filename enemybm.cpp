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
#include "enemybm.h"
#include "coord.h"
#include "globals.h"
using namespace std;

const double pi=3.14159265358979323;

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
  radius=8;
  health=1;
  hostile=1;
}

void ENEMYBM::render()
{
  for(int index=0;index<posHistory.size();index++)
	{
	  float alpha=(index==0?1.0f:2.0f/(index+4));
	  glPushMatrix();
	  glTranslatef(posHistory.at(index)->x,posHistory.at(index)->y,0);
	  glRotatef(posHistory.at(index)->dir+180,0,0,1);
	  //glScalef(1.0f,1.0f,1.0f);
	  
	  glBegin(GL_TRIANGLE_FAN);
	  //glColor3f((1+cos(countdown*2*PI/15))/2,0.0f,0.0f);
	  glColor4f(1.0f,0.0f,0.0f,alpha);
	  glVertex3f(0.0f,0.0f,0.0f);
	  glColor4f(1.0f,0.3f,0.0f,alpha);
	  for(int index=0;index<=6;index++)
	    {
	      glVertex3f(9*cos((float)index*pi/3),9*sin((float)index*pi/3),0.0f);
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
}

bool ENEMYBM::logic(int step)
{
  switch(step)
    {
    case 0:
      x+=xvel;
      y+=yvel;
      if(globalFrame%3==0)
	{
	  posHistory.insert(posHistory.begin(),new posState(x,y,getDir(xvel,yvel)));
	}
      if(posHistory.size()>10)
	{
	  delete posHistory.at(10);
	  posHistory.resize(10);
	}
      break;
    case 1:
      if(!((x>0)&&(x<screen.w)&&(y>0)&&(y<screen.h))&&dotProduct(xvel,yvel,x-screen.w/2,y+screen.h/2)>0)
	{
	  for(int index=0;index<posHistory.size();index++)
	    {
	      delete posHistory.at(index);
	    }
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
