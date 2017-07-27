//----------------------------------------------------------------------------
// DebugScreen
//----------------------------------------------------------------------------

#include "DebugScreen.h"
#include "MainWindow.h"
#include <string>

//----------------------------------------------------------------------------
// Constructor
DebugScreen::DebugScreen(AppContext* ctx): EventHandler(ctx)
{
}

//----------------------------------------------------------------------------
// Destructor
DebugScreen::~DebugScreen()
{
}

//----------------------------------------------------------------------------
bool
DebugScreen::init()
{
  return(true);
}

//----------------------------------------------------------------------------
void
DebugScreen::handleEvent(SDL_Event&)
{
}
   
//----------------------------------------------------------------------------
void
DebugScreen::animate()
{
  Renderer* r = appContext->getRenderer();

  int xSize = r->getXSize();
  int ySize = r->getYSize();
  
  // Ensure correct mode
  glPushMatrix();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, xSize, ySize, 0.0f, -1.0f, 1.0f);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  // Grab the font from the main window
  // TODO: Refactor - renderer should have it instead
  TiledFont* font = appContext->mainWindow->getFont();
  int lineHeight = font->getCharHeight();
  
  // Status info
  char tmpc[128];
  snprintf(tmpc, 128, "%d FPS", appContext->fps);
  int y = 0;
  font->draw(0, y, tmpc); y += lineHeight;
  
  std::string msg("       Vendor: ");
  msg += (const char*)glGetString(GL_VENDOR);
  font->draw(0, y, msg.data()); y += lineHeight;
  
  msg = "     Renderer: ";
  msg += (const char*)glGetString(GL_RENDERER);
  font->draw(0, y, msg.data()); y += lineHeight;
  
  msg = "OpenGL Verson: ";
  msg += (const char*)glGetString(GL_VERSION);
  font->draw(0, y, msg.data()); y += lineHeight;
  
  glPopMatrix();
}
