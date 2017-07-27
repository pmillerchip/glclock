//----------------------------------------------------------------------------
// TiledFont
//----------------------------------------------------------------------------

#ifndef _INCL_TILEDFONT_H
#define _INCL_TILEDFONT_H 1

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_opengl.h"

//----------------------------------------------------------------------------
class TiledFont
{
  public:
                    TiledFont();
                    ~TiledFont();

    // Initialise
    bool            init(const char* filename, int size);
    
    // Get a pointer to the internal font object
    TTF_Font*       getFont() const { return(font); }
    
    // Get the width and height of an individual character tile
    int             getCharWidth()  const { return(charWidth);  }
    int             getCharHeight() const { return(charHeight); }
    
    // Render a string onto the screen
    void            draw(double x, double y, const char*);
    
    // Render a single character
    void            draw(double x, double y, unsigned char c);

  private:
    bool            makeTile(char c, GLuint texture);
    void            renderTile(SDL_Surface* dest, char c);
    void            surfaceToGLTexture(SDL_Surface* surface, GLuint texture);

    // Variables
    TTF_Font*       font;
    int             charWidth;
    int             charHeight;
    int             tileSize;
    GLuint          tiles[256];
    GLuint          displayListID;
    bool            texturesGenerated;
};

#endif
