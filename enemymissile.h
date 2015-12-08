#pragma once

#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
using namespace std;

#include "object.h"

class ENEMYMISSILE: public OBJECT{
 public:
  int countdown;
  ENEMYMISSILE(WORLD&,int=0,int=0,int=0,int=0);
  void render();
  bool logic(int);
  void addToScore();
};
