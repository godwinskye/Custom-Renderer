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

	/*OctantWiz::Point3D first(522.68027320625310, 334.32526842825200, 174.25771842415494);
	OctantWiz::Point3D second(544.51451334859576, 315.48803782317572, 170.83751699089825);
	OctantWiz::Point3D third(522.68027320625310, 315.67473157174800, 174.25771842415494);

	Matrix zBuffer = Matrix(1000, 1000, MType::BACK_PLANE);*/

	OctantWiz::Point first11(315, 171);
	OctantWiz::Point second11(310, 171);          //write sort function
	OctantWiz::Point third11(325, 325);

	unsigned int white = 0xffffffff;

	switch (pageNumber % 9) {
	case 1: {
		draw_rect(0, 0, 650, 650, black);
		std::string inputfile("pageA");
		Interpreter Parser(drawable, inputfile);
		/*draw_rect(0, 0, 650, 650, 0xff000000);
		RenderTests::TransWireframeTri162Test(drawable, 10, 10);*/
		drawable->updateScreen();   // you must call this to make the display change.
	}
		break;
	case 2: {
		draw_rect(0, 0, 650, 650, black);
		std::string inputfile("pageB");
		Interpreter Parser(drawable, inputfile);
		drawable->updateScreen();
	}
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