#pragma once
#include <cstring>
#include <GL/gl.h>
//#include <FTGL/ftgl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "object.h"

class GTEXT:public OBJECT
{
 private:
  TTF_Font *font;
  SDL_Surface *textsurface;
  GLuint texture;
  bool center;
  int w,h;
 public:
  std::string text;
  GTEXT(string,int=12,int=0,int=0,int=0,int=0,bool=0);
  GTEXT(WORLD&,string,int=12,int=0,int=0,int=0,int=0,bool=0);
  void render();
  bool logic(int);
  void setFontSize(int);
  void setText(string);
  SDL_Color color(int,int,int);
};
