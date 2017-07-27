//----------------------------------------------------------------------------
// AppContext
//----------------------------------------------------------------------------

#ifndef _INCL_APPCONTEXT_H
#define _INCL_APPCONTEXT_H 1

#include "Renderer.h"

class MainWindow;

//----------------------------------------------------------------------------
class AppContext
{
  public:
                         AppContext();
                         ~AppContext();

    // Accessors
    Renderer*            getRenderer() { return(renderer); }
    
    // Variables
    MainWindow*          mainWindow;
    int                  fps;

  private:
    // Variables
    Renderer*            renderer;
};

#endif
