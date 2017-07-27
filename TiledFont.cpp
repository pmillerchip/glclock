//----------------------------------------------------------------------------
// TiledFont
//----------------------------------------------------------------------------

#include "TiledFont.h"
#include <stdio.h>

//----------------------------------------------------------------------------
// Constructor
TiledFont::TiledFont()
{
  font       = NULL;
  charWidth  = 0;
  charHeight = 0;
  tileSize   = 32;
  texturesGenerated = false;
}

//----------------------------------------------------------------------------
// Destructor
TiledFont::~TiledFont()
{
  if (texturesGenerated) glDeleteTextures(256, tiles);
}

//----------------------------------------------------------------------------
bool
TiledFont::init(const char* filename, int size)
{
  glGenTextures(256, tiles);
  texturesGenerated = true;

  // Load font
  font = TTF_OpenFont(filename, size);
  if (font == NULL)
  {
    fprintf(stderr, "Cannot load font: %s\n", TTF_GetError());
    return(false);
  }
  
  // Calculate the character dimensions
  if (TTF_SizeText(font, "M", &charWidth, &charHeight) != 0)
  {
    return(false);
  }
  
  int i;
  for(i=0; i < 256; ++i)
  {
    if (!makeTile((char)i, tiles[i]))
    {
      fprintf(stderr, "Error: Font tile create failed for character %d\n", i);
      return(false);
    }
  }
  
  double scale = 1.0 / ((double)tileSize);

  // Display list for drawing a single character
  displayListID = glGenLists(1);
  glNewList(displayListID, GL_COMPILE);

  glBegin(GL_QUADS);

  // Top-left vertex (corner)
  glTexCoord2f(0, 0);
  glVertex3f(0, 0, 0);

  // Top-right vertex (corner)
  glTexCoord2f(charWidth * scale, 0);
  glVertex3f(charWidth, 0, 0);

  // Bottom-right vertex (corner)
  glTexCoord2f(charWidth * scale, charHeight * scale);
  glVertex3f(charWidth, charHeight, 0);

  // Bottom-left vertex (corner)
  glTexCoord2f(0, charHeight * scale);
  glVertex3f(0, charHeight, 0);
  glEnd();
  glEndList();

  return(true);
}

//----------------------------------------------------------------------------
void
TiledFont::draw(double x, double y, const char* str)
{
  const unsigned char* d = (const unsigned char*)str;
  unsigned char c;
  while(*d != 0)
  {
    c = *d++;
    draw(x, y, c);
    x += charWidth;
  }
}

//----------------------------------------------------------------------------
void
TiledFont::draw(double x, double y, unsigned char c)
{
  GLuint tile;
  tile = tiles[(int)c];
    
  // Bind the texture to which subsequent calls refer to
  glBindTexture(GL_TEXTURE_2D, tile);
  glPushMatrix();
  glTranslatef(x, y, 0);
  glCallList(displayListID);
  glPopMatrix();
}

//----------------------------------------------------------------------------
bool
TiledFont::makeTile(char c, GLuint texture)
{
  Uint32 rmask, gmask, bmask, amask;

  // SDL interprets each pixel as a 32-bit number, so our masks must depend
  // on the endianness (byte order) of the machine
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif

  SDL_Surface* rv = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, tileSize, tileSize,
    32, rmask, gmask, bmask, amask);

  if (rv == NULL) return(false);
  
  // Render the text
  SDL_FillRect(rv, NULL, SDL_MapRGBA(rv->format, 255, 255, 255, 255));
  renderTile(rv, c);

  surfaceToGLTexture(rv, texture);
  SDL_FreeSurface(rv);
  return(true);
}

//----------------------------------------------------------------------------
void
TiledFont::renderTile(SDL_Surface* dest, char c)
{
  char str[2];
  str[0] = c;
  str[1] = 0;

  SDL_Color textColor = { 0, 0, 0 };
  SDL_Surface* img = TTF_RenderText_Blended(font, str, textColor);
  SDL_Rect offset;
  
  offset.x = 0;
  offset.y = 0;
  
  SDL_BlitSurface(img, NULL, dest, &offset);
  SDL_FreeSurface(img);
}
    
//----------------------------------------------------------------------------
void
TiledFont::surfaceToGLTexture(SDL_Surface* surface, GLuint texture)
{
  // Bind the texture object
  glBindTexture(GL_TEXTURE_2D, texture);
  
  // Set the texture's stretching properties
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  // Edit the texture object's image data using the information SDL_Surface gives us
  glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, 
               GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
}
