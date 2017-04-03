#include <iostream>
#include <string>
#include "client.h"
#include "RenderTests/RenderTests.h"
#include "Interpreter/Interpreter.h"
#include "Renderer/InterpolatedPolyFill.h"
#include "Renderer/InterpolatedLines.h"

Client::Client(Drawable *drawable)
{
    this->drawable = drawable;
}


void Client::nextPage() {
    static int pageNumber = 0;
	unsigned int black = 0xff000000;
    pageNumber++;
    std::cout << "PageNumber " << pageNumber << std::endl;

	OctantWiz::Point first(200, 300);
	OctantWiz::Point second(300, 300);
	OctantWiz::Point third(300, 450);

	OctantWiz::Point first11(315, 171);
	OctantWiz::Point second11(310, 171);          //write sort function
	OctantWiz::Point third11(325, 325);

	unsigned int white = 0xffffffff;

	switch (pageNumber % 9) {
	case 1: {
		draw_rect(0, 0, 650, 650, black);
		std::string inputfile("test3");
		Interpreter Parser(drawable, inputfile);
		/*draw_rect(0, 0, 650, 650, 0xff000000);
		RenderTests::TransWireframeTri162Test(drawable, 10, 10);*/
		drawable->updateScreen();   // you must call this to make the display change.
	}
		break;
	case 2:
		draw_rect(0, 0, 650, 650, black);
		RenderTests::TransMeshTri162Test(drawable, 10, 10);
		drawable->updateScreen();
		break;
	case 3:
		draw_rect(0, 0, 650, 650, black);
		RenderTests::zBufferTest(drawable);
		drawable->updateScreen();
		break;
	case 4: {
		draw_rect(0, 0, 650, 650, black);
		std::string inputfile("largecube");
		Interpreter Parser(drawable, inputfile);
		drawable->updateScreen();
	}
		break;
	case 5: {
		draw_rect(0, 0, 650, 650, black);
		std::string inputfile("page5");
		Interpreter Parser(drawable, inputfile);
		drawable->updateScreen();
	}
		break;
	case 6: {
		draw_rect(0, 0, 650, 650, black);
		std::string inputfile("test1");
		Interpreter Parser(drawable, inputfile);
		drawable->updateScreen();
	}
		break;
	case 7: {
		draw_rect(0, 0, 650, 650, black);
		std::string inputfile("test2");
		Interpreter Parser(drawable, inputfile);
		drawable->updateScreen();
	}
		break;
	case 8: {
		draw_rect(0, 0, 650, 650, black);
		std::string inputfile("test3");
		Interpreter Parser(drawable, inputfile);
		drawable->updateScreen();
	}
		break;
	}
}

void Client::draw4panels() {
	draw_rect(0, 0, 750, 750, 0xffff0080);
	draw_rect(50, 50, 350, 350, 0xff00ff40);
	draw_rect(400, 50, 700, 350, 0xff40ff00);
	draw_rect(50, 400, 350, 700, 0xffff8000);
	draw_rect(400, 400, 700, 700, 0xffffff00);
}

void Client::draw_rect(int x1, int y1, int x2, int y2, unsigned int color) {
    for(int x = x1; x<x2; x++) {
        for(int y=y1; y<y2; y++) {
            drawable->setPixel(x, y, color);
        }
    }
}