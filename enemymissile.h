#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <vector>
#include <GL/gl.h>
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
