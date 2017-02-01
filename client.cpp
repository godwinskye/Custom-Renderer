#include <iostream>
#include "client.h"

Client::Client(Drawable *drawable)
{
    this->drawable = drawable;
}


void Client::nextPage() {
    static int pageNumber = 0;
	unsigned int black = 0xff000000;
	RenderTests::RandomTestPackage package = RenderTests::GetPackage();
    pageNumber++;
    std::cout << "PageNumber " << pageNumber << std::endl;


	OctantWiz::Point Origin(200, 200);
	OctantWiz::Point Point1(270, 160);
	OctantWiz::Point Point2(300, 180);

    switch(pageNumber % 5) {
	case 1: {
		draw4panels();
		RenderTests::DDAStarburstTest(drawable, 200, 200, 125, 90, black);
		RenderTests::BRStarburstTest(drawable, 550, 200, 125, 90, black);
		RenderTests::MixStarburstTest(drawable, 200, 550, 125, 90, black);


		//RenderTests::AAStarburstTest(drawable, 550, 550, 125, 90);
		//LineRenderer::AArender(drawable, 550, 550, 650, 480);
		/*
		LineRenderer::AArender(drawable, 550, 550, 600, 400);
		LineRenderer::AArender(drawable, 550, 550, 500, 400);
		LineRenderer::AArender(drawable, 550, 550, 400, 500);
		LineRenderer::AArender(drawable, 550, 550, 400, 600);
		LineRenderer::AArender(drawable, 550, 550, 500, 700);
		LineRenderer::AArender(drawable, 550, 550, 600, 700);
		LineRenderer::AArender(drawable, 550, 550, 650, 600);
		*/


		drawable->updateScreen();   // you must call this to make the display change.
	}
		break;
    case 2:
		draw4panels();
		RenderTests::DDAParallelogramTest(drawable, 50, 50, black);
		RenderTests::BREParallelogramTest(drawable, 400, 50, black);
		RenderTests::MixParallelogramTest(drawable, 50, 400, black);
		drawable->updateScreen();
        break;
    case 3:
		draw4panels();
		RenderTests::DDARandomTest(drawable, package, 50, 50);
		RenderTests::BRERandomTest(drawable, package, 400, 50);
		RenderTests::MixRandomTest(drawable, package, 50, 400);
		drawable->updateScreen();
        break;
    case 4:
		draw4panels();
		//RenderTests::PolygonStarburstTest(drawable, 200, 200, 125, 90, black);
		PolyFill::Triangle(drawable, Origin, Point1, Point2);
		drawable->updateScreen();
		break;
        // fall through...
    default:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect(400, 400, 700, 700, 0xff00ff40);
        drawable->updateScreen();
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
