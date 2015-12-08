#pragma once

#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
using namespace std;

#include "object.h"

class ENEMYBOSS: public OBJECT{
 private:
  bool dead;
  float yvelstart,xvelstart,xstart,ystart,direction;
 public:
  ENEMYBOSS(WORLD&,int=0,int=0,int=0,int=0);
  void render();
  bool logic(int);
  void addToScore();
  void stopAndFire();
  float speed();
  void die();
};
