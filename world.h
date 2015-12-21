#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <vector>
//#include <GLFW/glfw3.h>

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
  void deleteobject(int);
  void setx(int);
  void addobject(OBJECT*);
  int printx();
  void render(int=0);
  void gamelogic();
  void generateEnemies();
  bool randomEnemy(WORLD&,int=0,int=0,int=0,int=0);
};
