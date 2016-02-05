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
#include "bullet.h"
#include "coord.h"
#include "globals.h"
using namespace std;

BULLET::BULLET(WORLD& world_a,float x_a,float y_a,float xvel_a,float yvel_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  hostile=0;
}

void BULLET::render()
{
  glPushMatrix();
  glTranslatef(x,y,0);
  glRotatef(getDir(xvel,yvel)+90,0,0,1);
  glBegin(GL_TRIANGLE_FAN);
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
  glColor3f(1.0f,1.0f,0.0f);//FFFF00
  glVertex3f(0.0f,8.0f,0.0f);

  glColor3f(1.0f,1.0f,0.0f);//FFFF00
  glVertex3f(2.0f,6.0f,0.0f);

  glColor3f(0.8f,0.8f,0.0f);//FFFF00
  glVertex3f(2.0f,-6.0f,0.0f);

  glColor3f(1.0f,1.0f,0.0f);//FFFF00
  glVertex3f(0.0f,-8.0f,0.0f);

  glColor3f(1.0f,1.0f,0.0f);//FFFF00
  glVertex3f(-2.0f,-6.0f,0.0f);

  glColor3f(1.0f,1.0f,0.0f);//FFFF00
  glVertex3f(-2.0f,6.0f,0.0f);

  
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

bool BULLET::logic(int step)
{
  switch(step)
	{
    case 0:
      x+=xvel*(60.0f/fps);
      y+=yvel*(60.0f/fps);
      break;
    case 1:
      if(!((x>0)&&(x<screen.w)&&(y>0)&&(y<screen.h))&&dotProduct(xvel,yvel,x-screen.w/2,y+screen.h/2)>0)
			{
				world->deleteobject(id);
			}
      break;
    case 2:
      checkCollision();
      break;
    default:
      return true;
      break;
	}
  return false;
}

void BULLET::checkCollision()
{
  for(int index=0;index<world->objects.size();index++)
	{
		if(collideCircles(x,y,world->objects.at(index)->x,world->objects.at(index)->y,(2*world->objects.at(index)->radius)-10)&&world->objects.at(index)->hostile&&world->objects.at(index)->type.compare("ENEMYBM")!=0)
		{
			world->objects.at(index)->health--;
			if(world->objects.at(index)->health==0)
			{
				world->objects.at(index)->addToScore();
				//world->deleteobject(world->objects.at(index)->id);
				world->objects.at(index)->die();
			}
			else
			{
				Mix_PlayChannel(hitSound.channel,hitSound.sound,0);
			}
			world->deleteobject(id);
		}
	}
}
