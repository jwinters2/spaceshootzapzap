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
//#include "text.h"
//#include "globals.h"

class GLYPH
{
 public:
  TTF_Font *font;
  SDL_Surface *start;
  SDL_Surface *mid;
  GLuint texture;
  int width,height;

  GLuint glyph_a;
  GLuint glyph_b;
  GLuint glyph_c;
  GLuint glyph_d;
  GLuint glyph_e;
  GLuint glyph_f;
  GLuint glyph_g;
  GLuint glyph_h;
  GLuint glyph_i;
  GLuint glyph_j;
  GLuint glyph_k;
  GLuint glyph_l;
  GLuint glyph_m;
  GLuint glyph_n;
  GLuint glyph_o;
  GLuint glyph_p;
  GLuint glyph_q;
  GLuint glyph_r;
  GLuint glyph_s;
  GLuint glyph_t;
  GLuint glyph_u;
  GLuint glyph_v;
  GLuint glyph_w;
  GLuint glyph_x;
  GLuint glyph_y;
  GLuint glyph_z;
  GLuint glyph_0;
  GLuint glyph_1;
  GLuint glyph_2;
  GLuint glyph_3;
  GLuint glyph_4;
  GLuint glyph_5;
  GLuint glyph_6;
  GLuint glyph_7;
  GLuint glyph_8;
  GLuint glyph_9;
  GLuint glyph_UNDERSCORE;
  GLuint glyph_MINUS;
  GLuint glyph_COLON;
  GLuint glyph_SPACE;
  void init(int size_a);
  void SetSurface(std::string,GLuint&);
  void render(std::string,int,int);
  SDL_Color color(int,int,int);
};
