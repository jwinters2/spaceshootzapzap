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
#include "enemynormal.h"
#include "explosion.h"
#include "coord.h"
#include "globals.h"
using namespace std;

ENEMYNORMAL::ENEMYNORMAL(WORLD& world_a,int x_a,int y_a,int xvel_a,int yvel_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  radius=12;
  health=1;
  hostile=1;
}

void ENEMYNORMAL::render()
{
  for(int index=0;index<posHistory.size();index++)
    {
      if(index%4==0)
	{
	  float alpha=(index==0?1.0f:2.0f/(index+4));
	  //cout<<"r"<<index<<" "<<alpha<<";";
	  glPushMatrix();
	  glTranslatef(posHistory.at(index)->x,posHistory.at(index)->y,0);
	  glRotatef(posHistory.at(index)->dir+180,0,0,1);
	  glBegin(GL_TRIANGLES);
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
	  glColor4f(1.0f,0.0f,1.0f,alpha);//FF00FF
	  glVertex3f(-12.0f,0.0f,0.0f);
	  
	  glColor4f(1.0f,0.0f,1.0f,alpha);//FF00FF	
	  glVertex3f(4.0f,0.0f,0.0f);
	  
	  glColor4f(0.8f,0.0f,0.8f,alpha);//DUNNO
	  glVertex3f(012.0f,012.0f,0.0f);
	  
	  
	  glColor4f(0.6f,0.0f,0.6f,alpha);//FF00FF
	  glVertex3f(-12.0f,0.0f,0.0f);
	  
	  glColor4f(0.6f,0.0f,0.6f,alpha);//FF00FF	
	  glVertex3f(4.0f,0.0f,0.0f);
	  
	  glColor4f(0.8f,0.0f,0.8f,alpha);//DUNNO
	  glVertex3f(012.0f,0-12.0f,0.0f);
	  
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

bool ENEMYNORMAL::logic(int step)
{
  switch(step)
    {
    case 0:
      x+=xvel;
      y+=yvel;
      
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

void ENEMYNORMAL::addToScore()
{
  new EXPLOSION(*world,x,y,1,0,1);
  globalScore+=50;
}
