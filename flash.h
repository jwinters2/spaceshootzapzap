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

class FLASH: public OBJECT{
 public:
  FLASH(WORLD&,int,int,int,int,float,float,float);
  void render();
  bool logic(int);
	float red,green,blue,opacity;
};
