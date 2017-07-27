//----------------------------------------------------------------------------
// Main routine
//----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "MainWindow.h"
#include "AppContext.h"

// The attributes of the screen
const int SCREEN_WIDTH  = 480;
const int SCREEN_HEIGHT = 48;
 
//----------------------------------------------------------------------------
int
main(int argc, char **argv)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    return(1);
  }

  // Initialize SDL_ttf
  if (TTF_Init() == -1) return(1);

  // Set up the app's context block
  AppContext ctx;
  
  // Set the video mode
  if (!ctx.getRenderer()->setVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT)) return(1);
  
  // Set up the window
  MainWindow* win = new MainWindow(&ctx);
  if (!win->init()) return(1);
  
  // Set the window caption
  SDL_WM_SetCaption("SDL/OpenGL Clock", NULL);
    
  // Main event loop
  SDL_Event event;
  bool quit = false;
  while(!quit)
  {
    while(SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        // Quit the program
        quit = true;
      }
      else
      {
        win->handleEvent(event);
        quit = !win->isOK();
      }
    }

    win->animate();
  }
 
  // Tidy up
  delete win;
  TTF_Quit();
  SDL_Quit();
  return(0);
}
