//----------------------------------------------------------------------------
// Renderer
//----------------------------------------------------------------------------

#ifndef _INCL_RENDERER_H
#define _INCL_RENDERER_H 1

#include "SDL.h"

//----------------------------------------------------------------------------
class Renderer
{
  public:
                          Renderer();
    virtual               ~Renderer();
    
    // Try to set the current video mode to the given size
    bool                  setVideoMode(int xSize, int ySize);
    
    // Returns the current size of the screen
    int                   getXSize() const { return(xSize); }
    int                   getYSize() const { return(ySize); }
    
    // Swap the display buffers
    virtual void          swapBuffers() = 0;
    
    // Fast-fill a solid rectangle to the screen of the given colour.
    // Colour components go from 0-255.
    virtual void          fillRectToScreen(SDL_Rect*, int r, int g, int b) = 0;
    
    // Get the scale factor for converting OpenGL coordinates to screen coordinates
    double                getDisplayScale() const { return(displayScale); }

  protected:
    virtual bool          setVideoModeInternal(int xSize, int ySize) = 0;

  private:
    int                   xSize;
    int                   ySize;
    double                displayScale;
};

#endif
