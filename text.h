#pragma once
#include <cstring>
#include <GL/gl.h>
#include <FTGL/ftgl.h>

#include "object.h"

class GTEXT:public OBJECT
{
 private:
  FTBitmapFont * font;
  bool center;
 public:
  std::string text;
  GTEXT(string,int=12,int=0,int=0,int=0,int=0,bool=0);
    GTEXT(WORLD&,string,int=12,int=0,int=0,int=0,int=0,bool=0);
  void render();
  bool logic(int);
  void setFontSize(int);
  void setText(string);
};
