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
#include "puinvuln.h"
#include "explosion.h"
#include "coord.h"
#include "globals.h"
using namespace std;

PUINVULN::PUINVULN(WORLD& world_a,int x_a,int y_a,int xvel_a,int yvel_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  radius=9;
  health=1;
  hostile=0;
}

void PUINVULN::render()
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
	  float alpha=(index==0?1.0f:(float)freq/((2*index)+4));
	  //cout<<"r"<<index<<" "<<alpha<<";";
	  glPushMatrix();
	  glTranslatef(posHistory.at(index)->x,posHistory.at(index)->y,0);
	  glRotatef(posHistory.at(index)->dir+90,0,0,1);
	  glBegin(GL_TRIANGLES);
	  	  //main body
	  glColor4f(0.8f,0.0f,0.8f,alpha);//FF00FF
	  glVertex3f(-4.0f,4.0f,0.0f);

    glColor4f(1.0f,0.0f,1.0f,alpha);
    glVertex3f(0.0f,8.0f,0.0f);

    glColor4f(0.8f,0.0f,0.8f,alpha);//FF00FF
	  glVertex3f(4.0f,4.0f,0.0f);
	
  
    glColor4f(1.0f,0.2f,1.0f,alpha);//FF00FF
	  glVertex3f(-4.0f,4.0f,0.0f);

    glColor4f(0.8f,0.0f,0.8f,alpha);
    glVertex3f(-4.0f,-4.0f,0.0f);

    glColor4f(1.0f,0.2f,1.0f,alpha);//FF00FF
	  glVertex3f(4.0f,4.0f,0.0f);
    
    
    glColor4f(0.8f,0.0f,0.8f,alpha);
    glVertex3f(-4.0f,-4.0f,0.0f);

    glColor4f(1.0f,0.2f,1.0f,alpha);//FF00FF
	  glVertex3f(4.0f,4.0f,0.0f);

    glColor4f(0.8f,0.0f,0.8f,alpha);
    glVertex3f(4.0f,-4.0f,0.0f);


    glColor4f(1.0f,0.2f,1.0f,alpha);//FF00FF
	  glVertex3f(-4.0f,-4.0f,0.0f);

    glColor4f(1.0f,0.0f,1.0f,alpha);
    glVertex3f(0.0f,-8.0f,0.0f);

    glColor4f(1.0f,0.2f,1.0f,alpha);//FF00FF
	  glVertex3f(4.0f,-4.0f,0.0f);

  
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
}

bool PUINVULN::logic(int step)
{
  switch(step)
    {
    case 0:
      x+=xvel*(60.0f/fps);
      y+=yvel*(60.0f/fps);
      
      posHistory.insert(posHistory.begin(),new posState(x,y,getDir(xvel,yvel)));
      
      if(posHistory.size()>40)
	{
	  delete posHistory.at(40);
	  posHistory.resize(40);
	}
      //posHistory.at(0)->x=x;
      //posHistory.at(0)->y=y;
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

void PUINVULN::addToScore()
{
}
