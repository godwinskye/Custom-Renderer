#ifndef CLIENT_H
#define CLIENT_H
#include "drawable.h"
#include "pageturner.h"
#include "RenderTests/RenderTests.h"

class Client : public PageTurner
{
public:
    Client(Drawable *drawable);
    void nextPage();
	Drawable *drawable;     //TODO ensure that public drawable is really okay
	void draw4panels();
private:
    void draw_rect(int x1, int y1, int x2, int y2, unsigned int color);
};

#endif // CLIENT_H
