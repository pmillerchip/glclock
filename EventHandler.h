//----------------------------------------------------------------------------
// EventHandler
//----------------------------------------------------------------------------

#ifndef _INCL_EVENTHANDLER_H
#define _INCL_EVENTHANDLER_H 1

#include "AppContext.h"

//----------------------------------------------------------------------------
class EventHandler
{
  public:
                          EventHandler(AppContext*);
    virtual               ~EventHandler();
    
    // Initialise.
    // Returns true on success, false on failure/
    virtual bool          init() = 0;

    // Handle an SDL event
    virtual void          handleEvent(SDL_Event&) = 0;
    
    // Handle one 'tick' of animation
    virtual void          animate() = 0;
  
  protected:
    AppContext*           appContext;

  private:
};

#endif
