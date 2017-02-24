#include "InterpolatedPolyFill.h"
#include "InterpolatedLines.h"

void PolyFill::LiTriangle(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2, unsigned int color1, unsigned int color2, unsigned int color3) {
	int currentIter;

	LineRenderer::FillPack line11 = LineRenderer::LiPolyDDArender(drawable, origin, endpoint1, color1, color2);
	LineRenderer::FillPack line22 = LineRenderer::LiPolyDDArender(drawable, origin, endpoint2, color1, color3);
	LineRenderer::FillPack line33 = LineRenderer::LiPolyDDArender(drawable, endpoint1, endpoint2, color2, color3);
	PolyFill::LongestTriLine package = LineRenderer::FindLongest(line11, line22, line33);


	LineRenderer::FillPack longestline = LineRenderer::LiPolyDDArender(drawable, package.longest.origin, package.longest.endpoint, 
										drawable->getPixel(package.longest.origin.x, package.longest.origin.y), 
										drawable->getPixel(package.longest.endpoint.x, package.longest.endpoint.y));

	LineRenderer::FillPack line2 = LineRenderer::LiPolyDDArender(drawable, package.shorter1.origin, package.shorter1.endpoint, 
									drawable->getPixel(package.shorter1.origin.x, package.shorter1.origin.y), 
									drawable->getPixel(package.shorter1.endpoint.x, package.shorter1.endpoint.y));

	LineRenderer::FillPack line3 = LineRenderer::LiPolyDDArender(drawable, package.shorter2.origin, package.shorter2.endpoint, 
									drawable->getPixel(package.shorter2.origin.x, package.shorter2.origin.y),
									drawable->getPixel(package.shorter2.endpoint.x, package.shorter2.endpoint.y));
	

	int something;

	if (longestline.xiter) {
		for (int i = 0; i < line2.map.size(); i++) {
			if (line2.xiter) {
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.x + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, currentIter, line2.map[currentIter], currentIter, longestline.map[currentIter], 
						drawable->getPixel(currentIter, line2.map[currentIter]), drawable->getPixel(currentIter, longestline.map[currentIter]));
				}
				else {
					currentIter = package.shorter1.origin.x - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, currentIter, line2.map[currentIter], currentIter, longestline.map[currentIter],
						drawable->getPixel(currentIter, line2.map[currentIter]), drawable->getPixel(currentIter, longestline.map[currentIter]));
				}
			}
			else {     //line2 = yiter
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.y + i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, line2.map[currentIter], currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], 
						drawable->getPixel(line2.map[currentIter], currentIter), drawable->getPixel(line2.map[currentIter], longestline.map[line2.map[currentIter]]));
				}
				else {
					currentIter = package.shorter1.origin.y - i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, line2.map[currentIter], currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], 
						drawable->getPixel(line2.map[currentIter], currentIter), drawable->getPixel(line2.map[currentIter], longestline.map[line2.map[currentIter]]));
				}
			}
		}

		for (int i = 0; i < line3.map.size(); i++) {
			if (line3.xiter) {
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.x + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, currentIter, line3.map[currentIter], currentIter, longestline.map[currentIter], 
						drawable->getPixel(currentIter, line3.map[currentIter]), drawable->getPixel(currentIter, longestline.map[currentIter]));
				}
				else {
					currentIter = package.shorter2.origin.x - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, currentIter, line3.map[currentIter], currentIter, longestline.map[currentIter],
						drawable->getPixel(currentIter, line3.map[currentIter]), drawable->getPixel(currentIter, longestline.map[currentIter]));
				}
			}
			else {       //line3 = yiter
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.y + i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, line3.map[currentIter], currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], 
						drawable->getPixel(line3.map[currentIter], currentIter), drawable->getPixel(line3.map[currentIter], longestline.map[line3.map[currentIter]]));
				}
				else {
					currentIter = package.shorter2.origin.y - i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, line3.map[currentIter], currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], 
						drawable->getPixel(line3.map[currentIter], currentIter), drawable->getPixel(line3.map[currentIter], longestline.map[line3.map[currentIter]]));
				}
			}
		}

	}
	else {    //longestline is a yiter
		for (int i = 0; i < line2.map.size(); i++) {
			if (line2.xiter) {
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.x + i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], line2.map[currentIter], 
						drawable->getPixel(currentIter, line2.map[currentIter]), drawable->getPixel(longestline.map[line2.map[currentIter]], line2.map[currentIter]));
				}
				else {
					currentIter = package.shorter1.origin.x - i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], line2.map[currentIter], 
						drawable->getPixel(currentIter, line2.map[currentIter]), drawable->getPixel(longestline.map[line2.map[currentIter]], line2.map[currentIter]));
				}
			}
			else {     //line2 is a yiter
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.y + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, line2.map[currentIter], currentIter, longestline.map[currentIter], currentIter, 
						drawable->getPixel(line2.map[currentIter], currentIter), drawable->getPixel(longestline.map[currentIter], currentIter));
				}
				else {
					currentIter = package.shorter1.origin.y - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, line2.map[currentIter], currentIter, longestline.map[currentIter], currentIter, 
						drawable->getPixel(line2.map[currentIter], currentIter), drawable->getPixel(longestline.map[currentIter], currentIter));
				}
			}
		}

		for (int i = 0; i < line3.map.size(); i++) {
			if (line3.xiter) {
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.x + i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], line3.map[currentIter], 
						drawable->getPixel(currentIter, line3.map[currentIter]), drawable->getPixel(longestline.map[line3.map[currentIter]], line3.map[currentIter]));
				}
				else {
					currentIter = package.shorter2.origin.x - i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], line3.map[currentIter], 
						drawable->getPixel(currentIter, line3.map[currentIter]), drawable->getPixel(longestline.map[line3.map[currentIter]], line3.map[currentIter]));
				}
			}
			else {      //line3 is a yiter
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.y + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, line3.map[currentIter], currentIter, longestline.map[currentIter], currentIter, 
						drawable->getPixel(line3.map[currentIter], currentIter), drawable->getPixel(longestline.map[currentIter], currentIter));
				}
				else {
					currentIter = package.shorter2.origin.y - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::LiDDArender(drawable, line3.map[currentIter], currentIter, longestline.map[currentIter], currentIter, 
						drawable->getPixel(line3.map[currentIter], currentIter), drawable->getPixel(longestline.map[currentIter], currentIter));
				}
			}
		}

	}
}
