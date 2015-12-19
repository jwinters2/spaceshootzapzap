#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <GL/gl.h>
//#include <freetype2/freetype/config/ftheader.h>
//#include <freetype2/ft2build.h>
//#include <FTGL/ftgl.h>
//#include <FTGL/FTGLPixmapFont.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "person.h"
#include "object.h"
#include "world.h"
#include "text.h"
#include "highscore.h"
#include "coord.h"
#include "globals.h"
using namespace std;

HIGHSCORE::HIGHSCORE(int size_a,int x_a,int y_a,int xvel_a,int yvel_a)
  :OBJECT(x_a,y_a,xvel_a,yvel_a)
{
  enteringName=true;
  type="HIGHSCORES";
  nameToEnter="";
  layer=6;
  fontSize=size_a;
  cout<<"set scoreboard font"<<endl;

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
  cout<<"set scoreboard surface"<<endl;
  text="test";

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
  h=start->h;

  SDL_FreeSurface(start);
  SDL_FreeSurface(mid);*/

  scoreFile.open("scoreboard.txt");
  string scoreName,scoreScore;
  while(scoreFile>>scoreName>>scoreScore)
    {
      stringPair scorePair;
      scoreEntries.push_back(scorePair);
      scoreEntries.back().s1=scoreName;
      scoreEntries.back().s2=scoreScore;
    }
}

void HIGHSCORE::reset()
{
  enteringName=true;
  nameToEnter="";
  scoreEntries.clear();
  scoreFile.close();
  scoreFile.open("scoreboard.txt");
  string scoreName,scoreScore;
  while(scoreFile>>scoreName>>scoreScore)
    {
      stringPair scorePair;
      scoreEntries.push_back(scorePair);
      scoreEntries.back().s1=scoreName;
      scoreEntries.back().s2=scoreScore;
    }
}

void HIGHSCORE::render()
{
  int width;

  
  glClearColor(0.0f,0.0f,0.0f,0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  /*glPushMatrix();
  //glTranslatef(x,y,0);
  
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
  */
 
  glColor4d(1.0,1.0,1.0,1.0);
  for(int index=0;index<(scoreEntries.size()>11?11:scoreEntries.size());index++)
    {
      for(int lindex=0;lindex<scoreEntries.at(index).s1.length();lindex++)
	{
	  glyph->render(scoreEntries.at(index).s1.substr(lindex,1),(screen.w/4)-((glyph->width*scoreEntries.at(index).s1.length()/2))+(glyph->width*lindex),y-(30*index));
	}

      for(int lindex=0;lindex<scoreEntries.at(index).s2.length();lindex++)
	{
	  glyph->render(scoreEntries.at(index).s2.substr(lindex,1),(screen.w*3/5)-((glyph->width*scoreEntries.at(index).s2.length()/2))+(glyph->width*lindex),y-(30*index));
	}
    }

  switch(nameToEnter.length())
    {
    case 0:
      text="___";
      break;
    case 1:
      text=" __";
      break;
    case 2:
      text="  _";
      break;
    case 3:
      text="   ";
      break;
    }

  for(int lindex=0;lindex<text.length();lindex++)
    {
      glyph->render(text.substr(lindex,1),(screen.w/4)-((glyph->width*text.length()/2))+(glyph->width*lindex),y-390);
    }
  
  for(int lindex=0;lindex<nameToEnter.length();lindex++)
    {
      glyph->render(nameToEnter.substr(lindex,1),(screen.w/4)-((glyph->width*3/2))+(glyph->width*lindex),y-390);
    }

  //setText(intToString(globalScore),fontSize);
  //drawText(screen.w*3/4,y-390,1);

  for(int lindex=0;lindex<intToString(globalScore).length();lindex++)
    {
      glyph->render(intToString(globalScore).substr(lindex,1),(screen.w*3/5)-((glyph->width*intToString(globalScore).length()/2))+(glyph->width*lindex),y-390);
    }
  
  if(enteringName)
    {
      text="ENTER INITIALS";
    }
  else
    {
      text="PRESS ENTER TO PLAY AGAIN";
    }

  for(int lindex=0;lindex<text.length();lindex++)
    {
      glyph->render(text.substr(lindex,1),(screen.w/2)-((glyph->width*text.length()/2))+(glyph->width*lindex),y-430);
    }

  //glPopAttrib();
  //glPopMatrix();
}

bool HIGHSCORE::logic(int step)
{
  if(enteringName)
    {
      enterName();
      if(keys.enter&&!keys.enter_old)
	{
	  switch(nameToEnter.length())
	    {
	    case 0:
	      gameScoreBoard=false;
	      enteringName=false;
	      playing=false;
	      return false;
	      //nameToEnter="---";
	      //break;
	    case 1:
	      nameToEnter+="--";
	      break;
	    case 2:
	      nameToEnter+="-";
	      break;
	    }
	  scoreFile.close();
	  scoreFile.open("scoreboard.txt",ios::in|ios::out|ios::trunc);
	  
	  stringPair scorePair;
	  scoreEntries.push_back(scorePair);
	  scoreEntries.back().s1=nameToEnter;
	  scoreEntries.back().s2=intToString(globalScore);
	  std::sort(scoreEntries.begin(),scoreEntries.end(),sortScores);
	  for(int index=0;index<scoreEntries.size();index++)
	    {
	      scoreFile<<scoreEntries.at(index).s1<<" ";
	      scoreFile<<scoreEntries.at(index).s2<<"\n";
	    }
	  scoreFile.close();
	  enteringName=false;
	  //gameScoreBoard=0;
	}
    }
  else
    {
      if(keys.enter&&!keys.enter_old)
	{
	  playing=false;
	  gameScoreBoard=false;
	}
    }
  keys.enter_old=keys.enter;
  return false;
  /*
  switch(step)
    {
    case 0:
      enterName();
      break;
    default:
      return true;
      break;
    }
  return false;
  */
}

void HIGHSCORE::setFontSize(int size)
{
  fontSize=size;
}

void HIGHSCORE::enterName()
{
  if(nameToEnter.length()>0 && keys.backspace && !keys.backspace_old)
    {
      nameToEnter.erase(nameToEnter.end()-1,nameToEnter.end());
    }
  if(nameToEnter.length()>=3)
    {
      return;
    }
  if(keys.a && !keys.a_old){nameToEnter.append("A");}
  if(keys.b && !keys.b_old){nameToEnter.append("B");}
  if(keys.c && !keys.c_old){nameToEnter.append("C");}
  if(keys.d && !keys.d_old){nameToEnter.append("D");}
  if(keys.e && !keys.e_old){nameToEnter.append("E");}
  if(keys.f && !keys.f_old){nameToEnter.append("F");}
  if(keys.g && !keys.g_old){nameToEnter.append("G");}
  if(keys.h && !keys.h_old){nameToEnter.append("H");}
  if(keys.i && !keys.i_old){nameToEnter.append("I");}
  if(keys.j && !keys.j_old){nameToEnter.append("J");}
  if(keys.k && !keys.k_old){nameToEnter.append("K");}
  if(keys.l && !keys.l_old){nameToEnter.append("L");}
  if(keys.m && !keys.m_old){nameToEnter.append("M");}
  if(keys.n && !keys.n_old){nameToEnter.append("N");}
  if(keys.o && !keys.o_old){nameToEnter.append("O");}
  if(keys.p && !keys.p_old){nameToEnter.append("P");}
  if(keys.q && !keys.q_old){nameToEnter.append("Q");}
  if(keys.r && !keys.r_old){nameToEnter.append("R");}
  if(keys.s && !keys.s_old){nameToEnter.append("S");}
  if(keys.t && !keys.t_old){nameToEnter.append("T");}
  if(keys.u && !keys.u_old){nameToEnter.append("U");}
  if(keys.v && !keys.v_old){nameToEnter.append("V");}
  if(keys.w && !keys.w_old){nameToEnter.append("W");}
  if(keys.x && !keys.x_old){nameToEnter.append("X");}
  if(keys.y && !keys.y_old){nameToEnter.append("Y");}
  if(keys.z && !keys.z_old){nameToEnter.append("Z");}
 
  keys.a_old=keys.a;
  keys.b_old=keys.b;
  keys.c_old=keys.c;
  keys.d_old=keys.d;
  keys.e_old=keys.e;
  keys.f_old=keys.f;
  keys.g_old=keys.g;
  keys.h_old=keys.h;
  keys.i_old=keys.i;
  keys.j_old=keys.j;
  keys.k_old=keys.k;
  keys.l_old=keys.l;
  keys.m_old=keys.m;
  keys.n_old=keys.n;
  keys.o_old=keys.o;
  keys.p_old=keys.p;
  keys.q_old=keys.q;
  keys.r_old=keys.r;
  keys.s_old=keys.s;
  keys.t_old=keys.t;
  keys.u_old=keys.u;
  keys.v_old=keys.v;
  keys.w_old=keys.w;
  keys.x_old=keys.x;
  keys.y_old=keys.y;
  keys.z_old=keys.z;
  keys.backspace_old=keys.backspace;
}

void HIGHSCORE::setText(string text_a,int size_a,int length_a)
{
  string textToSet=text_a;
  while(textToSet.length()<length_a)
    {
      textToSet.append("_");
    }
  if(textToSet.length()==0)
    {
      textToSet=" ";
    }
  //cout<<"start setText"<<endl;
  //SDL_Surface* start;
  //SDL_Surface* mid;

  //cout<<"start making surfaces: "<<textToSet<<" ("<<textToSet.length()<<")"<<endl;
  start=TTF_RenderText_Solid(font,textToSet.c_str(),color(255,255,255));
  mid=SDL_CreateRGBSurface(0,start->w,start->h,32,0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
  SDL_BlitSurface(start,0,mid,0);

  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);
  glTexImage2D(GL_TEXTURE_2D,0,4,start->w,start->h,0,GL_BGRA,GL_UNSIGNED_BYTE,mid->pixels);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  w=start->w;
  h=start->h;

  SDL_FreeSurface(start);
  SDL_FreeSurface(mid);
}

void HIGHSCORE::drawText(int x_a,int y_a,bool center)
{
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  glPushMatrix();
  glTranslatef(x_a,y_a,0);
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
}

SDL_Color HIGHSCORE::color(int r,int g,int b)
{
  SDL_Color cl={r,g,b};
  return cl;
}

void HIGHSCORE::clean()
{
  //SDL_FreeSurface(start);
  //SDL_FreeSurface(mid);
  //TTF_CloseFont(font);
}
