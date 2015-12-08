#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "person.h"
#include "object.h"
#include "world.h"
#include "player.h"
#include "coord.h"
#include "globals.h"
#include "bullet.h"
using namespace std;

PLAYER::PLAYER(WORLD& world_a,int x_a,int y_a,int xvel_a,int yvel_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  type="PLAYER";
  maxspeed=10;
  hostile=0;
}

void PLAYER::render()
{
  glPushMatrix();
  glTranslatef(x,y,0);
  glRotatef(sqrt((xvel*xvel)+(yvel*yvel))/2,yvel,xvel,0);
  glBegin(GL_QUADS);
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
  glColor3f(0.6f,0.6f,0.6f);//999999
  glVertex3f(-12.0f,-12.0f,0.0f);

  glColor3f(0.5f,0.5f,0.5f);//888888	
  glVertex3f(-12.0f,012.0f,0.0f);

  glColor3f(0.6f,0.6f,0.6f);//999999
  glVertex3f(012.0f,012.0f,0.0f);

  glColor3f(0.5f,0.5f,0.5f);//888888
  glVertex3f(012.0f,-12.0f,0.0f);
  glEnd();

  //spikes
  for(int i=0;i<4;i++)
    {
      glRotatef(90,0,0,1);
      glBegin(GL_QUADS);
      glColor3f(1.0f,1.0f,0.0f);//BBBB00
      glVertex3f(0.0f,-18.0f,0.0f);
      
      //glColor3f(0.8f,0.6f,0.5f);//BB9900	
      glVertex3f(4.0f,-9.0f,0.0f);
      
      glColor3f(1.0f,0.7f,0.5f);//DUNNO	
      glVertex3f(0.0f,-06.0f,0.0f);
      
      //glColor3f(0.8f,0.6f,0.5f);//BB9900	
      glVertex3f(-4.0f,-9.0f,0.0f);
      
      glEnd();
    }
  glPopMatrix();

  //OLD CLI RENDER
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
}

bool PLAYER::logic(int step)
{
  switch(step)
    {
    case 0:
      if(exist)
	{
	  if(keys.up)
	    {
	      yvel+=2;
	    }
	  if(keys.down)
	    {
	      yvel-=2;
	    }
	  if(keys.left)
	    {
	      xvel-=2;
	    }
	  if(keys.right)
	    {
	      xvel+=2;
	    }
	  if((xvel*xvel)+(yvel*yvel)>maxspeed*maxspeed)
	    {
	      xvel*=maxspeed/sqrt((xvel*xvel)+(yvel*yvel));
	      yvel*=maxspeed/sqrt((xvel*xvel)+(yvel*yvel));
	    }
	  //move, and stay in frame
	  x+=xvel;
	  y+=yvel;
	  if((x<0)||(x>screen.w))
	    {
	      x-=xvel;
	      xvel=0;
	    }
	  if((y<0)||(y>screen.h))
	    {
	      y-=yvel;
	      yvel=0;
	    }

	  //slow down if no keys are pressed
	  if(!(keys.up||keys.down||keys.left||keys.right))
	    {
	      if(xvel!=0)
		{
		  xvel*=(sqrt((xvel*xvel)+(yvel*yvel))-1)/sqrt((xvel*xvel)+(yvel*yvel));
		  if(abs(xvel)<1)
		    {
		      xvel=0;
		    }
		}
	      if(yvel!=0)
		{
		  yvel*=(sqrt((xvel*xvel)+(yvel*yvel))-1)/sqrt((xvel*xvel)+(yvel*yvel));
		  if(abs(yvel)<1)
		    {
		      yvel=0;
		    }
		}
	    }
	}
      if(keys.attack)
	{
	  shootBullets();
	}
      break;
    case 1:
      checkCollisions();
      break;
    case 2:
      if(globalFrame%12==0 && globalFrame!=0)
	{
	  globalScore+=10;
	}
      break;
    default:
      return true;
      break;
    }
  return false;
}

void PLAYER::checkCollisions()
{
  for(int index=0;index<world->objects.size();index++)
    {
      if(collideCircles(x,y,world->objects.at(index)->x,world->objects.at(index)->y,4+(2*world->objects.at(index)->radius))&&world->objects.at(index)->hostile&& !(keys.y && keys.i))
	{
	  cout<<"Collision, game over"<<endl;
	  //quitGame();
	  gameScoreBoard=1;
	}
    }
}

void PLAYER::shootBullets()
{
  if((globalFrame-attackFrame)%6==0)
    {
      new BULLET(*world,x,y,0,16);
      new BULLET(*world,x,y,0,-16);
      new BULLET(*world,x,y,16,0);
      new BULLET(*world,x,y,-16,0);
      alSourcePlay(Source.at(1));
    }
}
