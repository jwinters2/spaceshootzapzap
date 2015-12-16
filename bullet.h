#pragma once

#include <iostream>
#include <vector>
#include <GL/gl.h>
using namespace std;

#include "object.h"

class BULLET: public OBJECT{
 public:
  BULLET(WORLD&,int=0,int=0,int=0,int=0);
  void render();
  bool logic(int);
  void checkCollision();
};
