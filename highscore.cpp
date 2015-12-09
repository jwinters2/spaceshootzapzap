#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <GL/gl.h>
//#include <freetype2/freetype/config/ftheader.h>
//#include <freetype2/ft2build.h>
#include <FTGL/ftgl.h>
#include <FTGL/FTGLPixmapFont.h>
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
  cout<<"set text"<<endl;
  font = new FTPixmapFont("emulogic.ttf");
  cout<<"set font"<<endl;
  font->FaceSize(size_a);
  cout<<"end text constructor"<<endl;

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

  glClearColor(0.0f,0.0f,0.0f,0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();
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
  */
 
  glColor4d(1.0,1.0,1.0,1.0);
  for(int index=0;index<(scoreEntries.size()>11?11:scoreEntries.size());index++)
    {
      font->Render(scoreEntries.at(index).s1.c_str(),-1,FTPoint(x,y-(30*index),0)); //text doesn't transform, so use FTPoint
      font->Render(scoreEntries.at(index).s2.c_str(),-1,FTPoint(x+screen.w/2-40,y-(30*index),0)); //text doesn't transform, so use FTPoint
    }
  switch(nameToEnter.length())
    {
    case 0:
      font->Render("___",-1,FTPoint(x,y-390,0)); //text doesn't transform, so use FTPoint
      break;
    case 1:
      font->Render(" __",-1,FTPoint(x,y-390,0)); //text doesn't transform, so use FTPoint
      break;
    case 2:
      font->Render("  _",-1,FTPoint(x,y-390,0)); //text doesn't transform, so use FTPoint
      break;
    }
  font->Render(nameToEnter.c_str(),-1,FTPoint(x,y-390,0)); //text doesn't transform, so use FTPoint
  font->Render(intToString(globalScore).c_str(),-1,FTPoint(x+screen.w/2-40,y-390,0)); //text doesn't transform, so use FTPoint
  if(enteringName)
    {
      font->Render("ENTER INITIALS",-1,FTPoint((screen.w/2)-180,y-430,0));
    }
  else
    {
      font->Render("PRESS ENTER TO PLAY AGAIN",-1,FTPoint((screen.w/2)-280,y-430,0));
    }

  glPopAttrib();
  glPopMatrix();
}

bool HIGHSCORE::logic(int step)
{
  if(enteringName)
    {
      enterName();
      if(keys.enter)
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
	  gameScoreBoard=false;
	  enteringName=false;
	  playing=false;
	  //gameScoreBoard=0;
	}
    }
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
  font->FaceSize(size);
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
  if(keys.a && !keys.a_old){nameToEnter.append("a");}
  if(keys.b && !keys.b_old){nameToEnter.append("b");}
  if(keys.c && !keys.c_old){nameToEnter.append("c");}
  if(keys.d && !keys.d_old){nameToEnter.append("d");}
  if(keys.e && !keys.e_old){nameToEnter.append("e");}
  if(keys.f && !keys.f_old){nameToEnter.append("f");}
  if(keys.g && !keys.g_old){nameToEnter.append("g");}
  if(keys.h && !keys.h_old){nameToEnter.append("h");}
  if(keys.i && !keys.i_old){nameToEnter.append("i");}
  if(keys.j && !keys.j_old){nameToEnter.append("j");}
  if(keys.k && !keys.k_old){nameToEnter.append("k");}
  if(keys.l && !keys.l_old){nameToEnter.append("l");}
  if(keys.m && !keys.m_old){nameToEnter.append("m");}
  if(keys.n && !keys.n_old){nameToEnter.append("n");}
  if(keys.o && !keys.o_old){nameToEnter.append("o");}
  if(keys.p && !keys.p_old){nameToEnter.append("p");}
  if(keys.q && !keys.q_old){nameToEnter.append("q");}
  if(keys.r && !keys.r_old){nameToEnter.append("r");}
  if(keys.s && !keys.s_old){nameToEnter.append("s");}
  if(keys.t && !keys.t_old){nameToEnter.append("t");}
  if(keys.u && !keys.u_old){nameToEnter.append("u");}
  if(keys.v && !keys.v_old){nameToEnter.append("v");}
  if(keys.w && !keys.w_old){nameToEnter.append("w");}
  if(keys.x && !keys.x_old){nameToEnter.append("x");}
  if(keys.y && !keys.y_old){nameToEnter.append("y");}
  if(keys.z && !keys.z_old){nameToEnter.append("z");}
 
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
