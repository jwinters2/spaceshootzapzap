#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
//#include <AL/al.h>
//#include <AL/alc.h>
//#include <AL/alut.h>
#include "person.h"
#include "object.h"
#include "world.h"
#include "enemymissile.h"
#include "explosion.h"
#include "coord.h"
#include "globals.h"
using namespace std;

const double pi=3.14159265358979323;

ENEMYMISSILE::ENEMYMISSILE(WORLD& world_a,int x_a,int y_a,int xvel_a,int yvel_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  radius=12;
  health=1;
  Mix_PlayChannel(beepbeepbeepSound.channel,beepbeepbeepSound.sound,3);
  countdown=fps;
  hostile=0;
}

void ENEMYMISSILE::render()
{
      
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
      for(int index=0;index<posHistory.size();index++)
	{
          int freq=fps/15;
	  if(freq<=0)
            {
              freq=1;
            }
          if(index%freq==0 && index<=0.6666*fps)
	    {
	      float alpha=(index==0?1.0f:2.0f/(index+4));
	      glPushMatrix();
	      glTranslatef(posHistory.at(index)->x,posHistory.at(index)->y,0);
	      glRotatef(getDir(xvel,yvel)+180,0,0,1);
	      
	      glBegin(GL_TRIANGLES);
	      glColor4f(1.0f,0.5f,0.0f,alpha);//FF00FF
	      glVertex3f(-12.0f,0.0f,0.0f);
	      
	      glColor4f(1.0f,0.5f,0.0f,alpha);//FF00FF	
	      glVertex3f(4.0f,0.0f,0.0f);
	      
	      glColor4f(0.8f,0.4f,0.0f,alpha);//DUNNO
	      glVertex3f(12.0f,8.0f,0.0f);
	      
	      
	      glColor4f(0.6f,0.3f,0.0f,alpha);//FF00FF
	      glVertex3f(-12.0f,0.0f,0.0f);
	      
	      glColor4f(0.6f,0.3f,0.0f,alpha);//FF00FF	
	      glVertex3f(4.0f,0.0f,0.0f);
	      
	      glColor4f(0.8f,0.4f,0.0f,alpha);//DUNNO
	      glVertex3f(012.0f,-8.0f,0.0f);
	      glEnd();
	      glPopMatrix();
	    }
	}
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
      glPushMatrix();
      glTranslatef(x,y,0);
      glRotatef(getDir(xvel,yvel)+180,0,0,1);
  
      glBegin(GL_TRIANGLE_FAN);
      glColor4f(1.0f,0.5f,0.0f,0.0f);
      glVertex3f(0.0f,0.0f,0.0f);
      glColor4f(1.0f,0.5f,0.0f,1.0f);
      //glColor3f((1+cos(countdown*2*PI/15))/2,0.0f,0.0f);
      //glColor4f(1.0f,0.5f,0.0f,(1+cos((float)jndex+countdown*2*PI/15))/3);
      for(int index=0;index<128;index++)
	{
	  glVertex3f(3.0f*((100-countdown)%10)*cos((float)index*pi/63.5),3.0f*((100-countdown)%10)*sin((float)index*pi/63.5),0.0f);
	}
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
	  //alSourcePause(Source.at(3));
	  //Mix_PlayChannel(-1,beepbeepbeepWAV,0);
	  countdown--;
	  if(countdown==0)
	    {
	      hostile=1;
	      xvel=-xtarget*16/sqrt(pow(xtarget,2)+pow(ytarget,2));
	      yvel=-ytarget*16/sqrt(pow(xtarget,2)+pow(ytarget,2));
	      Mix_HaltChannel(-1);
	    }
	}
      else
	{
	  x+=xvel*(60.0f/fps);
	  y+=yvel*(60.0f/fps);

	  if(countdown==0)
	    {
	      posHistory.insert(posHistory.begin(),new posState(x,y,getDir(xvel,yvel)));
	    }
      
	  if(posHistory.size()>40)
	    {
	      delete posHistory.at(40);
	      posHistory.resize(40);
	    }
	}
      break;
    case 1:
      if(!((x>0)&&(x<screen.w)&&(y>0)&&(y<screen.h))&&dotProduct(xvel,yvel,x-screen.w/2,y-screen.h/2)>0)
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

void ENEMYMISSILE::addToScore()
{
  new EXPLOSION(*world,x,y,1,0.5f,0);
  globalScore+=300;
}
