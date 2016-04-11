#ifndef FONT_H
#define FONT_H

#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Font {

  public:
   Font(const std::string&, int);
   ~Font();

   void load();
   
   void drawTextCentered(const ALLEGRO_COLOR&, const std::string&);
   void drawTextCenteredF(const ALLEGRO_COLOR&, const std::string&, int);

   void drawTextF(const ALLEGRO_COLOR&, int, int, const std::string&, int);

   bool isLoaded() const;
   
  private:
   ALLEGRO_FONT* _font;
   std::string _filename;
   int _size;
};



#endif
