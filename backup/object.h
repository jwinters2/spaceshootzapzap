#pragma once

#include <iostream>
#include <vector>
#include <GL/glut.h>

//#include "world.h"
//#include "person.h"
//#include "object.h"
using namespace std;
class WORLD;

class OBJECT
{
public:
  int x,xvel,y,yvel,id;
  bool exist;
  WORLD * world;
  OBJECT(WORLD&,int=0,int=0,int=0,int=0);
  void init(WORLD&,int=0,int=0,int=0,int=0);
  virtual void render();
  virtual bool logic(int);
};
