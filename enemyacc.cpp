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
#include "enemyacc.h"
#include "coord.h"
#include "globals.h"
using namespace std;

ENEMYACC::ENEMYACC(WORLD& world_a,int x_a,int y_a,int xvel_a,int yvel_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  radius=12;
  health=1;
  xacc=0.1*xvel;
  yacc=0.1*yvel;
  hostile=1;
}

void ENEMYACC::render()
{
  glPushMatrix();
  glTranslatef(x,y,0);
  glRotatef(getDir(xvel,yvel)+180,0,0,1);
  glBegin(GL_TRIANGLES);
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
  glColor3f(0.0f,1.0f,1.0f);//00FFFF
  glVertex3f(-12.0f,0.0f,0.0f);

  glColor3f(0.0f,1.0f,1.0f);	
  glVertex3f(4.0f,0.0f,0.0f);

  glColor3f(0.0f,0.8f,0.8f);
  glVertex3f(012.0f,012.0f,0.0f);

  
  glColor3f(0.0f,0.6f,0.6f);
  glVertex3f(-12.0f,0.0f,0.0f);

  glColor3f(0.0f,0.6f,0.6f);	
  glVertex3f(4.0f,0.0f,0.0f);

  glColor3f(0.0f,0.8f,0.8f);
  glVertex3f(012.0f,0-12.0f,0.0f);
  
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

bool ENEMYACC::logic(int step)
{
  switch(step)
    {
    case 0:
      x+=xvel;
      y+=yvel;
      if((x>0)&&(x<screen.w)&&(y>0)&&(y<screen.h))
	{
	  xvel+=xacc;
	  yvel+=yacc;
	}
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

void ENEMYACC::addToScore()
{
  globalScore+=100;
}
