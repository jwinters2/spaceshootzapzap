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
//#include "world.h"
//#include "person.h"

class PERSON: public OBJECT{
 private:
  int age;
 public:
  PERSON(WORLD&,int=0,int=0,int=0,int=0,int=18);
  void render();
  bool logic(int);
};
