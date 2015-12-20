#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <fstream>
#include <cstring>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
//#include <FTGL/ftgl.h>

#include "object.h"
#include "text.h"
#include "globals.h"
#include "glyph.h"

class HIGHSCORE:public OBJECT
{
 private:
  TTF_Font *font;
  SDL_Surface *textsurface;
  SDL_Surface* start;
  SDL_Surface* mid;
  GLuint texture;
  GLYPH* glyph;
  bool center;
  int w,h;
  int fontSize;
 public:
  string text;
  string nameToEnter;
  bool enteringName;
  fstream scoreFile;
  vector<stringPair> scoreEntries;
  HIGHSCORE(int=12,int=0,int=0,int=0,int=0);
  void render();
  bool logic(int);
  void setText(string,int,int=0);
  void drawText(int,int,bool);
  void setFontSize(int);
  void enterName();
  void reset();
  void clean();
  SDL_Color color(int,int,int);
};
