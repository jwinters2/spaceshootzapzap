#include <iostream>
#include <vector>
#include <cstdlib>
#include "person.h"
#include "object.h"
#include "world.h"
#include "person.h"
using namespace std;

PERSON::PERSON(WORLD& world_a,int x_a,int y_a,int xvel_a,int yvel_a,int age_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  age=age_a;
}

void PERSON::render()
{
  glBegin(GL_QUADS);

  if(exist)
    {
      glColor3f(0.0f,1.0f,1.0f);//00ffff
    }
  else
    {
      glColor3f(1.0f,0.0f,1.0f);//ff00ff
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
  cout<<"yvel:"<<yvel<<"\t";
  cout<<"age: "<<age<<"\t";
  if(!exist)
    {
      cout<<"DESTROYED";
    }
  cout<<endl;
}

bool PERSON::logic(int step)
{
  switch(step)
    {
    case 0:
      if(exist)
	{
	  xvel=rand()%5-2;
	  yvel=rand()%5-2;
	  x+=xvel;
	  y+=yvel;
	  if(x<0 || x>40)
	    {
	      x-=xvel;
	    }
	  if(y<0 || y>40)
	    {
	      y-=yvel;
	    }
	}
      break;
    case 1:
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
