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
#include "text.h"
#include "coord.h"
#include "globals.h"
using namespace std;

GTEXT::GTEXT(WORLD& world_a,string text_a,int size_a,int x_a,int y_a,int xvel_a,int yvel_a,bool center_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  type="TEXT";
  layer=7;
  center=center_a;
  texture=0;
  cout<<"begin text constructor"<<endl;
  text=text_a;
  cout<<"set text"<<endl;
  glyph=&glyph_36;
  switch(size_a)
    {
    case 18:
        glyph=&glyph_18;
	break;
    case 36:
        glyph=&glyph_36;
	break;
    case 60:
        glyph=&glyph_60;
	break;
    }
  /*
  font = TTF_OpenFont("Unifont.ttf",size_a);
  TTF_SetFontStyle(font,TTF_STYLE_BOLD);
  cout<<"set font"<<endl;
  //font->FaceSize(size_a);
  cout<<"end text constructor"<<endl;
  //int w,h;
  
  start=TTF_RenderText_Solid(font,text.c_str(),color(255,255,255));
  mid=SDL_CreateRGBSurface(0,start->w,start->h,32,0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
  SDL_BlitSurface(start,0,mid,0);

  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);
  glTexImage2D(GL_TEXTURE_2D,0,4,start->w,start->h,0,GL_BGRA,GL_UNSIGNED_BYTE,mid->pixels);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  w=start->w;
  h=start->h;*/
}

GTEXT::GTEXT(string text_a,int size_a,int x_a,int y_a,int xvel_a,int yvel_a,bool center_a)
  :OBJECT(x_a,y_a,xvel_a,yvel_a)
{
  type="TEXT";
  layer=7;
  center=center_a;
  texture=0;
  cout<<"begin text constructor"<<endl;
  text=text_a;
  cout<<"set text"<<endl;
  glyph=&glyph_36;
  switch(size_a)
    {
    case 18:
        glyph=&glyph_18;
	break;
    case 36:
        glyph=&glyph_36;
	break;
    case 60:
        glyph=&glyph_60;
	break;
    }
  /*font = TTF_OpenFont("Unifont.ttf",size_a);
  TTF_SetFontStyle(font,TTF_STYLE_BOLD);
  cout<<"set font"<<endl;
  //font->FaceSize(size_a);
  cout<<"end text constructor"<<endl;

  //SDL_Surface* start;
  //SDL_Surface* mid;
  
  start=TTF_RenderText_Solid(font,text.c_str(),color(255,255,255));
  mid=SDL_CreateRGBSurface(0,start->w,start->h,32,0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
  SDL_BlitSurface(start,0,mid,0);

  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);
  glTexImage2D(GL_TEXTURE_2D,0,4,start->w,start->h,0,GL_BGRA,GL_UNSIGNED_BYTE,mid->pixels);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  w=start->w;
  h=start->h;*/
}

void GTEXT::render()
{
  if(center)
    {
       for(int index=0;index<text.length();index++)
	{
	  glyph->render(text.substr(index,1),x-((glyph->width*text.length()/2))+(glyph->width*index),y);
	}
    }
  else
    {
      for(int index=0;index<text.length();index++)
	{
	  glyph->render(text.substr(index,1),x+(glyph->width*index),y);
	}
    }
  /*glPushMatrix();
  glTranslatef(x,y,0);
  
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);

  /*glBegin(GL_QUADS);
  glColor4f(0.0f,0.0f,0.0f,0.3f);
  glVertex3f(0.0f,0.0f,0.0f);
  glVertex3f(screen.w,0.0f,0.0f);
  glVertex3f(screen.w,32.0f,0.0f);
  glVertex3f(0.0f,32.0f,0.0f);
  glEnd();
  
 
  glColor4d(1.0,1.0,1.0,1.0);
  int width=0;
  /*if(center)
    {
      width=abs(font->BBox(text.c_str(),-1,FTPoint(x,y,0),FTPoint(2,0,0)).Lower().X()-font->BBox(text.c_str(),-1,FTPoint(x,y,0),FTPoint(2,0,0)).Upper().X());
    }
  font->Render(text.c_str(),-1,FTPoint(x-(width/2),y,0),FTPoint(2,0,0),FTGL::ALIGN_CENTER); //text doesn't transform, so use FTPoint
  font->Render(text.c_str(),-1,FTPoint(x-(width/2)+1,y,0),FTPoint(2,0,0),FTGL::ALIGN_CENTER); //text doesn't transform, so use FTPoint
  font->Render(text.c_str(),-1,FTPoint(x-(width/2),y+1,0),FTPoint(2,0,0),FTGL::ALIGN_CENTER); //text doesn't transform, so use FTPoint

  
  glPopAttrib();
  glPopMatrix();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  glPushMatrix();
  glTranslatef(x,y,0);
    for(int index=0;index<=1;index++)
      {
	glBegin(GL_QUADS);
	glColor3f(1.0f,1.0f,1.0f);
	if(center)
	  {
	    glTexCoord2f(0.0f,1.0f);
	    glVertex3f(-w/2,index,0);
	    glTexCoord2f(1.0f,1.0f);
	    glVertex3f(w/2,index,0);
	    glTexCoord2f(1.0f,0.0f);
	    glVertex3f(w/2,h+index,0);
	    glTexCoord2f(0.0f,0.0f);
	    glVertex3f(-w/2,h+index,0);
	  }
	else
	  {
	    glTexCoord2f(0.0f,1.0f);
	    glVertex3f(0,index,0);
	    glTexCoord2f(1.0f,1.0f);
	    glVertex3f(w,index,0);
	    glTexCoord2f(1.0f,0.0f);
	    glVertex3f(w,h+index,0);
	    glTexCoord2f(0.0f,0.0f);
	    glVertex3f(0,h+index,0);
	  }
	glEnd();
      }
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
  */
}

bool GTEXT::logic(int step)
{
  switch(step)
    {
    case 0:
      break;
    default:
      return true;
      break;
    }
  return false;
}

void GTEXT::setText(string text_a)
{
  text=text_a;
  
  /*start=TTF_RenderText_Solid(font,text.c_str(),color(255,255,255));
  mid=SDL_CreateRGBSurface(0,start->w,start->h,32,0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
  SDL_BlitSurface(start,0,mid,0);

  //glGenTextures(1,&texture);
  //glBindTexture(GL_TEXTURE_2D,texture);
  glTexImage2D(GL_TEXTURE_2D,0,4,start->w,start->h,0,GL_BGRA,GL_UNSIGNED_BYTE,mid->pixels);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  w=start->w;
  h=start->h;

  SDL_FreeSurface(start);
  SDL_FreeSurface(mid);*/
}

void GTEXT::setFontSize(int size)
{
  //font->FaceSize(size);
}

SDL_Color GTEXT::color(int r,int g,int b)
{
  SDL_Color cl={r,g,b};
  return cl;
}

void GTEXT::clean()
{
  /*SDL_FreeSurface(start);
  SDL_FreeSurface(mid);
  TTF_CloseFont(font);*/
}
