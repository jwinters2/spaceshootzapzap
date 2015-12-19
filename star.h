#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <vector>
#include <GL/gl.h>
//#include <GLFW/glfw3.h>
using namespace std;

#include "object.h"

class STAR: public OBJECT{
 public:
  int starSpeed;
  STAR(WORLD&,int=0,int=0,int=0,int=0);
  void render();
  bool logic(int);
};
