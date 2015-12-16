#pragma once

#include <iostream>
#include <vector>
#include <GL/gl.h>
using namespace std;

#include "object.h"

class PLAYER: public OBJECT{
 public:
  PLAYER(WORLD&,int=0,int=0,int=0,int=0);
  int maxspeed;
  void render();
  void checkCollisions();
  bool logic(int);
  void shootBullets();
};
