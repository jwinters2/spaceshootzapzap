#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h> //usleep(250000)
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GLFW/glfw3.h>
#include <AL/al.h>
#include <AL/alc.h>
//#include <AL/alu.h>
#include <AL/alut.h>
#include "object.h"
//#include "graphics.h"
#include "world.h"
#include "person.h"
#include "player.h"
#include "globals.h"
#include "enemynormal.h"
#include "enemyacc.h"
#include "star.h"
#include "text.h"
#include "highscore.h"
//#include "graphics.h"
using namespace std;

WORLD new_world;
box WindowSize;
const Uint8* keystate=SDL_GetKeyState(NULL);
SDL_Joystick* joy;
SDL_Event event;

void handleKeypress();
void handleJoystick();

int main(int argc, char** argv)
{
  //WORLD new_world;
  screen.w=640;
  screen.h=640;
  globalFrame=0;
  globalScore=0;
  int qwerty=100;
  srand(time(NULL));

  SDL_Init(SDL_INIT_EVERYTHING);
  window=SDL_SetVideoMode(screen.w,screen.h,32,SDL_DOUBLEBUF|SDL_OPENGL);
  TTF_Init();
  SDL_WM_SetCaption("space_shoot_zap_zap.exe", NULL );

  //glfwInit();

  //FWwindow* window=glfwCreateWindow(screen.w,screen.h,"space_shoot_zap_zap.exe",NULL,NULL);
  //glfwMakeContextCurrent(window);

  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,screen.w,0,screen.h);

  //glfwSetKeyCallback(window,handleKeypress);
  //glfwSetWindowCloseCallback(window,quitGame);

  alutInit(&argc,argv);
  LoadALData();
  SetListenerValues();

  joy=SDL_JoystickOpen(0);
  
  GTEXT pauseText("PAUSE",32,(screen.w/2),(screen.h-24)/2,0,0,1);
  
  HIGHSCORE scoreBoard(36,80,screen.h-120,0,0);
  
  vector<GTEXT*> startMenuText;
  vector<OBJECT*> objects;
  
  while(true)
    {
      glClearColor(0.0f,0.0f,0.0f,0.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      playing=1;
      start_menu=1;
      gamePause=0;
      gameScoreBoard=0;
      startMenuText.clear();
      objects.clear();
      new_world.objects.clear();
      globalFrame=0;
      globalScore=0;
      alSourcePlay(Source.at(0));
      
      startMenuText.push_back(new GTEXT("PRESS ENTER OR 10 TO START",36,(screen.w/2),(screen.h-24)/4,0,0,1));
      startMenuText.push_back(new GTEXT("WASD - ARROW KEYS:     MOVE",18,(screen.w/2)-250,(screen.h-24)/2+20,0,0,0));
      startMenuText.push_back(new GTEXT("P - BUTTON 9     :     PAUSE",18,(screen.w/2)-250,(screen.h-24)/2,0,0,0));
      startMenuText.push_back(new GTEXT("SPACE - BUTTON 1 :     SHOOT",18,(screen.w/2)-250,(screen.h-24)/2-20,0,0,0));
      startMenuText.push_back(new GTEXT("ESC              :     QUIT GAME LIKE A QUITTER",18,(screen.w/2)-250,(screen.h-24)/2-40,0,0,0));
      startMenuText.push_back(new GTEXT("SPACE SHOOT",60,(screen.w/2),(screen.h-24)*3/4+24,0,0,1));
      startMenuText.push_back(new GTEXT("ZAP-ZAP",60,(screen.w/2),(screen.h-24)*3/4-24,0,0,1));

      scoreBoard.reset();
      
      objects.push_back(new PLAYER(new_world,screen.w/2,screen.h/2,0,0));
      objects.push_back(new GTEXT(new_world,("SCORE "+intToString(globalScore)),36,0,screen.h-36,0,0,0));
      //stars
      for(int i=0;i<50;i++)
	{
	  objects.push_back(new STAR(new_world,rand()%screen.w,rand()%screen.h,0,0));
	}
      
      while(playing)
	{
	  handleJoystick();
	  handleKeypress();
	  //glfwPollEvents();
	  if(start_menu)
	    {
	      for(int index=0;index<startMenuText.size();index++)
		{
		  startMenuText.at(index)->render();
		}
	    }
	  else if(gamePause)
	    {
	      pauseText.render();
	      while(!gamePause)
		{
		  handleKeypress();
		}
	    }
	  else if(gameScoreBoard)
	    {
	      alSourceStop(Source.at(0));
	      alSourceStop(Source.at(3));
	      scoreBoard.logic(0);
	      scoreBoard.render();
	    }
	  else
	    {
	      new_world.gamelogic();
	      new_world.render();
	    }
	  SDL_GL_SwapBuffers();
	  SDL_Flip(window);
	  //glfwSwapBuffers(window);
	  /*
	  while(glfwGetTime()<(double)0.01666667)
	    {
	    }
	  glfwSetTime(0);
	  */
	}
    }
  
  return 0;
}

void handleKeypress()
{
  //* while(SDL_PollEvent(&event))
  SDL_PollEvent(&event);
    {
      switch(event.type)
	{
	case SDL_QUIT:
	  quitGame();
	}
    }//*/
  SDL_PumpEvents();
  SDL_JoystickUpdate();
  //cout<<SDL_JoystickOpened(0)<<endl;
  if(keystate[SDLK_ESCAPE])
    {
      cout<<"escape was pressed"<<endl;
      quitGame();
    }
  if(keystate[SDLK_RETURN] || SDL_JoystickGetButton(joy,9))
    {
      start_menu=0;
    }
  keys.up   =(keystate[SDLK_UP]    || keystate[SDLK_w] || SDL_JoystickGetAxis(joy,1)<0);
  keys.down =(keystate[SDLK_DOWN]  || keystate[SDLK_s] || SDL_JoystickGetAxis(joy,1)>0);
  keys.left =(keystate[SDLK_LEFT]  || keystate[SDLK_a] || SDL_JoystickGetAxis(joy,0)<0);
  keys.right=(keystate[SDLK_RIGHT] || keystate[SDLK_d] || SDL_JoystickGetAxis(joy,0)>0);
  keys.enter=keystate[SDLK_RETURN];
  keys.attack=(keystate[SDLK_SPACE] || SDL_JoystickGetButton(joy,0));
  if(keys.attack && !keys.attack_old)
    {
      attackFrame=globalFrame;
    }
  keys.a=keystate[SDLK_a];
  keys.b=keystate[SDLK_b];
  keys.c=keystate[SDLK_c];
  keys.d=keystate[SDLK_d];
  keys.e=keystate[SDLK_e];
  keys.f=keystate[SDLK_f];
  keys.g=keystate[SDLK_g];
  keys.h=keystate[SDLK_h];
  keys.i=keystate[SDLK_i];
  keys.j=keystate[SDLK_j];
  keys.k=keystate[SDLK_k];
  keys.l=keystate[SDLK_l];
  keys.m=keystate[SDLK_m];
  keys.n=keystate[SDLK_n];
  keys.o=keystate[SDLK_o];
  keys.p=(keystate[SDLK_p]||((!gameScoreBoard) && SDL_JoystickGetButton(joy,8)));
  keys.q=keystate[SDLK_q];
  keys.r=keystate[SDLK_r];
  keys.s=keystate[SDLK_s];
  keys.t=keystate[SDLK_t];
  keys.u=keystate[SDLK_u];
  keys.v=keystate[SDLK_v];
  keys.w=keystate[SDLK_w];
  keys.x=keystate[SDLK_x];
  keys.y=keystate[SDLK_y];
  keys.z=keystate[SDLK_z];
  keys.backspace=keystate[SDLK_BACKSPACE];
  if (keys.p&&(!keys.p_old)&&(!gameScoreBoard)&&(!start_menu))
    {
      if(gamePause)
	{
	  alSourcePlay(Source.at(0));
	}
      else
	{
	  alSourcePause(Source.at(0));
	}
      gamePause=!gamePause;
    }

  keys.attack_old=keys.attack;
  if(!gameScoreBoard){keys.p_old=keys.p;}
  keys.right_old=keys.right;
  keys.left_old=keys.left;
  keys.up_old=keys.up;
  keys.down_old=keys.down;
  keys.enter_old=keys.enter;
  //keys.backspace_old=keys.backspace;
}
/*
{
  //int joystick=glfwJoystickPresent(GLFW_JOYSTICK_1);
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
      quitGame();
      KillALData();
      exit(0);
    }
  if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
    {
      start_menu=0;
    }
  if (key == GLFW_KEY_P && action == GLFW_PRESS &&(!gameScoreBoard)&&(!start_menu))
    {
      if(gamePause)
	{
	  alSourcePlay(Source.at(0));
	}
      else
	{
	  alSourcePause(Source.at(0));
	}
      gamePause=!gamePause;
    }
  if (key==GLFW_KEY_UP || key==GLFW_KEY_W)
    {
      keys.up=action;
    }
  if (key==GLFW_KEY_DOWN || key==GLFW_KEY_S)
    {
      keys.down=action;
    }
  if (key==GLFW_KEY_LEFT || key==GLFW_KEY_A)
    {
      keys.left=action;
    }
  if (key==GLFW_KEY_RIGHT || key==GLFW_KEY_D)
    {
      keys.right=action;
    }
  if(key==GLFW_KEY_ENTER)
    {
      keys.enter=action;
    }
  if(key==GLFW_KEY_A){keys.a=action;}
  if(key==GLFW_KEY_B){keys.b=action;}
  if(key==GLFW_KEY_C){keys.c=action;}
  if(key==GLFW_KEY_D){keys.d=action;}
  if(key==GLFW_KEY_E){keys.e=action;}
  if(key==GLFW_KEY_F){keys.f=action;}
  if(key==GLFW_KEY_G){keys.g=action;}
  if(key==GLFW_KEY_H){keys.h=action;}
  if(key==GLFW_KEY_I){keys.i=action;}
  if(key==GLFW_KEY_J){keys.j=action;}
  if(key==GLFW_KEY_K){keys.k=action;}
  if(key==GLFW_KEY_L){keys.l=action;}
  if(key==GLFW_KEY_M){keys.m=action;}
  if(key==GLFW_KEY_N){keys.n=action;}
  if(key==GLFW_KEY_O){keys.o=action;}
  if(key==GLFW_KEY_P){keys.p=action;}
  if(key==GLFW_KEY_Q){keys.q=action;}
  if(key==GLFW_KEY_R){keys.r=action;}
  if(key==GLFW_KEY_S){keys.s=action;}
  if(key==GLFW_KEY_T){keys.t=action;}
  if(key==GLFW_KEY_U){keys.u=action;}
  if(key==GLFW_KEY_V){keys.v=action;}
  if(key==GLFW_KEY_W){keys.w=action;}
  if(key==GLFW_KEY_X){keys.x=action;}
  if(key==GLFW_KEY_Y){keys.y=action;}
  if(key==GLFW_KEY_Z){keys.z=action;}
  if(key==GLFW_KEY_BACKSPACE){keys.backspace=action;}
  
  if(key==GLFW_KEY_SPACE)
    {
      if(keys.attack==0 && action==1)
	{
	  attackFrame=globalFrame;
	}
      keys.attack=action; 
    }
}
*/

void handleJoystick()
{
}
/*
{
  if(glfwJoystickPresent(GLFW_JOYSTICK_1)==GL_FALSE)
    {
      return;
    }
  joystick.attack=(glfwGetJoystickButtons(GLFW_JOYSTICK_1,&count)[0]==1);
  joystick.p=(glfwGetJoystickButtons(GLFW_JOYSTICK_1,&count)[8]==1);
  joystick.right=(glfwGetJoystickAxes(GLFW_JOYSTICK_1,&count)[0]==1);
  joystick.left=(glfwGetJoystickAxes(GLFW_JOYSTICK_1,&count)[0]==-1);
  joystick.up=(glfwGetJoystickAxes(GLFW_JOYSTICK_1,&count)[1]==-1);
  joystick.down=(glfwGetJoystickAxes(GLFW_JOYSTICK_1,&count)[1]==1);
  joystick.enter=(glfwGetJoystickButtons(GLFW_JOYSTICK_1,&count)[9]==1);

  if(glfwGetJoystickButtons(GLFW_JOYSTICK_1,&count)[9]==1)
    {
      start_menu=0;
    }
  if(joystick.p==1&&joystick.p_old==0 &&(!gameScoreBoard)&&(!start_menu))
    {
      if(gamePause)
	{
	  alSourcePlay(Source.at(0));
	}
      else
	{
	  alSourcePause(Source.at(0));
	}
      gamePause=!gamePause;
    }      
  if(joystick.attack!=joystick.attack_old)
    {
      keys.attack=joystick.attack;
      attackFrame=globalFrame;
    }
  if(joystick.right!=joystick.right_old)
    {
      keys.right=joystick.right;
    }
  if(joystick.left!=joystick.left_old)
    {
      keys.left=joystick.left;
    }
  if(joystick.up!=joystick.up_old)
    {
      keys.up=joystick.up;
    }
  if(joystick.down!=joystick.down_old)
    {
      keys.down=joystick.down;
    }
  if(joystick.enter!=joystick.enter_old)
    {
      keys.enter=joystick.enter;
    }
  
  joystick.attack_old=joystick.attack;
  joystick.p_old=joystick.p;
  joystick.right_old=joystick.right;
  joystick.left_old=joystick.left;
  joystick.up_old=joystick.up;
  joystick.down_old=joystick.down;
  joystick.enter_old=joystick.enter;
}
*/
