//----------------------------------------------------------------------------
// DebugScreen
// Inherits from class EventHandler
//----------------------------------------------------------------------------

#ifndef _INCL_DEBUGSCREEN_H
#define _INCL_DEBUGSCREEN_H 1

#include "EventHandler.h"

//----------------------------------------------------------------------------
class DebugScreen: public EventHandler
{
  public:
                          DebugScreen(AppContext*);
    virtual               ~DebugScreen();

    virtual bool          init();
    virtual void          handleEvent(SDL_Event&);
    virtual void          animate();

  private:
};

#endif
