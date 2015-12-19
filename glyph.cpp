#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <GL/gl.h>
#include <SDL2/SDL_ttf.h>
//#include <freetype2/freetype/config/ftheader.h>
//#include <freetype2/ft2build.h>
//#include <FTGL/ftgl.h>
//#include <FTGL/FTGLPixmapFont.h>
#include "person.h"
#include "object.h"
#include "world.h"
#include "coord.h"
//#include "globals.h"

#include "glyph.h"
using namespace std;

void GLYPH::init(int size_a)
{
  font = TTF_OpenFont("Unifont.ttf",size_a);
  TTF_SetFontStyle(font,TTF_STYLE_BOLD);
  SetSurface("A",glyph_a);
  SetSurface("B",glyph_b);
  SetSurface("C",glyph_c);
  SetSurface("D",glyph_d);
  SetSurface("E",glyph_e);
  SetSurface("F",glyph_f);
  SetSurface("G",glyph_g);
  SetSurface("H",glyph_h);
  SetSurface("I",glyph_i);
  SetSurface("J",glyph_j);
  SetSurface("K",glyph_k);
  SetSurface("L",glyph_l);
  SetSurface("M",glyph_m);
  SetSurface("N",glyph_n);
  SetSurface("O",glyph_o);
  SetSurface("P",glyph_p);
  SetSurface("Q",glyph_q);
  SetSurface("R",glyph_r);
  SetSurface("S",glyph_s);
  SetSurface("T",glyph_t);
  SetSurface("U",glyph_u);
  SetSurface("V",glyph_v);
  SetSurface("W",glyph_w);
  SetSurface("X",glyph_x);
  SetSurface("Y",glyph_y);
  SetSurface("Z",glyph_z);
  SetSurface("0",glyph_0);
  SetSurface("1",glyph_1);
  SetSurface("2",glyph_2);
  SetSurface("3",glyph_3);
  SetSurface("4",glyph_4);
  SetSurface("5",glyph_5);
  SetSurface("6",glyph_6);
  SetSurface("7",glyph_7);
  SetSurface("8",glyph_8);
  SetSurface("9",glyph_9);
  SetSurface("_",glyph_UNDERSCORE);
  SetSurface("-",glyph_MINUS);
  SetSurface(":",glyph_COLON);
  SetSurface(" ",glyph_SPACE);

}

void GLYPH::SetSurface(string letter,GLuint &surf)
{
  start=TTF_RenderText_Solid(font,letter.c_str(),color(255,255,255));
  mid=SDL_CreateRGBSurface(0,start->w,start->h,32,0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
  SDL_BlitSurface(start,0,mid,0);

  glGenTextures(1,&surf);
  glBindTexture(GL_TEXTURE_2D,surf);
  glTexImage2D(GL_TEXTURE_2D,0,4,start->w,start->h,0,GL_BGRA,GL_UNSIGNED_BYTE,mid->pixels);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  width=start->w;
  height=start->h;

  SDL_FreeSurface(start);
  SDL_FreeSurface(mid);
}

void GLYPH::render(string letter,int x_a,int y_a)
{
  glEnable(GL_TEXTURE_2D);
  if(letter.compare("a")==0 || letter.compare("A")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_a);
    }
  if(letter.compare("b")==0 || letter.compare("B")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_b);
    }
  if(letter.compare("c")==0 || letter.compare("C")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_c);
    }
  if(letter.compare("d")==0 || letter.compare("D")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_d);
    }
  if(letter.compare("e")==0 || letter.compare("E")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_e);
    }
  if(letter.compare("f")==0 || letter.compare("F")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_f);
    }
  if(letter.compare("g")==0 || letter.compare("G")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_g);
    }
  if(letter.compare("h")==0 || letter.compare("H")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_h);
    }
  if(letter.compare("i")==0 || letter.compare("I")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_i);
    }
  if(letter.compare("j")==0 || letter.compare("J")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_j);
    }
  if(letter.compare("k")==0 || letter.compare("K")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_k);
    }
  if(letter.compare("l")==0 || letter.compare("L")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_l);
    }
  if(letter.compare("m")==0 || letter.compare("M")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_m);
    }
  if(letter.compare("n")==0 || letter.compare("N")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_n);
    }
  if(letter.compare("o")==0 || letter.compare("O")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_o);
    }
  if(letter.compare("p")==0 || letter.compare("P")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_p);
    }
  if(letter.compare("q")==0 || letter.compare("Q")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_q);
    }
  if(letter.compare("r")==0 || letter.compare("R")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_r);
    }
  if(letter.compare("s")==0 || letter.compare("S")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_s);
    }
  if(letter.compare("t")==0 || letter.compare("T")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_t);
    }
  if(letter.compare("u")==0 || letter.compare("U")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_u);
    }
  if(letter.compare("v")==0 || letter.compare("V")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_v);
    }
  if(letter.compare("w")==0 || letter.compare("W")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_w);
    }
  if(letter.compare("x")==0 || letter.compare("X")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_x);
    }
  if(letter.compare("y")==0 || letter.compare("Y")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_y);
    }
  if(letter.compare("z")==0 || letter.compare("Z")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_z);
    }
  if(letter.compare("0")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_0);
    }
  if(letter.compare("1")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_1);
    }
  if(letter.compare("2")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_2);
    }
  if(letter.compare("3")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_3);
    }
  if(letter.compare("4")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_4);
    }
  if(letter.compare("5")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_5);
    }
  if(letter.compare("6")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_6);
    }
  if(letter.compare("7")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_7);
    }
  if(letter.compare("8")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_8);
    }
  if(letter.compare("9")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_9);
    }
  if(letter.compare("_")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_UNDERSCORE);
    }
  if(letter.compare("-")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_MINUS);
    }
  if(letter.compare(":")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_COLON);
    }
  if(letter.compare(" ")==0)
    {
      glBindTexture(GL_TEXTURE_2D, glyph_SPACE);
    }

  glPushMatrix();
  glTranslatef(x_a,y_a,0);
    for(int index=0;index<=1;index++)
      {
	glBegin(GL_QUADS);
	glColor3f(1.0f,1.0f,1.0f);
	
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(0,index,0);
	glTexCoord2f(1.0f,1.0f);
	glVertex3f(width,index,0);
	glTexCoord2f(1.0f,0.0f);
	glVertex3f(width,height+index,0);
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(0,height+index,0);
	    
	glEnd();
      }
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
}

SDL_Color GLYPH::color(int r,int g,int b)
{
  SDL_Color cl={r,g,b};
  return cl;
}
