#pragma once
#include "LineRender.h"

namespace RenderTests {
	//Starburst Tests
	void DDAStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines);
	void BRStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines);
	void MixStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines);
	void AAStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines);

	//Parallelogram Test
	void DDAParallelogramTest(Drawable *drawable, int x, int y);
	void BREParallelogramTest(Drawable *drawable, int x, int y);
	void MixParallelogramTest(Drawable *drawable, int x, int y);
}