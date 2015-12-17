#pragma once

#include <iostream>
#include <vector>
#include <string>

//#include "world.h"
//#include "person.h"
//#include "object.h"
using namespace std;
class WORLD;

class OBJECT
{
public:
  float x,xvel,y,yvel,radius;
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
