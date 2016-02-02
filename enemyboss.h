#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <vector>
#include <GL/gl.h>
using namespace std;

#include "object.h"

class ENEMYBOSS: public OBJECT{
 private:
  bool dead;
  float yvelstart,xvelstart,xstart,ystart,direction;
  float bornFps;
 public:
  ENEMYBOSS(WORLD&,int=0,int=0,int=0,int=0);
  void render();
  bool logic(int);
  void addToScore();
  void stopAndFire();
  float speed();
  void die();
};
