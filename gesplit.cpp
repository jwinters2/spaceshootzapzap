#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
//#include <unistd.h> //usleep(250000)
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GLFW/glfw3.h>
//#include <AL/al.h>
//#include <AL/alc.h>
//#include <AL/alu.h>
//#include <AL/alut.h>
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
#include "glyph.h"
//#include "graphics.h"
using namespace std;

//I blame microsoft for making me need this.
extern "C" {FILE __iob_func[3]={*stdin,*stdout,*stderr};}

WORLD new_world;
box WindowSize;
const Uint8* keystate=SDL_GetKeyboardState(NULL);
SDL_Joystick* joy;
SDL_Event event;
bool fullscreen;
int monitor;

void handleKeypress();
void handleJoystick();

int main(int argc, char** argv)
{
  SDL_DisplayMode display;
  if((argc==3 || argc==2) && strcmp(argv[1],"-f")==0)
  {
    fullscreen=true;
		if(argc==3)
		{
			monitor=atoi(argv[2]);
		}
		else
		{
			monitor=0;
		}
  }
  else
  {
    fullscreen=false;
  }

  if(argc==3)
  {
    screen.w=atoi(argv[1]);  
    screen.h=atoi(argv[2]);  
  }
  else
  {
    screen.w=640;
    screen.h=640;
  }
  //WORLD new_world;
  globalFrame=0;
  globalScore=0;
  int qwerty=100;
  srand(time(NULL));

  SDL_Init(SDL_INIT_EVERYTHING);
  window=SDL_CreateWindow("spaceshootzapzap.exe",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,screen.w,screen.h,SDL_WINDOW_OPENGL);

  if(fullscreen)
  {
    SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GetCurrentDisplayMode(monitor,&display);
    screen.w=display.w;
    screen.h=display.h;

  }
  
  SDL_GLContext glcontext=SDL_GL_CreateContext(window);
  TTF_Init();
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
  long timer=0;

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

  Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
  initSounds();
  //alutInit(&argc,argv);
  //LoadALData();
  //SetListenerValues();

  joy=SDL_JoystickOpen(0);

  glyph_18.init(18);
  glyph_36.init(36);
  glyph_60.init(60);
  
  GTEXT pauseText("PAUSE",32,(screen.w/2),(screen.h-24)/2,0,0,1);
  
  HIGHSCORE scoreBoard(36,80,screen.h-120,0,0);
  
  vector<GTEXT*> startMenuText;
  vector<OBJECT*> objects;
  
  while(!quit)
    {
      glClearColor(0.0f,0.0f,0.0f,0.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      playing=1;
      start_menu=1;
      gamePause=0;
      gameScoreBoard=0;
      for(int index=0;index<startMenuText.size();index++)
	{
	  startMenuText.at(index)->clean();
	  delete startMenuText.at(index);
	}
      for(int index=0;index<objects.size();index++)
	{
	  if(objects.at(index)->type.compare("TYPE")==0)
	    {
	      objects.at(index)->clean();
	      delete startMenuText.at(index);
	    }
	}
      startMenuText.clear();
      objects.clear();
      new_world.objects.clear();
      globalFrame=0;
      globalScore=0;
      Mix_PlayMusic(music,-1);      
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
      for(int i=0;i<(50*screen.w*screen.h)/(409600);i++)
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
	      Mix_HaltMusic();
	      Mix_HaltChannel(-1);
	      scoreBoard.logic(0);
	      scoreBoard.render();
	    }
	  else
	    {
	      new_world.gamelogic();
	      new_world.render();
	    }
	  SDL_GL_SwapWindow(window);
	  glClear(0);
	  //SDL_Flip(window);
	  if((SDL_GetTicks()-timer)<1000.0f/60)
	    {
	      SDL_Delay((1000.0f/60)-(SDL_GetTicks()-timer));
	    }
	  //cout<<1000/(SDL_GetTicks()-timer)<<" fps"<<endl;
	  fps=1000.0f/(SDL_GetTicks()-timer);
	  cout<<"fps: "<<fps<<endl;
	  timer=SDL_GetTicks();
	}
    }
  cout<<"KillAlData()"<<endl;
  KillALData();
  cout<<"startMenuText: "<<startMenuText.size()<<endl;
  for(int index=0;index<startMenuText.size();index++)
    {
      //cout<<"startMenuText.at("<<index<<")"<<endl;
      startMenuText.at(index)->clean();
    }
  cout<<"objects"<<endl;
  for(int index=0;index<objects.size();index++)
    {
      //cout<<"objects.at("<<index<<")"<<endl;
      if(objects.at(index)->type.compare("TEXT")==0)
	{
	  objects.at(index)->clean();
	}
    }
  SDL_GL_DeleteContext(glcontext);
  cout<<"scoreBoard.clean()"<<endl;
  scoreBoard.clean();
  cout<<"pauseText.clean()"<<endl;
  pauseText.clean();
  TTF_Quit();
  //std::cout<<"freeing surface"<<std::endl;
  //SDL_FreeSurface(window);
  //std::cout<<"quitting SDL"<<std::endl;
  SDL_Quit();
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
  if(keystate[SDL_SCANCODE_ESCAPE])
    {
      cout<<"escape was pressed"<<endl;
      quitGame();
    }
  if(keystate[SDL_SCANCODE_RETURN] || SDL_JoystickGetButton(joy,9))
    {
      start_menu=0;
    }
  keys.up   =(keystate[SDL_SCANCODE_UP]    || keystate[SDL_SCANCODE_W] || SDL_JoystickGetAxis(joy,1)<0);
  keys.down =(keystate[SDL_SCANCODE_DOWN]  || keystate[SDL_SCANCODE_S] || SDL_JoystickGetAxis(joy,1)>0);
  keys.left =(keystate[SDL_SCANCODE_LEFT]  || keystate[SDL_SCANCODE_A] || SDL_JoystickGetAxis(joy,0)<0);
  keys.right=(keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D] || SDL_JoystickGetAxis(joy,0)>0);
  keys.enter=(keystate[SDL_SCANCODE_RETURN]||SDL_JoystickGetButton(joy,9));
  keys.attack=(keystate[SDL_SCANCODE_SPACE] || SDL_JoystickGetButton(joy,0));
  if(keys.attack && !keys.attack_old)
    {
      attackFrame=globalFrame;
    }
  keys.a=keystate[SDL_SCANCODE_A];
  keys.b=keystate[SDL_SCANCODE_B];
  keys.c=keystate[SDL_SCANCODE_C];
  keys.d=keystate[SDL_SCANCODE_D];
  keys.e=keystate[SDL_SCANCODE_E];
  keys.f=keystate[SDL_SCANCODE_F];
  keys.g=keystate[SDL_SCANCODE_G];
  keys.h=keystate[SDL_SCANCODE_H];
  keys.i=keystate[SDL_SCANCODE_I];
  keys.j=keystate[SDL_SCANCODE_J];
  keys.k=keystate[SDL_SCANCODE_K];
  keys.l=keystate[SDL_SCANCODE_L];
  keys.m=keystate[SDL_SCANCODE_M];
  keys.n=keystate[SDL_SCANCODE_N];
  keys.o=keystate[SDL_SCANCODE_O];
  keys.p=(keystate[SDL_SCANCODE_P]||((!gameScoreBoard) && SDL_JoystickGetButton(joy,8)));
  keys.q=keystate[SDL_SCANCODE_Q];
  keys.r=keystate[SDL_SCANCODE_R];
  keys.s=keystate[SDL_SCANCODE_S];
  keys.t=keystate[SDL_SCANCODE_T];
  keys.u=keystate[SDL_SCANCODE_U];
  keys.v=keystate[SDL_SCANCODE_V];
  keys.w=keystate[SDL_SCANCODE_W];
  keys.x=keystate[SDL_SCANCODE_X];
  keys.y=keystate[SDL_SCANCODE_Y];
  keys.z=keystate[SDL_SCANCODE_Z];
  keys.backspace=keystate[SDL_SCANCODE_BACKSPACE];
  if (keys.p&&(!keys.p_old)&&(!gameScoreBoard)&&(!start_menu))
	{
		if(gamePause)
		{
			if(Mix_PausedMusic()==1)
			{
				Mix_ResumeMusic();
			}
		}
		else
		{
			if(Mix_PausedMusic()==0)
			{
				Mix_PauseMusic();
			}
		}
		gamePause=!gamePause;
	}

  keys.attack_old=keys.attack;
  if(!gameScoreBoard){keys.p_old=keys.p;}
  keys.right_old=keys.right;
  keys.left_old=keys.left;
  keys.up_old=keys.up;
  keys.down_old=keys.down;
  if(!gameScoreBoard){keys.enter_old=keys.enter;}
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
