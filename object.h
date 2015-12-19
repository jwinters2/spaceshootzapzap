#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <vector>
#include <string>

//#include "world.h"
//#include "person.h"
//#include "object.h"
using namespace std;

struct posState
{
  float x;
  float y;
  float dir;
  posState(float x_a,float y_a,float dir_a)
  {
    x=x_a;
    y=y_a;
    dir=dir_a;
  }
};

class WORLD;

class OBJECT
{
public:
  float x,xvel,y,yvel,radius;
  vector<posState*> posHistory;
  int health;
  int age;
  int id;
  int layer;
  string type;
  bool exist;
  bool hostile;
  WORLD * world;
  OBJECT(WORLD&,float=0,float=0,float=0,float=0);
  OBJECT(float=0,float=0,float=0,float=0);
  void init(WORLD&,int=0,int=0,int=0,int=0);
  virtual void render();
  virtual bool logic(int);
  virtual void setText(string){};
  virtual void addToScore(){};
  virtual void die();
  virtual void clean(){};
};
