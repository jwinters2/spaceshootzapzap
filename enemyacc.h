#pragma once

#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
using namespace std;

#include "object.h"

class ENEMYACC: public OBJECT{
 public:
  float xacc,yacc;
  ENEMYACC(WORLD&,int=0,int=0,int=0,int=0);
  void render();
  bool logic(int);
  void addToScore();
};
