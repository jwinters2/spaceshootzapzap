#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <vector>
#include <GL/gl.h>
using namespace std;

#include "object.h"

class BULLET: public OBJECT{
 public:
  BULLET(WORLD&,float=0,float=0,float=0,float=0);
  void render();
  bool logic(int);
  void checkCollision();
};
