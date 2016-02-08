#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <cstdlib> //system("clear")
#include <vector>
#include <cmath>
#include <GL/gl.h>
//#include <GLFW/glfw3.h>
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
#include "puinvuln.h"
#include "pushoot.h"
#include "pubomb.h"
#include "flash.h"
using namespace std;

const double pi=3.14159265358979323;

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
  
	if(peaceTime>0)
	{
		peaceTime-=60.0/fps;
	}
	else
	{
		peaceTime=0;
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
  #ifdef __unix
  system("clear");
  #endif
  #ifdef __unix__
  system("clear");
  #endif

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

  float red,green,blue;
  if((globalFrame%1200)<200)//red to yellow
    {
      red=1;
      green=(globalFrame%1200)/200.0f;
      blue=0;
    }
  if((globalFrame%1200)>=200 && (globalFrame%1200)<400)//yellow to green
    {
      red=1-((globalFrame%1200)-200)/200.0f;
      green=1;
      blue=0;
    }
  if((globalFrame%1200)>=400 && (globalFrame%1200)<600)//green to cyan
    {
      red=0;
      green=1;
      blue=((globalFrame%1200)-400)/200.0f;
    }
  if((globalFrame%1200)>=600 && (globalFrame%1200)<800)//cyan to blue
    {
      red=0;
      green=1-((globalFrame%1200)-600)/200.0f;
      blue=1;
    }
  if((globalFrame%1200)>=800 && (globalFrame%1200)<1000)//blue to magenta
    {
      red=((globalFrame%1200)-800)/200.0f;
      green=0;
      blue=1;
    }
  if((globalFrame%1200)>=1000)//magenta to red
    {
      red=1;
      green=0;
      blue=1-((globalFrame%1200)-1000)/200.0f;
    }
  /*
  float red=(1+sin(globalFrame*pi/600))/2;
  float green=(1+sin((2*pi/3)+globalFrame*pi/600))/2;
  float blue=(1+sin((4*pi/3)+globalFrame*pi/600))/2;
  */
  float value=(float)globalFrame/12000;
  if(value>0.3)
    {
      value=0.3;
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
  int frequency=(409600.0/(screen.w*screen.h))*(15+(30*pow(1.001,(-1*globalFrame/2))));
  cout<<"frequency "<<frequency<<endl;
  if(globalFrame%frequency==0 && peaceTime==0)//globalFrame>60)
  {
		if(rand()%(screen.w+screen.h)<screen.w)
		{
			if(rand()%2==0)
			{
				randomEnemy(*this,rand()%screen.w,-20,0,6);
			}
			else
			{
				randomEnemy(*this,rand()%screen.w,screen.h+20,0,-6);
			}
		}
		else
		{
			if(rand()%2==0)
			{
				randomEnemy(*this,-20,rand()%screen.h,6,0);
			}
			else
			{
				randomEnemy(*this,screen.w+20,rand()%screen.h,-6,0);
			}
		}
  }
}

bool WORLD::randomEnemy(WORLD& world,int x,int y,int xvel,int yvel)
{  
  float proportion=10+globalFrame/225;
  if(proportion>80)
    {
      proportion=80;
    }
  int enemy=rand()%100;
  int purand=rand()%300;
  switch(purand)
  {
    case 0:
      new PUINVULN(world,x,y,xvel/3,yvel/3);
      return false;
    case 1:
      new PUSHOOT(world,x,y,xvel/3,yvel/3);
      return false;
		case 2:
      new PUBOMB(world,x,y,xvel/3,yvel/3);
      return false;
  }

  if((globalScore+1000)%5000>4500)
  {
    //if(abs(x-screen.w/2)>abs(y-screen.h/2))
		if(x==-20 || x==screen.w+20)
    {
      new ENEMYBOSS(world,x,screen.h/2,xvel/3,yvel/3);
    }
    else
    {
      new ENEMYBOSS(world,screen.w/2,y,xvel/3,yvel/3);
    }
    return true;
  }
  if(enemy<(proportion*1/3))
  {
    new ENEMYACC(world,x,y,xvel,yvel);
    return false;
  }
  if(enemy<(proportion*2/3))
  {
    new ENEMYHOMING(world,x,y,xvel,yvel);
    return false;
  }
  if(enemy<(proportion*3/3))
  {
    OBJECT* play=NULL;
    for(int index=0;index<objects.size();index++)
    {
      if(objects.at(index)->type.compare("PLAYER")==0)
      {
        play=objects.at(index);
        break;
      }
    }
    float spawnx,spawny;
    do
    {
      spawnx=rand()%screen.w;
      spawny=rand()%screen.h;
    }
    while(sqrt(pow(spawnx-play->x,2)+pow(spawny-play->y,2))<=150);
    new ENEMYMISSILE(world,spawnx,spawny,0,0);
    return false;
  }
  new ENEMYNORMAL(world,x,y,xvel,yvel);
  return false;
}
 
