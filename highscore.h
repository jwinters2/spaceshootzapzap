#pragma once
#include <fstream>
#include <cstring>
#include <GL/gl.h>
#include <FTGL/ftgl.h>

#include "object.h"
#include "text.h"
#include "globals.h"

class HIGHSCORE:public OBJECT
{
 private:
  FTBitmapFont * font;
 public:
  string text;
  string nameToEnter;
  bool enteringName;
  fstream scoreFile;
  vector<stringPair> scoreEntries;
  HIGHSCORE(int=12,int=0,int=0,int=0,int=0);
  void render();
  bool logic(int);
  void setFontSize(int);
  void enterName();
  void reset();
};
