//----------------------------------------------------------------------------
// RendererOpenGL
//----------------------------------------------------------------------------

#ifndef _INCL_RENDEREROPENGL_H
#define _INCL_RENDEREROPENGL_H 1

#include "Renderer.h"
#include "SDL_opengl.h"

//----------------------------------------------------------------------------
class RendererOpenGL: public Renderer
{
  public:
                          RendererOpenGL();
    virtual               ~RendererOpenGL();
    
    // Inherited
    virtual void          swapBuffers() { SDL_GL_SwapBuffers(); }
    virtual void          fillRectToScreen(SDL_Rect*, int r, int g, int b);

  protected:
    virtual bool          setVideoModeInternal(int xSize, int ySize);

  private:
};

#endif
