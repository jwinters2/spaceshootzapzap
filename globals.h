#pragma once
#define pi 3.1415926535
#include <cstdlib> //atoi
#include <string>
#include <vector>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

struct box
{
  int w;
  int h;
};

struct keyboard
{
  bool up,up_old;
  bool down,down_old;
  bool left,left_old;
  bool right,right_old;
  bool attack,attack_old;
  bool enter,enter_old;
  bool a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,backspace;
  bool a_old,b_old,c_old,d_old,e_old,f_old,g_old,h_old,i_old,j_old,k_old,l_old,m_old,n_old,o_old,p_old,q_old,r_old,s_old,t_old,u_old,v_old,w_old,x_old,y_old,z_old,backspace_old;
  keyboard()
  {
    up=0;
    down=0;
    left=0;
    right=0;
    attack=0;
    enter=0;
    a=0;
    b=0;
    c=0;
    d=0;
    e=0;
    f=0;
    g=0;
    h=0;
    i=0;
    j=0;
    k=0;
    l=0;
    m=0;
    n=0;
    o=0;
    p=0;
    q=0;
    r=0;
    s=0;
    t=0;
    u=0;
    v=0;
    w=0;
    x=0;
    y=0;
    z=0;
  }
};

struct stringPair
{
  std::string s1;
  std::string s2;
};

struct soundFile
{
  std::string fileName;
  ALboolean loop;
};

extern keyboard keys;
extern keyboard joystick;
extern box screen;
extern bool playing;
extern int globalFrame;
extern int attackFrame;
extern int globalScore;
extern bool start_menu;
extern bool gamePause;
extern bool gameScoreBoard;
extern int count;
extern const unsigned char* axes;
extern const float* dpad;
extern std::vector<ALuint> Source,Buffer;
extern ALfloat SourcePos[];
extern ALfloat SourceVel[];
extern ALfloat ListenerPos[];
extern ALfloat ListenerVel[];
extern ALfloat ListenerOri[];

void quitGame();
float getDir(float,float);
float dotProduct(float,float,float,float);
bool collideCircles(float,float,float,float,float);
std::string intToString(int);
std::string leadingZeros(int,int);
ALboolean LoadALData();
void SetListenerValues();
void KillALData();
soundFile soundFileInit(std::string,ALboolean);
bool sortScores(stringPair,stringPair);
