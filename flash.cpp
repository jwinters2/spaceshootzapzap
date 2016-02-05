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
#include "flash.h"
#include "explosion.h"
#include "coord.h"
#include "globals.h"
using namespace std;

FLASH::FLASH(WORLD& world_a, int x_a, int y_a, int xvel_a, int yvel_a, float red_a, float green_a, float blue_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  hostile=0;
  type="FLASH";
	opacity=0.8;
	layer=3;
	red=red_a;
	green=green_a;
	blue=blue_a;
}

void FLASH::render()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f(red,green,blue,opacity);

	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f((float)screen.w,0.0f,0.0f);
	glVertex3f((float)screen.w,(float)screen.h,0.0f);
	glVertex3f(0.0f,(float)screen.h,0.0f);

	glEnd();
	glPopMatrix();
}
      
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

bool FLASH::logic(int step)
{
  switch(step)
    {
    case 0:
			if(opacity<=0)
			{
				world->deleteobject(id);
			}
			opacity-=0.05;
    default:
      return true;
      break;
    }
  return false;
}

