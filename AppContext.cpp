//----------------------------------------------------------------------------
// AppContext
//----------------------------------------------------------------------------

#include "AppContext.h"
#include "RendererOpenGL.h"

//----------------------------------------------------------------------------
// Constructor
AppContext::AppContext()
{
  renderer = new RendererOpenGL;
  fps      = 0;
}

//----------------------------------------------------------------------------
// Destructor
AppContext::~AppContext()
{
  delete renderer;
}

