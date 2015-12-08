#include <iostream>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include "globals.h"
#include "object.h"
#include "person.h"
#include "player.h"
#include "world.h"
using namespace std;

OBJECT::OBJECT(WORLD& world_a,float x_a,float y_a,float xvel_a,float yvel_a)
{
  world=&world_a;
  world_a.addobject(this);
  exist=true;
  x=x_a;
  xvel=xvel_a;
  y=y_a;
  yvel=yvel_a;
  type="NULL";
  layer=5;
  age=0;
}

OBJECT::OBJECT(float x_a,float y_a,float xvel_a,float yvel_a)
{
  exist=true;
  x=x_a;
  xvel=xvel_a;
  y=y_a;
  yvel=yvel_a;
  type="NULL";
  layer=5;
  age=0;
}

void OBJECT::init(WORLD& world_a,int x_a,int y_a,int xvel_a,int yvel_a)
{
  world=&world_a;
  world_a.addobject(this);
  world_a.setx(200);
  exist=true;
  x=x_a;
  xvel=xvel_a;
  y=y_a;
  yvel=yvel_a;
}

bool OBJECT::logic(int step)
{
  switch(step)
    {
    case 0:
      if(exist)
	{
	  x+=xvel;
	  y+=yvel;
	}
      break;
    case 1:
      if(exist)
	{
	  if(x<0 || x>40)
	    {
	      x-=xvel;
	      xvel*=-1;
	    }
	  if(y<0 || y>40)
	    {
	      y-=yvel;
	      yvel*=-1;
	    }
	}
      break;
    case 2:
      for(int index_flogic=0;index_flogic<world->objects.size();index_flogic++)
	{
	  if(x==world->objects.at(index_flogic)->x
	     && y==world->objects.at(index_flogic)->y
	     && id!=world->objects.at(index_flogic)->id)
	    {
	      exist=false;
	    }
	}
      break;
    default:
      return true;
      break;
    }
  return false;
}

void OBJECT::render()
{
  glBegin(GL_QUADS);

  if(exist)
    {
      glColor3f(1.0f,1.0f,1.0f);//ffffff
    }
  else
    {
      glColor3f(1.0f,0.0f,0.0f);//ff0000
    }
  
  glVertex3f((float)x-20,(float)y-20,-60.0f);
  glVertex3f((float)x-19.2,(float)y-20,-60.0f);
  glVertex3f((float)x-19.2,(float)y-19.2,-60.0f);
  glVertex3f((float)x-20,(float)y-19.2,-60.0f);

  glEnd();
  //OLD CLI RENDER
  cout<<"id: "<<id<<"\t";
  cout<<"x:"<<x<<"\t";
  cout<<"y:"<<y<<"\t";
  cout<<"xvel:"<<xvel<<"\t";
  cout<<"yvel:"<<yvel<<"\t\t";
  if(!exist)
    {
      cout<<"DESTROYED";
    }
  cout<<endl;
  
}

void OBJECT::die()
{
  alSourcePlay(Source.at(2));
  world->deleteobject(id);
}
