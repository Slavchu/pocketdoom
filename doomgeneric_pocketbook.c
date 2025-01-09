#include "src/doomgeneric.h"
#include "src/doomkeys.h"
#include <inkview.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <memory.h>
#include <sys/time.h>

#define SCREEN_ORIENTATION 1
#define KEYQUEUE_SIZE 16
#define FULL_UPDATE_FREQ 64

static unsigned char key_pressed;
static unsigned short current_key;
static pthread_t doomloop_thread;

// unused functions
void DG_SetWindowTitle(const char *title){}
void DG_Init(){}

void DG_DrawFrame(){
  if(DG_ScreenBuffer == NULL)
    return;
  for(int x = 0; x < DOOMGENERIC_RESX; x++){
    for(int y = 0; y < DOOMGENERIC_RESY; y++){
      DrawPixel(x,y, (int)DG_ScreenBuffer[y*DOOMGENERIC_RESX + x]);
    }
  }
  PartialUpdate(0,0, DOOMGENERIC_RESX, DOOMGENERIC_RESY); 
}

void* doom_loop(void * arg){
  while(1){
    doomgeneric_Tick();
  } 
  return NULL;
}

void handle_key(int key){  
  switch (key) {
    case KEY_LEFT:{
      current_key = KEY_LEFTARROW;
      break;
    }
    case KEY_RIGHT:{
      current_key = KEY_RIGHTARROW;
      break;
    }
    case KEY_UP:{
      current_key = KEY_UPARROW;
      break;
    }
    case KEY_DOWN:{
      current_key = KEY_DOWNARROW;
      break;
    }
    case KEY_OK:{
      current_key = KEY_FIRE;
      break;
    }
    case KEY_NEXT:{
      current_key = KEY_ENTER;
      break;
    }
    default:
      current_key = KEY_USE;
      break;
  }
}

//pocketbook specific event handler
int pb_handler(int type, int par1, int par2){
  switch(type){
    case EVT_INIT:{
      doomgeneric_Create(0, NULL);
      SetOrientation(SCREEN_ORIENTATION);
      pthread_create(&doomloop_thread, NULL, doom_loop, NULL);
      pthread_detach(doomloop_thread);
      break;
    }
    case EVT_SHOW:{
      ClearScreen();
      FullUpdate();
      break;
    }
    case EVT_KEYPRESS:{
      key_pressed = 1;
      handle_key(par1); 
      break;
    }
    case EVT_KEYRELEASE:{
      handle_key(par1);
      key_pressed = 0;
      break;
    }
    case EVT_EXIT:{
      break;
    }
    default:
      break;
  }

  return 0;
}

void DG_SleepMs(uint32_t ms){
  usleep(ms * 1000);
}

uint32_t DG_GetTicksMs(){
  struct timeval tp;
  struct timezone tzp;

  gettimeofday(&tp, &tzp);

  return (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
}

int DG_GetKey(int *pressed, unsigned char *doomKey){
  unsigned short keyData = current_key;
  
  if (!keyData){
    return 0;
  }
  else{
    *pressed = key_pressed;
    *doomKey = keyData & 0xFF;
    current_key = 0;          
    return 1;
  }
}

int main(int argc, char **argv){
  InkViewMain(pb_handler);
  return 0;
}
