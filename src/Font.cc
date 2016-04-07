#include "Font.h"


Font::Font(const std::string& filename, int size) : _filename(filename), _size(size) {
   _font = al_load_font(_filename.c_str(), _size, 0);
}

Font::~Font() {
   al_destroy_font(_font);
}

void Font::drawTextCentered(const ALLEGRO_COLOR& color, const std::string& message) {
   al_draw_text(_font, color, 400, 300, ALLEGRO_ALIGN_CENTRE, message.c_str());   
}

void Font::drawTextCenteredF(const ALLEGRO_COLOR& color, const std::string& message,
			     int format) {
   al_draw_textf(_font, color, 400, 300, ALLEGRO_ALIGN_CENTRE, message.c_str(), format);   
}

void Font::drawTextF(const ALLEGRO_COLOR& color, int x, int y, const std::string& message,
		    int format) {
   al_draw_textf(_font, color, x, y, ALLEGRO_ALIGN_CENTRE, message.c_str(), format);
}

