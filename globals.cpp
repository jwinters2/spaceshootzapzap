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
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
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
bool start_menu=1;
bool gamePause=0;
bool gameScoreBoard=0;

std::vector<ALuint> Source,Buffer;
ALfloat SourcePos[]={0.0,0.0,0.0};
ALfloat SourceVel[]={0.0,0.0,0.0};
ALfloat ListenerPos[]={0.0,0.0,0.0};
ALfloat ListenerVel[]={0.0,0.0,0.0};
ALfloat ListenerOri[]={0.0,0.0,-1.0,0.0,1.0,0.0};

SDL_Surface* window;

int count;
//const unsigned char* axes=glfwGetJoystickButtons(GLFW_JOYSTICK_1,&count);
//const float* dpad=glfwGetJoystickAxes(GLFW_JOYSTICK_1,&count);


void quitGame()
{
  //glfwTerminate();
  std::cout<<"killing AL data"<<std::endl;
  KillALData();
  TTF_Quit();
  std::cout<<"freeing surface"<<std::endl;
  SDL_FreeSurface(window);
  std::cout<<"quitting SDL"<<std::endl;
  SDL_Quit();
  std::cout<<"exiting"<<std::endl;
  exit(0);
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

ALboolean LoadALData()
{
  ALenum format;
  ALsizei size;
  ALvoid* data;
  ALsizei freq;
  ALboolean loop;

  std::vector<soundFile> sFiles;
  sFiles.push_back(soundFileInit("music.wav",AL_TRUE));
  sFiles.push_back(soundFileInit("shoot.wav",AL_FALSE));
  sFiles.push_back(soundFileInit("explosion.wav",AL_FALSE));
  sFiles.push_back(soundFileInit("beepbeepbeep.wav",AL_TRUE));
  sFiles.push_back(soundFileInit("hit.wav",AL_FALSE));
  sFiles.push_back(soundFileInit("heating.wav",AL_FALSE));
  sFiles.push_back(soundFileInit("explosion_big.wav",AL_FALSE));

  for(int index=0;index<sFiles.size();index++)
    {
      Buffer.push_back(0);
      alGenBuffers(1,&Buffer.at(index));
      Buffer.at(index)=alutCreateBufferFromFile(sFiles.at(index).fileName.c_str());
    }
  /*
    alutLoadWAVFile("music.wav",&format,&size,&data,&freq,&loop);
    alBufferData(Buffer,format,data,size,freq);
    alutUnloadWAV(format,data,size,freq);
  */
  for(int index=0;index<Buffer.size();index++)
    {
      Source.push_back(0);
      alGenSources(1,&Source.at(index));
      
      alSourcei(Source.at(index),AL_BUFFER,Buffer.at(index));
      alSourcef(Source.at(index),AL_PITCH,1.0f);
      alSourcef(Source.at(index),AL_GAIN,1.0f);
      alSourcefv(Source.at(index),AL_POSITION,SourcePos);
      alSourcefv(Source.at(index),AL_VELOCITY,SourceVel);
      alSourcei(Source.at(index),AL_LOOPING,sFiles.at(index).loop);
    }
  
  return AL_TRUE;
}

void SetListenerValues()
{
  alListenerfv(AL_POSITION,ListenerPos);
  alListenerfv(AL_VELOCITY,ListenerVel);
  alListenerfv(AL_ORIENTATION,ListenerOri);
}

void KillALData()
{
  for(int index=0;index<Buffer.size();index++)
    {
      alDeleteBuffers(1,&Buffer.at(index));
    }
  for(int index=0;index<Source.size();index++)
    {
      alDeleteSources(1,&Source.at(index));
    }
  alutExit();
}

soundFile soundFileInit(std::string fileName_a,ALboolean loop_a)
{
  soundFile sf;
  sf.fileName=fileName_a;
  sf.loop=loop_a;
  return sf;
}

bool sortScores(stringPair a,stringPair b)
{
  return (atoi(a.s2.c_str())>atoi(b.s2.c_str()));
}
