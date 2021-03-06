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
#include "enemyboss.h"
#include "enemybm.h"
#include "coord.h"
#include "globals.h"
using namespace std;

const double pi=3.14159265358979323;

ENEMYBOSS::ENEMYBOSS(WORLD& world_a,int x_a,int y_a,int xvel_a,int yvel_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  layer=6;
  yvelstart=yvel;
  xvelstart=xvel;
  xstart=x;
  ystart=y;
  direction=getDir(xvel,yvel)-90;
    
  type="BOSS";
  radius=42;
  health=30;
  hostile=1;
  dead=0;
  bornFps=fps;
}

void ENEMYBOSS::render()
{
  if(!dead || age<=bornFps)
	{
		for(int index=0;index<5;index++)
		{
			glPushMatrix();
			glTranslatef(x-(index*2*xvel),y-(index*2*yvel),0);
			glRotatef(direction,0,0,1);
			glScalef(1.33f,1.33f,0.0f);
			
			glBegin(GL_TRIANGLE_FAN);
			
			glColor4f(1.0f,1.0f,0.5f,(float)1/(2+index));//FFFF70
			glVertex3f(0.0f,-9.0f,0.0f);
			
			glVertex3f(-36.0f,-27.0f,0.0f);
			glVertex3f(-36.0f,8.0f,0.0f);
			glVertex3f(0.0f,27.0f,0.0f);
			//glColor3f(1.0f,0.0f,0.3f);
			glVertex3f(36.0f,9.0f,0.0f);
			glVertex3f(36.0f,-27.0f,0.0f);
			glEnd();
			glPopMatrix();
		}
		
		glPushMatrix();
		glTranslatef(x,y,0);
		glRotatef(direction,0,0,1);
		glScalef(1.33f,1.33f,0.0f);
		
		//orange strip
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f,0.7f,0.0f);//FF0000
		glVertex3f(0.0f,-9.0f,0.0f);
		glVertex3f(0.0f,27.0f,0.0f);
		glColor3f(0.8f,0.5f,0.0f);//FF0000
		glVertex3f(-36.0f,9.0f,0.0f);
		glVertex3f(-36.0f,-27.0f,0.0f);
		glEnd();
		
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.6f,0.4f,0.0f);//FF0000
		glVertex3f(0.0f,-9.0f,0.0f);
		glVertex3f(0.0f,27.0f,0.0f);
		glColor3f(0.8f,0.5f,0.0f);//FF0000
		glVertex3f(36.0f,9.0f,0.0f);
		glVertex3f(36.0f,-27.0f,0.0f);
		glEnd();
		
		//main body
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f,0.0f,0.0f);//FF0000
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,36.0f,0.0f);
		glColor3f(0.8f,0.0f,0.0f);//FF0000
		glVertex3f(-36.0f,18.0f,0.0f);
		glVertex3f(-36.0f,-18.0f,0.0f);
		glEnd();
		
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.6f,0.0f,0.0f);//FF0000
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,36.0f,0.0f);
		glColor3f(0.8f,0.0f,0.0f);//FF0000
		glVertex3f(36.0f,18.0f,0.0f);
		glVertex3f(36.0f,-18.0f,0.0f);
		glEnd();
		glPopMatrix();
	}

  if(dead)
	{
		glPushMatrix();
		glTranslatef(x,y,0);
		glRotatef(direction,0,0,1);
		glScalef(1.33f,1.33f,0.0f);
		if(age>bornFps)
		{
			glScalef(((float)age-bornFps),((float)age-bornFps),0);
		}
		//death glow
		glBegin(GL_TRIANGLE_FAN);
		if(age>bornFps)
		{
			//alSourceStop(Source.at(5));
			Mix_PlayChannel(explosionBigSound.channel,explosionBigSound.sound,0);
			glColor4f(1.0f,1.0f,1.0f,1.0f-3.0f*(((float)age-bornFps)/bornFps));//FFFFFF
		}
		else
		{
			glColor4f(1.0f,1.0f,1.0f,(float)age/bornFps);//FFFFFF
		}
		glVertex3f(0.0f,-9.0f,0.0f);
		glVertex3f(36.0f,-27.0f,0.0f);
		glVertex3f(36.0f,18.0f,0.0f);
		glVertex3f(0.0f,36.0f,0.0f);
		glVertex3f(-36.0f,18.0f,0.0f);
		glVertex3f(-36.0f,-27.0f,0.0f);
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
}

bool ENEMYBOSS::logic(int step)
{
  switch(step)
    {
    case 0:
      x+=xvel*(60.0f/fps);
      y+=yvel*(60.0f/fps);
      age++;
      if(!dead)
			{
				stopAndFire();
			}
      else
			{
				if(age>1.5*bornFps)
				{
					world->deleteobject(id);
				}
			}
      break;
    case 1:
      if(!((x>0)&&(x<screen.w)&&(y>0)&&(y<screen.h))&&dotProduct(xvel,yvel,x-screen.w/2,y-screen.h/2)>0)
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

void ENEMYBOSS::addToScore()
{
  globalScore+=1000;
}

void ENEMYBOSS::stopAndFire()
{
  if(age<(int)(50*bornFps/60))
	{
		return;
	}
  if(age==(int)(50*bornFps/60))
	{
		xvel=yvelstart;
		yvel=xvelstart;
	}
  if(age%(int)(bornFps*2/3)==0)
	{
		int range;
		if(xvel==0)
		{
			range=(screen.w*7)/640;
		}
		else
		{
			range=(screen.h*7)/640;
		}

		for(int index=-range;index<=range;index++)
		{
			new ENEMYBM(*world,x,y,9*cos((direction+90)*pi/180+(2.25*index/range)),9*sin((direction+90)*pi/180+(2.25*index/range)));
		}
	}
  if(!((x>radius)&&(x<screen.w-radius)&&(y>radius)&&(y<screen.h-radius))
	&&(dotProduct(xvel,yvel,x-screen.w/2,y-screen.h/2)>0))
	{
		xvel*=-1;
		yvel*=-1;
	}
}

float ENEMYBOSS::speed()
{
  return sqrt(pow(xvel,2)+pow(yvel,2));
}

void ENEMYBOSS::die()
{
  for(int index=0;index<world->objects.size();index++)
    {
      if(world->objects.at(index)->type.compare("ENEMYBM")==0)
	{
	  world->objects.at(index)->hostile=0;
	}
    }
  Mix_PlayChannel(heatingSound.channel,heatingSound.sound,0);
  hostile=0;
  dead=1;
  age=0;
  xvel=0;
  yvel=0;
}
