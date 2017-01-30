#pragma once
#include "LineRender.h"

namespace RenderTests {
	void DDAStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines);
	void BRStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines);
	void MixStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines);
	void AAStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines);
}