#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
//#include <AL/al.h>
//#include <AL/alc.h>
//#include <AL/alut.h>
#include "glyph.h"
#include "globals.h"

box screen;

struct keyboard;
keyboard keys;
keyboard joystick;
//keys.up=false;
//keys.down=false;
//keys.left=false;
//keys.right=false;

int globalFrame;
int attackFrame;
int globalScore;
bool playing=1;
bool quit=0;
bool start_menu=1;
bool gamePause=0;
bool gameScoreBoard=0;

Mix_Music* music;
Mix_Chunk* shootWAV;
Mix_Chunk* explosionWAV;
Mix_Chunk* beepbeepbeepWAV;
Mix_Chunk* hitWAV;
Mix_Chunk* heatingWAV;
Mix_Chunk* explosionBigWAV;

SDL_Surface* window;

GLYPH glyph_18;
GLYPH glyph_36;
GLYPH glyph_60;

int count;
//const unsigned char* axes=glfwGetJoystickButtons(GLFW_JOYSTICK_1,&count);
//const float* dpad=glfwGetJoystickAxes(GLFW_JOYSTICK_1,&count);


void quitGame()
{
  playing=false;
  quit=true;
  /* //glfwTerminate();
  std::cout<<"killing AL data"<<std::endl;
  KillALData();
  TTF_Quit();
  std::cout<<"freeing surface"<<std::endl;
  SDL_FreeSurface(window);
  std::cout<<"quitting SDL"<<std::endl;
  SDL_Quit();
  std::cout<<"exiting"<<std::endl;
  exit(0);*/
}

void initSounds()
{
  music=Mix_LoadMUS("music.wav");
  shootWAV=Mix_LoadWAV("shoot.wav");
  explosionWAV=Mix_LoadWAV("explosion.wav");
  beepbeepbeepWAV=Mix_LoadWAV("beepbeepbeep.wav");
  hitWAV=Mix_LoadWAV("hit.wav");
  heatingWAV=Mix_LoadWAV("heating.wav");
  explosionBigWAV=Mix_LoadWAV("explosion_big.wav");
}

float getDir(float x,float y)
{
  return (atan2(y,x)*180/pi);
}

float dotProduct(float x1,float y1,float x2,float y2)
{
  return ((x1*x2)+(y1*y2));
};

bool collideCircles(float x1,float y1,float x2,float y2,float dist)
{
  return(sqrt(pow((x2-x1),2)+pow((y2-y1),2))<=dist);
}

std::string intToString(int x)
{
  std::ostringstream stream;
  stream<<std::setw(8)<<std::setfill('0')<<x;
  return stream.str();
}

std::string leadingZeros(int num,int length)
{
  std::string str="";
  int zeros=0;
  num=abs(num);
  for(int index=1;index<8;index++)
    {
      if(num<pow(10,index))
	{
	  zeros++;
	}
    }
  str.append("0",length-zeros);
  return "";
}

void KillALData()
{
  Mix_FreeMusic(music);
  Mix_FreeChunk(shootWAV);
  Mix_FreeChunk(explosionWAV);
  Mix_FreeChunk(beepbeepbeepWAV);
  Mix_FreeChunk(hitWAV);
  Mix_FreeChunk(heatingWAV);
  Mix_FreeChunk(explosionBigWAV);
  Mix_CloseAudio();
}

bool sortScores(stringPair a,stringPair b)
{
  return (atoi(a.s2.c_str())>atoi(b.s2.c_str()));
}
