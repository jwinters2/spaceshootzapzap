#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h> //usleep(250000)
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
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

void handleKeypress(GLFWwindow*,int,int,int,int);
void handleJoystick();
void quitGame(GLFWwindow*);

WORLD new_world;
box WindowSize;

int main(int argc, char** argv)
{
  //WORLD new_world;
  screen.w=640;
  screen.h=640;
  globalFrame=0;
  globalScore=0;
  int qwerty=100;
  srand(time(NULL));

  glfwInit();

  GLFWwindow* window=glfwCreateWindow(screen.w,screen.h,"space_shoot_zap_zap.exe",NULL,NULL);
  glfwMakeContextCurrent(window);

  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,screen.w,0,screen.h);

  glfwSetKeyCallback(window,handleKeypress);
  glfwSetWindowCloseCallback(window,quitGame);

  alutInit(&argc,argv);
  LoadALData();
  SetListenerValues();
  
  GTEXT pauseText("PAUSE",24,(screen.w/2)-62,(screen.h-24)/2,0,0);
  
  HIGHSCORE scoreBoard(24,80,screen.h-120,0,0);
  
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
      
      startMenuText.push_back(new GTEXT("PRESS ENTER OR 4 TO START",24,(screen.w/2)-300,(screen.h-24)/4,0,0));
      startMenuText.push_back(new GTEXT("WASD - ARROW KEYS:     MOVE",12,40,(screen.h-24)/2+20,0,0));
      startMenuText.push_back(new GTEXT("P:                     PAUSE",12,40,(screen.h-24)/2,0,0));
      startMenuText.push_back(new GTEXT("SPACE - BUTTON :       SHOOT",12,40,(screen.h-24)/2-20,0,0));
      startMenuText.push_back(new GTEXT("ESC:                   QUIT GAME LIKE A QUITTER",12,40,(screen.h-24)/2-40,0,0));
      startMenuText.push_back(new GTEXT("SPACE SHOOT",40,(screen.w/2)-220,(screen.h-24)*3/4+20,0,0));
      startMenuText.push_back(new GTEXT("ZAP-ZAP",40,(screen.w/2)-140,(screen.h-24)*3/4-20,0,0));

      scoreBoard.reset();
      
      objects.push_back(new PLAYER(new_world,screen.w/2,screen.h/2,0,0));
      objects.push_back(new GTEXT(new_world,("SCORE "+intToString(globalScore)),24,0,screen.h-24,0,0));
      //stars
      for(int i=0;i<50;i++)
	{
	  objects.push_back(new STAR(new_world,rand()%screen.w,rand()%screen.h,0,0));
	}
      
      while(playing)
	{
	  handleJoystick();
	  glfwPollEvents();
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
	  glfwSwapBuffers(window);
	  usleep(16667);
	}
    }
  
  return 0;
}

void handleKeypress(GLFWwindow* window, int key, int scancode, int action, int mods)
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

void handleJoystick()
{
  if(glfwJoystickPresent(GLFW_JOYSTICK_1)==GL_FALSE)
    {
      return;
    }
  joystick.attack=(glfwGetJoystickButtons(GLFW_JOYSTICK_1,&count)[0]==1);
  joystick.p=(glfwGetJoystickButtons(GLFW_JOYSTICK_1,&count)[9]==1);
  joystick.right=(glfwGetJoystickAxes(GLFW_JOYSTICK_1,&count)[0]==1);
  joystick.left=(glfwGetJoystickAxes(GLFW_JOYSTICK_1,&count)[0]==-1);
  joystick.up=(glfwGetJoystickAxes(GLFW_JOYSTICK_1,&count)[1]==-1);
  joystick.down=(glfwGetJoystickAxes(GLFW_JOYSTICK_1,&count)[1]==1);

  if(glfwGetJoystickButtons(GLFW_JOYSTICK_1,&count)[3]==1)
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
  
  joystick.attack_old=joystick.attack;
  joystick.p_old=joystick.p;
  joystick.right_old=joystick.right;
  joystick.left_old=joystick.left;
  joystick.up_old=joystick.up;
  joystick.down_old=joystick.down;

}

void quitGame(GLFWwindow*)
{
  glfwTerminate();
  KillALData();
  exit(0);
}