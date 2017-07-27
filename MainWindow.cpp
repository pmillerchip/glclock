//----------------------------------------------------------------------------
// MainWindow
//----------------------------------------------------------------------------

#include "MainWindow.h"
#include <sys/time.h>

const int SCREEN_BPP = 32;
const int FONT_SIZE = 16;

//----------------------------------------------------------------------------
// Constructor
MainWindow::MainWindow(AppContext* ctx):
  EventHandler(ctx)
{
  ctx->mainWindow = this;
  okFlag          = false;
  numFrames       = 0;
  lastFPSTicks    = SDL_GetTicks();
  lastFrameTicks  = SDL_GetTicks();
}

//----------------------------------------------------------------------------
// Destructor
MainWindow::~MainWindow()
{
}

//----------------------------------------------------------------------------
bool
MainWindow::init()
{
  if (okFlag) return(false);  // Don't init twice

  // Load font
  if (!monoFont.init("LiberationMono-Bold.ttf", FONT_SIZE)) return(false);

  lastFrameTicks = SDL_GetTicks();

  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_SMOOTH);
  
  okFlag = true;
  return(true);
}

//----------------------------------------------------------------------------
void
MainWindow::handleEvent(SDL_Event& event)
{
  // Don't handle the event if the window isn't happy
  if (!okFlag) return;
  
  if (event.type == SDL_VIDEORESIZE)
  {
    // Resize the screen
    if (!appContext->getRenderer()->setVideoMode(event.resize.w, event.resize.h))
    {
      okFlag = false;
      return;
    }
  }
  else if (event.type == SDL_KEYDOWN)
  {
    if (event.key.keysym.sym == SDLK_q)
    {
      okFlag = false;
      return;
    }
  }
}

//----------------------------------------------------------------------------
void
MainWindow::animate()
{
  Renderer* r = appContext->getRenderer();

  int xSize = r->getXSize();
  int ySize = r->getYSize();
  
  // Ensure correct mode
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, xSize / 2, ySize / 2, 0.0f, -1.0f, 1.0f);
  glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Read clock
  struct timeval tv;
  gettimeofday(&tv, NULL);
  
  // PAL Frame count
  int millisec = ((tv.tv_sec) % 100) * 1000;
  millisec += tv.tv_usec / 1000;

  // Status info
  char tmpc[128];
  snprintf(tmpc, 128, "%02d.%06d (frm %d)", (tv.tv_sec) % 100, tv.tv_usec, millisec / 40);
  monoFont.draw(0, 0, tmpc);
  
  // Calculate FPS
  Uint32 thisTicks = SDL_GetTicks();
  ++numFrames;
  Uint32 numFPSTicks = thisTicks - lastFPSTicks;
  if (numFPSTicks > 1000)
  {
    appContext->fps = (int)(((double)numFrames) * 1000.0 / ((double)numFPSTicks));
    numFrames = 0;
    lastFPSTicks = thisTicks;
  }
  
  // Update the screen
  r->swapBuffers();
  
  // Clamp framerate
  Uint32 numTicks = thisTicks - lastFrameTicks;
  if (numTicks < 10) SDL_Delay(10 - numTicks);
  lastFrameTicks = thisTicks;
}

