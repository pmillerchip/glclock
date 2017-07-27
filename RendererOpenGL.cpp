//----------------------------------------------------------------------------
// RendererOpenGL
//----------------------------------------------------------------------------

#include "RendererOpenGL.h"

//----------------------------------------------------------------------------
// Constructor
RendererOpenGL::RendererOpenGL()
{
}

//----------------------------------------------------------------------------
// Destructor
RendererOpenGL::~RendererOpenGL()
{
}

//----------------------------------------------------------------------------
bool
RendererOpenGL::setVideoModeInternal(int x, int y)
{
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
 
  SDL_Surface* screen = SDL_SetVideoMode(x, y, 32, SDL_OPENGL);
  if (screen == NULL)
  {
    fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
    return(false);
  }

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   
  glViewport(0, 0, x, y);
   
  glClear(GL_COLOR_BUFFER_BIT);
   
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  double ds = getDisplayScale();
  glOrtho(0.0f, x / ds, 0.0f, y / ds, -1.0f, 1.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  return(true);
}
  
//----------------------------------------------------------------------------
void
RendererOpenGL::fillRectToScreen(SDL_Rect* rect, int r, int g, int b)
{
  glBegin(GL_QUADS);
  glColor3f(r / 255.0, g / 255.0, b / 255.0);
  glVertex2i(rect->x, rect->y);
  glVertex2i(rect->x + rect->w, rect->y);
  glVertex2i(rect->x + rect->w, rect->y + rect->h);
  glVertex2i(rect->x, rect->y + rect->h);
  glColor3f(1.0, 1.0, 1.0);
  glEnd();
}



