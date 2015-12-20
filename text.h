#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <cstring>
#include <GL/gl.h>
//#include <FTGL/ftgl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "glyph.h"

#include "object.h"

class GTEXT:public OBJECT
{
 private:
  TTF_Font *font;
  //SDL_Surface *textsurface;
  SDL_Surface* start;
  SDL_Surface* mid;
  GLYPH* glyph;
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
  void clean();
  SDL_Color color(int,int,int);
};
