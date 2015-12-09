#define PI 3.16159265358979323

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include "person.h"
#include "object.h"
#include "world.h"
#include "enemymissile.h"
#include "coord.h"
#include "globals.h"
using namespace std;

ENEMYMISSILE::ENEMYMISSILE(WORLD& world_a,int x_a,int y_a,int xvel_a,int yvel_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  radius=12;
  health=1;
  alSourcePlay(Source.at(3));
  countdown=60;
  hostile=0;
}

void ENEMYMISSILE::render()
{
  glPushMatrix();
  glTranslatef(x,y,0);
  glRotatef(getDir(xvel,yvel)+180,0,0,1);
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
  if(countdown==0)
    {
      glBegin(GL_TRIANGLES);
      glColor3f(1.0f,0.5f,0.0f);//FF00FF
      glVertex3f(-12.0f,0.0f,0.0f);
      
      glColor3f(1.0f,0.5f,0.0f);//FF00FF	
      glVertex3f(4.0f,0.0f,0.0f);
      
      glColor3f(0.8f,0.4f,0.0f);//DUNNO
      glVertex3f(12.0f,08.0f,0.0f);
      
      
      glColor3f(0.6f,0.3f,0.0f);//FF00FF
      glVertex3f(-12.0f,0.0f,0.0f);
      
      glColor3f(0.6f,0.3f,0.0f);//FF00FF	
      glVertex3f(4.0f,0.0f,0.0f);
      
      glColor3f(0.8f,0.4f,0.0f);//DUNNO
      glVertex3f(012.0f,-8.0f,0.0f);
      glEnd();
    }
  else
    {
      /*for(int jndex=0;jndex<=5;jndex++)
	{
	      glBegin(GL_TRIANGLE_FAN);
	      glColor4f(1.0f,0.5f,0.0f,0.0f);
	      glVertex3f(0.0f,0.0f,0.0f);
	      //glColor3f((1+cos(countdown*2*PI/15))/2,0.0f,0.0f);
	      glColor4f(1.0f,0.5f,0.0f,(1+cos((float)jndex+countdown*2*PI/15))/3);
	      for(int index=0;index<128;index++)
		{
		  glVertex3f(4.0f*(1+jndex)*cos((float)index*PI/63.75),4.0f*(1+jndex)*sin((float)index*PI/63.75),0.0f);
		}
	      glEnd();
	}*/
       glBegin(GL_TRIANGLE_FAN);
       glColor4f(1.0f,0.5f,0.0f,0.0f);
       glVertex3f(0.0f,0.0f,0.0f);
       glColor4f(1.0f,0.5f,0.0f,1.0f);
       //glColor3f((1+cos(countdown*2*PI/15))/2,0.0f,0.0f);
       //glColor4f(1.0f,0.5f,0.0f,(1+cos((float)jndex+countdown*2*PI/15))/3);
       for(int index=0;index<128;index++)
	 {
	   glVertex3f(3.0f*((100-countdown)%10)*cos((float)index*PI/63.75),3.0f*((100-countdown)%10)*sin((float)index*PI/63.75),0.0f);
	 }
       glEnd();
    }
  
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

bool ENEMYMISSILE::logic(int step)
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
  
  switch(step)
    {
    case 0:
      if(countdown>0)
	{
	  alSourcePause(Source.at(3));
	  alSourcePlay(Source.at(3));
	  countdown--;
	  if(countdown==0)
	    {
	      hostile=1;
	      xvel=-xtarget*20/sqrt(pow(xtarget,2)+pow(ytarget,2));
	      yvel=-ytarget*20/sqrt(pow(xtarget,2)+pow(ytarget,2));
	      alSourceStop(Source.at(3));
	    }
	}
      else
	{
	  x+=xvel;
	  y+=yvel;
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

void ENEMYMISSILE::addToScore()
{
  globalScore+=300;
}
