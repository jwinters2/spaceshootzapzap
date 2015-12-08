#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <GL/gl.h>
//#include <freetype2/freetype/config/ftheader.h>
//#include <freetype2/ft2build.h>
#include <FTGL/ftgl.h>
#include <FTGL/FTGLPixmapFont.h>
#include "person.h"
#include "object.h"
#include "world.h"
#include "text.h"
#include "coord.h"
#include "globals.h"
using namespace std;

GTEXT::GTEXT(WORLD& world_a,string text_a,int size_a,int x_a,int y_a,int xvel_a,int yvel_a)
  :OBJECT(world_a,x_a,y_a,xvel_a,yvel_a)
{
  type="TEXT";
  layer=7;
  cout<<"begin text constructor"<<endl;
  text=text_a;
  cout<<"set text"<<endl;
  font = new FTPixmapFont("emulogic.ttf");
  cout<<"set font"<<endl;
  font->FaceSize(size_a);
  cout<<"end text constructor"<<endl;
}

GTEXT::GTEXT(string text_a,int size_a,int x_a,int y_a,int xvel_a,int yvel_a)
  :OBJECT(x_a,y_a,xvel_a,yvel_a)
{
  type="TEXT";
  layer=6;
  cout<<"begin text constructor"<<endl;
  text=text_a;
  cout<<"set text"<<endl;
  font = new FTPixmapFont("emulogic.ttf");
  cout<<"set font"<<endl;
  font->FaceSize(size_a);
  cout<<"end text constructor"<<endl;
}

void GTEXT::render()
{
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
  font->Render(text.c_str(),-1,FTPoint(x,y,0)); //text doesn't transform, so use FTPoint
  glPopAttrib();
  glPopMatrix();
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
}

void GTEXT::setFontSize(int size)
{
  font->FaceSize(size);
}