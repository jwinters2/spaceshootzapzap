#include <iostream>
#include <vector>
#include "object.h"
//#include "graphics.h"
#include "world.h"
#include "person.h"
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
	  if(
	     (objects.at(i)->y < objects.at(iMin)->y)||
	     (
	      (objects.at(i)->y == objects.at(iMin)->y)
	      && (objects.at(i)->x < objects.at(iMin)->x)
	     )
	    )
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
  cout<<frame<<endl;
  for(int index=0;index<objects.size();index++)
    {
      objects.at(index)->render();
    }
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
