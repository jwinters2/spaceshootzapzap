#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "person.h"
#include "object.h"
#include "world.h"
#include "enemyhoming.h"
#include "coord.h"
#include "globals.h"
using namespace std;

ENEMYHOMING::ENEMYHOMING(WORLD& world_a,int x_a,int y_a,int xvel_a,int yvel_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  radius=12;
  health=1;
  hostile=1;
}

void ENEMYHOMING::render()
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
  glColor3f(0.5f,1.0f,0.0f);//FF00FF
  glVertex3f(-12.0f,0.0f,0.0f);

  glColor3f(0.5f,1.0f,0.0f);	
  glVertex3f(4.0f,0.0f,0.0f);

  glColor3f(0.4f,0.8f,0.0f);
  glVertex3f(012.0f,012.0f,0.0f);

  
  glColor3f(0.3f,0.6f,0.0f);
  glVertex3f(-12.0f,0.0f,0.0f);

  glColor3f(0.3f,0.6f,0.0f);	
  glVertex3f(4.0f,0.0f,0.0f);

  glColor3f(0.4f,0.8f,0.0f);
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

bool ENEMYHOMING::logic(int step)
{
  int xtarget,ytarget;
  for(int index=0;index<world->objects.size();index++)
    {
      if(world->objects.at(index)->type.compare("PLAYER")==0)
	{
	  xtarget=x-world->objects.at(index)->x;
	  ytarget=y-world->objects.at(index)->y;
	  break;
	}
    }

  float speed=sqrt(pow(xvel,2)+pow(yvel,2));
  switch(step)
    {
    case 0:
      x+=xvel;
      y+=yvel;
      xvel-=0.4*(xtarget/sqrt(pow(xtarget,2)+pow(ytarget,2)));
      yvel-=0.4*(ytarget/sqrt(pow(xtarget,2)+pow(ytarget,2)));
      xvel*=speed/sqrt(pow(xvel,2)+pow(yvel,2));
      yvel*=speed/sqrt(pow(xvel,2)+pow(yvel,2));
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

void ENEMYHOMING::addToScore()
{
  globalScore+=150;
}
