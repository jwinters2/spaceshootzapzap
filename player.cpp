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
#include "player.h"
#include "coord.h"
#include "globals.h"
#include "bullet.h"
using namespace std;

const double pi=3.14159265358979323;

PLAYER::PLAYER(WORLD& world_a,int x_a,int y_a,int xvel_a,int yvel_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  type="PLAYER";
  maxspeed=7;
  hostile=0;
  bulletTimer=0;
  radius=12;
  invincibleTimer=0;
  fireboostTimer=0;
	scoreFpsTimer=fps;
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
  if(invincibleTimer>0)
  {
    //INVINCIBLY PURPLE
    glColor3f(1.0f,0.6f,1.0f);//999999
    glVertex3f(-12.0f,-12.0f,0.0f);

    glColor3f(0.8f,0.0f,0.8f);//888888	
    glVertex3f(-12.0f,012.0f,0.0f);

    glColor3f(1.0f,0.6f,1.0f);//999999
    glVertex3f(012.0f,012.0f,0.0f);

    glColor3f(0.8f,0.0f,0.8f);//888888	
    glVertex3f(012.0f,-12.0f,0.0f);
  }
  else
  {
    glColor3f(0.6f,0.6f,0.6f);//999999
    glVertex3f(-12.0f,-12.0f,0.0f);

    glColor3f(0.5f,0.5f,0.5f);//888888	
    glVertex3f(-12.0f,012.0f,0.0f);

    glColor3f(0.6f,0.6f,0.6f);//999999
    glVertex3f(012.0f,012.0f,0.0f);

    glColor3f(0.5f,0.5f,0.5f);//888888
    glVertex3f(012.0f,-12.0f,0.0f);
  }


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
	      yvel+=0.8*(60.0f/fps);//1.5;
	    }
	  if(keys.down)
	    {
	      yvel-=0.8*(60.0f/fps);//1.5;
	    }
	  if(keys.left)
	    {
	      xvel-=0.8*(60.0f/fps);//1.5;
	    }
	  if(keys.right)
	    {
	      xvel+=0.8*(60.0f/fps);//1.5;
	    }
	  if((xvel*xvel)+(yvel*yvel)>maxspeed*maxspeed)
	    {
	      xvel*=maxspeed/sqrt((xvel*xvel)+(yvel*yvel));
	      yvel*=maxspeed/sqrt((xvel*xvel)+(yvel*yvel));
	    }
	  //move, and stay in frame
	  x+=xvel*(60.0f/fps);
	  y+=yvel*(60.0f/fps);
	  if((x<0)||(x>screen.w))
	    {
	      x-=xvel*(60.0f/fps);
	      xvel=0;
	    }
	  if((y<0)||(y>screen.h))
	    {
	      y-=yvel*(60.0f/fps);
	      yvel=0;
	    }

	  //slow down if no keys are pressed
	  if(!(keys.up||keys.down||keys.left||keys.right))
	    {
	      if(xvel!=0)
		{
		  xvel*=(sqrt((xvel*xvel)+(yvel*yvel))-60.0f/fps)/sqrt((xvel*xvel)+(yvel*yvel));
		  if(abs(xvel)<1)
		    {
		      xvel=0;
		    }
		}
	      if(yvel!=0)
		{
		  yvel*=(sqrt((xvel*xvel)+(yvel*yvel))-60.0f/fps)/sqrt((xvel*xvel)+(yvel*yvel));
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
      if(bulletTimer>0)
			{
				bulletTimer--;
			}

      if(invincibleTimer>0)
      {
        invincibleTimer-=(60.0f/fps);
      }
      
      if(fireboostTimer>0)
      {
        fireboostTimer-=(60.0f/fps);
      }

      if(scoreFpsTimer<=0 && globalFrame>5)
			{
				globalScore+=10;
				scoreFpsTimer=fps/2;
			}
			scoreFpsTimer--;

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
      if(invincibleTimer>0)
      {
				world->objects.at(index)->addToScore();
				world->objects.at(index)->die();
      }
      else
      {
        cout<<"Collision, game over"<<endl;
        //quitGame();
        gameScoreBoard=1;
      }
    }
    if(collideCircles(x,y,world->objects.at(index)->x,world->objects.at(index)->y,4+radius)&&world->objects.at(index)->type.compare("PUINVULN")==0)
    {
      invincibleTimer=180;
      world->deleteobject(world->objects.at(index)->id);
    }
    if(collideCircles(x,y,world->objects.at(index)->x,world->objects.at(index)->y,4+radius)&&world->objects.at(index)->type.compare("PUSHOOT")==0)
    {
      fireboostTimer=180;
      world->deleteobject(world->objects.at(index)->id);
    }

  }
}

void PLAYER::shootBullets()
{
  if(fireboostTimer>0)
  {
    /*
    new BULLET(*world,x,y,-3,11.619);
    new BULLET(*world,x,y,0,11.619);
    new BULLET(*world,x,y,30,11.619);

    new BULLET(*world,x,y,-3,-11.619);
    new BULLET(*world,x,y,0,-11.619);
    new BULLET(*world,x,y,3,-11.619);
    
    new BULLET(*world,x,y,11.619,-3);
    new BULLET(*world,x,y,11.619,0);
    new BULLET(*world,x,y,11.619,3);

    new BULLET(*world,x,y,-11.619,-3);
    new BULLET(*world,x,y,-11.619,0);
    new BULLET(*world,x,y,-11.619,3);
    */

    for(int index=0;index<4;index++)
    {
      new BULLET(*world,x,y,12.0*cos(index*pi/2),12.0*sin(index*pi/2));
      new BULLET(*world,x,y,12.0*cos(index*pi/2+(fireboostTimer*pi/180)),12.0*sin(index*pi/2+(fireboostTimer*pi/180)));
      new BULLET(*world,x,y,12.0*cos(index*pi/2-(fireboostTimer*pi/180)),12.0*sin(index*pi/2-(fireboostTimer*pi/180)));
    }
    Mix_PlayChannel(shootSound.channel,shootSound.sound,0);
    bulletTimer=fps/10;
  }
  else
  {
    if(bulletTimer==0)
      {
        for(int index=0;index<4;index++)
        {
          new BULLET(*world,x,y,12.0*cos(index*pi/2),12.0*sin(index*pi/2));
        }
        Mix_PlayChannel(shootSound.channel,shootSound.sound,0);
        bulletTimer=fps/5;
      }
  }
}
