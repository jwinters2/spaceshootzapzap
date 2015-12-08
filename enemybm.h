#pragma once

#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
using namespace std;

#include "object.h"

class ENEMYBM: public OBJECT{
 public:
  //ENEMYBM(WORLD&,int=0,int=0,int=0,int=0);
  ENEMYBM(WORLD&,float=0,float=0,float=0,float=0);
  void render();
  bool logic(int);
  void addToScore();
};
