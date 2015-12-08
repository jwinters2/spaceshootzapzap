#pragma once

#include <iostream>
#include <vector>
#include <GL/glut.h>

//#include "world.h"
#include "object.h"
//#include "graphics.h"
//#include "person.h"
//#include "world.h"
using namespace std;
class OBJECT;

class WORLD
{
  friend class OBJECT;
private:
  int x,id_index;
public:
  vector<OBJECT *> objects;
  WORLD();
  void setx(int);
  void addobject(OBJECT*);
  int printx();
  void render(int=0);
  void gamelogic();
};
