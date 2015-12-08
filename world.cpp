#define PI 3.14159265358

#include <iostream>
#include <cstdlib> //system("clear")
#include <vector>
#include <cmath>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "object.h"
//#include "graphics.h"
#include "world.h"
#include "person.h"
#include "player.h"
#include "globals.h"
#include "enemynormal.h"
#include "enemyacc.h"
#include "enemyhoming.h"
#include "enemymissile.h"
#include "enemyboss.h"
using namespace std;

WORLD::WORLD()
{
  x=472;
  id_index=10000;
}

int WORLD::printx()
{
  return x;
}

void WORLD::gamelogic()
{
  //actual logic
  generateEnemies();
  for(int index=0;index<objects.size();index++)
    {
      if(objects.at(index)->type.compare("TEXT")==0)
      {
	objects.at(index)->setText("SCORE "+leadingZeros(globalScore,8)+intToString(globalScore));
      }
    }
  
  int step=0;
  bool logic_done=false;
  while(!logic_done)
    {
      logic_done=true;
      for(int index=0;index<objects.size();index++)
	{
	  logic_done=(objects.at(index)->logic(step) && logic_done);
	}
      step++;
    }

  //sort objects vector
  int iMin;
  OBJECT* buffer;
  for(int j=0;j<objects.size()-1;j++)
    {
      iMin=j;
      for(int i=j;i<objects.size();i++)
	{
	  if(objects.at(i)->id < objects.at(iMin)->id)
	    {
	      iMin=i;
	    }
	}
      if(iMin!=j)
	{
	  buffer=objects.at(iMin);
	  objects.at(iMin)=objects.at(j);
	  objects.at(j)=buffer;
	}
    }
  
}

void WORLD::render(int frame)
{
  system("clear");

  /*for(int i=0;i<11;i++)
    {
      cout<<i<<": "<<(glfwGetJoystickButtons(GLFW_JOYSTICK_1,&count)[i]==1)<<" ";
    }
  cout<<glfwGetJoystickAxes(GLFW_JOYSTICK_1,&count)[0]<<endl;*/
  cout<<"joystick.attack: "<<joystick.attack<<endl;
  cout<<"frame "<<globalFrame<<endl;
  cout<<"score "<<globalScore<<endl;
  cout<<"attack frame "<<attackFrame<<endl;
  cout<<"number of entities "<<objects.size()+1<<endl;

  float red=(1+sin(globalFrame*PI/300))/2;
  float green=(1+sin((2*PI/3)+globalFrame*PI/300))/2;
  float blue=(1+sin((4*PI/3)+globalFrame*PI/300))/2;
  float value=(float)globalFrame/6000;
  if(value>0.25)
    {
      value=0.25;
    }

  glClearColor(value*red,value*green,value*blue,0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for(int layer_index=0;layer_index<10;layer_index++)
    {
      for(int index=0;index<objects.size();index++)
	{
	  if(objects.at(index)->layer==layer_index)
	    {
	      objects.at(index)->render();
	    }
	}
    }
  globalFrame++;
}

void WORLD::setx(int x_a)
{
  x=x_a;
}

void WORLD::addobject(OBJECT* object_a)
{
  objects.push_back(object_a);
  object_a->id=id_index;
  id_index++;
}

void WORLD::deleteobject(int idToDelete)
{
  for(int index=0;index<objects.size();index++)
    {
      if(objects.at(index)->id==idToDelete)
	{
	  delete objects.at(index);
	  objects.erase(objects.begin()+index);
	}
    }
}

void WORLD::generateEnemies()
{
  for(int index=0;index<objects.size();index++)
    {
      if(objects.at(index)->type.compare("BOSS")==0)
	{
	  return;
	}
    }
  int frequency=10+(20*pow(1.001,(-1*globalFrame)));
  cout<<"frequency "<<frequency<<endl;
  if(globalFrame%frequency==0 && globalFrame>30)
    {
      switch(rand()%4)
	{
	case 0://from top
	  randomEnemy(*this,rand()%screen.w,-20,0,12);
	  //new ENEMYNORMAL(*this,rand()%screen.w,-20,0,12);
	case 1://from bottom
	  randomEnemy(*this,rand()%screen.w,screen.h+20,0,-12);
	case 2://from left
	  randomEnemy(*this,-20,rand()%screen.h,12,0);
	case 3://from right
	  randomEnemy(*this,screen.w+20,rand()%screen.h,-12,0);
	}
    }
}

void WORLD::randomEnemy(WORLD& world,int x,int y,int xvel,int yvel)
{
  float proportion=10+globalFrame/225;
  if(proportion>80)
    {
      proportion=80;
    }
  int enemy=rand()%100;
  if(enemy<(proportion*1/16))
    {
      if(abs(x-screen.w/2)>abs(y-screen.h/2))
	{
	  new ENEMYBOSS(world,x,screen.h/2,xvel/3,yvel/3);
	}
      else
	{
	  new ENEMYBOSS(world,screen.w/2,y,xvel/3,yvel/3);
	}
      return;
    }
  if(enemy<(proportion*6/16))
    {
      new ENEMYACC(world,x,y,xvel,yvel);
      return;
    }
  if(enemy<(proportion*11/16))
    {
      new ENEMYHOMING(world,x,y,xvel,yvel);
      return;
    }
  if(enemy<(proportion*16/16))
    {
      new ENEMYMISSILE(world,rand()%screen.w,rand()%screen.h,0,0);
      return;
    }
  new ENEMYNORMAL(world,x,y,xvel,yvel);
}
