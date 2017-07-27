//----------------------------------------------------------------------------
// MainWindow
//----------------------------------------------------------------------------

#ifndef _INCL_MAINWINDOW_H
#define _INCL_MAINWINDOW_H 1

#include "EventHandler.h"
#include "TiledFont.h"

//----------------------------------------------------------------------------
class MainWindow: public EventHandler
{
  public:
                    MainWindow(AppContext*);
    virtual         ~MainWindow();

    // Initialise
    virtual bool    init();

    // Handle an SDL event
    virtual void    handleEvent(SDL_Event&);
    
    // Handle one 'tick' of animation
    virtual void    animate();
    
    // Check if the window is OK
    bool            isOK() const { return(okFlag); }
    
    // Get the window's font
    TiledFont*      getFont() { return(&monoFont); }

  private:
    // Variables
    bool            okFlag;
    int             xSize;
    int             ySize;
    TiledFont       monoFont;       
    Uint32          lastFrameTicks;
    Uint32          lastFPSTicks;
    int             numFrames;
};

#endif
