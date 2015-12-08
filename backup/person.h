#pragma once

#include <iostream>
#include <vector>
#include <GL/glut.h>
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
