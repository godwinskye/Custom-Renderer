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

void PolyFill::Triangle3D(Drawable * drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint1, OctantWiz::Point3D endpoint2, Matrix & zBuffer, unsigned int color1, unsigned int color2, unsigned int color3) {
	int currentIter;

	LineRenderer::FillPack3D line11 = LineRenderer::PolyDDArender3D(drawable, origin, endpoint1, zBuffer, color1, color2);
	LineRenderer::FillPack3D line22 = LineRenderer::PolyDDArender3D(drawable, origin, endpoint2, zBuffer, color1, color3);
	LineRenderer::FillPack3D line33 = LineRenderer::PolyDDArender3D(drawable, endpoint1, endpoint2, zBuffer, color2, color3);
	PolyFill::LongestTriLine3D package = LineRenderer::FindLongest3D(line11, line22, line33);


	LineRenderer::FillPack3D longestline = LineRenderer::PolyDDArender3D(drawable, package.longest.origin, package.longest.endpoint, zBuffer,
		drawable->getPixel(package.longest.origin.x, package.longest.origin.y),
		drawable->getPixel(package.longest.endpoint.x, package.longest.endpoint.y));

	LineRenderer::FillPack3D line2 = LineRenderer::PolyDDArender3D(drawable, package.shorter1.origin, package.shorter1.endpoint, zBuffer,
		drawable->getPixel(package.shorter1.origin.x, package.shorter1.origin.y),
		drawable->getPixel(package.shorter1.endpoint.x, package.shorter1.endpoint.y));

	LineRenderer::FillPack3D line3 = LineRenderer::PolyDDArender3D(drawable, package.shorter2.origin, package.shorter2.endpoint, zBuffer,
		drawable->getPixel(package.shorter2.origin.x, package.shorter2.origin.y),
		drawable->getPixel(package.shorter2.endpoint.x, package.shorter2.endpoint.y));

	int z, z2;

	if (longestline.xiter) {
		for (int i = 0; i < line2.map.size(); i++) {
			if (line2.xiter) {
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.x + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					z = zBuffer.at(currentIter, line2.map[currentIter]);
					z2 = zBuffer.at(currentIter, longestline.map[currentIter]);
					LineRenderer::LiDDArender3D(drawable, currentIter, line2.map[currentIter], z, currentIter, longestline.map[currentIter], z2, zBuffer,
						drawable->getPixel(currentIter, line2.map[currentIter]), drawable->getPixel(currentIter, longestline.map[currentIter]));
				}
				else {
					currentIter = package.shorter1.origin.x - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					z = zBuffer.at(currentIter, line2.map[currentIter]);
					z2 = zBuffer.at(currentIter, longestline.map[currentIter]);
					LineRenderer::LiDDArender3D(drawable, currentIter, line2.map[currentIter], z, currentIter, longestline.map[currentIter], z2, zBuffer,
						drawable->getPixel(currentIter, line2.map[currentIter]), drawable->getPixel(currentIter, longestline.map[currentIter]));
				}
			}
			else {     //line2 = yiter
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.y + i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					z = zBuffer.at(line2.map[currentIter], currentIter);
					z2 = zBuffer.at(line2.map[currentIter], longestline.map[line2.map[currentIter]]);
					LineRenderer::LiDDArender3D(drawable, line2.map[currentIter], currentIter, z, line2.map[currentIter], longestline.map[line2.map[currentIter]], z2, zBuffer,
						drawable->getPixel(line2.map[currentIter], currentIter), drawable->getPixel(line2.map[currentIter], longestline.map[line2.map[currentIter]]));
				}
				else {
					currentIter = package.shorter1.origin.y - i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					z = zBuffer.at(line2.map[currentIter], currentIter);
					z2 = zBuffer.at(line2.map[currentIter], longestline.map[line2.map[currentIter]]);
					LineRenderer::LiDDArender3D(drawable, line2.map[currentIter], currentIter, z, line2.map[currentIter], longestline.map[line2.map[currentIter]], z2, zBuffer,
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
					z = zBuffer.at(currentIter, line3.map[currentIter]);
					z2 = zBuffer.at(currentIter, longestline.map[currentIter]);
					LineRenderer::LiDDArender3D(drawable, currentIter, line3.map[currentIter], z, currentIter, longestline.map[currentIter], z2, zBuffer,
						drawable->getPixel(currentIter, line3.map[currentIter]), drawable->getPixel(currentIter, longestline.map[currentIter]));
				}
				else {
					currentIter = package.shorter2.origin.x - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					z = zBuffer.at(currentIter, line3.map[currentIter]);
					z2 = zBuffer.at(currentIter, longestline.map[currentIter]);
					LineRenderer::LiDDArender3D(drawable, currentIter, line3.map[currentIter], z, currentIter, longestline.map[currentIter], z2, zBuffer,
						drawable->getPixel(currentIter, line3.map[currentIter]), drawable->getPixel(currentIter, longestline.map[currentIter]));
				}
			}
			else {       //line3 = yiter
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.y + i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					z = zBuffer.at(line3.map[currentIter], currentIter);
					z2 = zBuffer.at(line3.map[currentIter], longestline.map[line3.map[currentIter]]);
					LineRenderer::LiDDArender3D(drawable, line3.map[currentIter], currentIter, z, line3.map[currentIter], longestline.map[line3.map[currentIter]], z2, zBuffer,
						drawable->getPixel(line3.map[currentIter], currentIter), drawable->getPixel(line3.map[currentIter], longestline.map[line3.map[currentIter]]));
				}
				else {
					currentIter = package.shorter2.origin.y - i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					z = zBuffer.at(line3.map[currentIter], currentIter);
					z2 = zBuffer.at(line3.map[currentIter], longestline.map[line3.map[currentIter]]);
					LineRenderer::LiDDArender3D(drawable, line3.map[currentIter], currentIter, z, line3.map[currentIter], longestline.map[line3.map[currentIter]], z2, zBuffer,
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
					z = zBuffer.at(currentIter, line2.map[currentIter]);
					z2 = zBuffer.at(longestline.map[line2.map[currentIter]], line2.map[currentIter]);
					LineRenderer::LiDDArender3D(drawable, currentIter, line2.map[currentIter], z, longestline.map[line2.map[currentIter]], line2.map[currentIter], z2, zBuffer,
						drawable->getPixel(currentIter, line2.map[currentIter]), drawable->getPixel(longestline.map[line2.map[currentIter]], line2.map[currentIter]));
				}
				else {
					currentIter = package.shorter1.origin.x - i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					z = zBuffer.at(currentIter, line2.map[currentIter]);
					z2 = zBuffer.at(longestline.map[line2.map[currentIter]], line2.map[currentIter]);
					LineRenderer::LiDDArender3D(drawable, currentIter, line2.map[currentIter], z, longestline.map[line2.map[currentIter]], line2.map[currentIter], z2, zBuffer,
						drawable->getPixel(currentIter, line2.map[currentIter]), drawable->getPixel(longestline.map[line2.map[currentIter]], line2.map[currentIter]));
				}
			}
			else {     //line2 is a yiter
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.y + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					z = zBuffer.at(line2.map[currentIter], currentIter);
					z2 = zBuffer.at(longestline.map[currentIter], currentIter);
					LineRenderer::LiDDArender3D(drawable, line2.map[currentIter], currentIter, z, longestline.map[currentIter], currentIter, z2, zBuffer,
						drawable->getPixel(line2.map[currentIter], currentIter), drawable->getPixel(longestline.map[currentIter], currentIter));
				}
				else {
					currentIter = package.shorter1.origin.y - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					z = zBuffer.at(line2.map[currentIter], currentIter);
					z2 = zBuffer.at(longestline.map[currentIter], currentIter);
					LineRenderer::LiDDArender3D(drawable, line2.map[currentIter], currentIter, z, longestline.map[currentIter], currentIter, z2, zBuffer,
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
					z = zBuffer.at(currentIter, line3.map[currentIter]);
					z2 = zBuffer.at(longestline.map[line3.map[currentIter]], line3.map[currentIter]);
					LineRenderer::LiDDArender3D(drawable, currentIter, line3.map[currentIter], z, longestline.map[line3.map[currentIter]], line3.map[currentIter], z2, zBuffer,
						drawable->getPixel(currentIter, line3.map[currentIter]), drawable->getPixel(longestline.map[line3.map[currentIter]], line3.map[currentIter]));
				}
				else {
					currentIter = package.shorter2.origin.x - i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					z = zBuffer.at(currentIter, line3.map[currentIter]);
					z2 = zBuffer.at(longestline.map[line3.map[currentIter]], line3.map[currentIter]);
					LineRenderer::LiDDArender3D(drawable, currentIter, line3.map[currentIter], z, longestline.map[line3.map[currentIter]], line3.map[currentIter], z2, zBuffer,
						drawable->getPixel(currentIter, line3.map[currentIter]), drawable->getPixel(longestline.map[line3.map[currentIter]], line3.map[currentIter]));
				}
			}
			else {      //line3 is a yiter
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.y + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					z = zBuffer.at(line3.map[currentIter], currentIter);
					z2 = zBuffer.at(longestline.map[currentIter], currentIter);
					LineRenderer::LiDDArender3D(drawable, line3.map[currentIter], currentIter, z, longestline.map[currentIter], currentIter, z2, zBuffer,
						drawable->getPixel(line3.map[currentIter], currentIter), drawable->getPixel(longestline.map[currentIter], currentIter));
				}
				else {
					currentIter = package.shorter2.origin.y - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					z = zBuffer.at(line3.map[currentIter], currentIter);
					z2 = zBuffer.at(longestline.map[currentIter], currentIter);
					LineRenderer::LiDDArender3D(drawable, line3.map[currentIter], currentIter, z, longestline.map[currentIter], currentIter, z2, zBuffer,
						drawable->getPixel(line3.map[currentIter], currentIter), drawable->getPixel(longestline.map[currentIter], currentIter));
				}
			}
		}

	}
}

void PolyFill::WireTriangle3D(Drawable * drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint1, OctantWiz::Point3D endpoint2, Matrix & zBuffer, unsigned int color1, unsigned int color2, unsigned int color3) {
	LineRenderer::LiDDArender3D(drawable, origin, endpoint1, zBuffer, color1, color2);
	LineRenderer::LiDDArender3D(drawable, origin, endpoint2, zBuffer, color1, color3);
	LineRenderer::LiDDArender3D(drawable, endpoint1, endpoint2, zBuffer, color2, color3);
}

void PolyFill::RealLiTriangle(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2, unsigned int color1, unsigned int color2, unsigned int color3) {
	std::vector<OctantWiz::Point> list;
	OctantWiz::Point top, middle, bottom;
	list.push_back(origin);
	list.push_back(endpoint1);
	list.push_back(endpoint2);
	bool leftIsVar = false;

	bottom = MathWiz::GetLargestYAndRemoveIt(list);
	middle = MathWiz::GetLargestYAndRemoveIt(list);
	top = MathWiz::GetLargestYAndRemoveIt(list);

	double gradient = MathWiz::GetReverseGradient(top, middle);
	double fgradient = MathWiz::GetReverseGradient(top, bottom);

	//Initialization of variables
	double leftpoint, rightpoint;
	double lgradient, rgradient;
	unsigned int leftcolor, rightcolor;
	double leftredgr, leftbluegr, leftgreengr;
	double rightredgr, rightbluegr, rightgreengr;

	//Assignment of variables
	if (middle.x <= bottom.x) {
		leftpoint = top.x + gradient;
		rightpoint = top.x + fgradient;
		lgradient = gradient;
		rgradient = fgradient;
		if (top.x == middle.x) {
			lgradient = 0;
		}
		else if (top.x == bottom.x) {
			rgradient = 0;
		}
		leftIsVar = true;

		//Color interpolation for left
		int range = middle.y - top.y;

		int red1 = ((color2 >> 16) & 0xff) - ((color1 >> 16) & 0xff);
		leftredgr = static_cast<double>(red1) / static_cast<double>(range);
		
		int green1 = ((color2 >> 8) & 0xff) - ((color1 >> 8) & 0xff);
		leftgreengr = static_cast<double>(green1) / static_cast<double>(range);
		
		int blue1 = (color2 & 0xff) - (color1 & 0xff);
		leftbluegr = static_cast<double>(blue1) / static_cast<double>(range);

		leftcolor = color1;
		MathWiz::InterpolateColorOnce(leftcolor, leftredgr, leftgreengr, leftbluegr);

		//Color interpolation for right
		int range2 = bottom.y - top.y;

		int red2 = ((color3 >> 16) & 0xff) - ((color1 >> 16) & 0xff);
		rightredgr = static_cast<double>(red2) / static_cast<double>(range2);

		int green2 = ((color3 >> 8) & 0xff) - ((color1 >> 8) & 0xff);
		rightgreengr = static_cast<double>(green2) / static_cast<double>(range2);

		int blue2 = (color3 & 0xff) - (color1 & 0xff);
		rightbluegr = static_cast<double>(blue2) / static_cast<double>(range2);

		rightcolor = color1;
		MathWiz::InterpolateColorOnce(rightcolor, rightredgr, rightgreengr, rightbluegr);
	}
	else {
		leftpoint = top.x + fgradient;
		rightpoint = top.x + gradient;
		lgradient = fgradient;
		rgradient = gradient;
		if (top.x == middle.x) {
			rgradient = 0;
		}
		else if (top.x == bottom.x) {
			lgradient = 0;
		}
		leftIsVar = false;

		//Color interpolation for left
		leftredgr = (((color3 >> 16) & 0xff) - ((color1 >> 16) & 0xff)) / (bottom.y - top.y);
		leftgreengr = (((color3 >> 8) & 0xff) - ((color1 >> 8) & 0xff)) / (bottom.y - top.y);
		leftbluegr = ((color3 & 0xff) - (color1 & 0xff)) / (bottom.y - top.y);
		leftcolor = color1;
		MathWiz::InterpolateColorOnce(leftcolor, leftredgr, leftgreengr, leftbluegr);

		//Color interpolation for right
		rightredgr = (((color2 >> 16) & 0xff) - ((color1 >> 16) & 0xff)) / (middle.y - top.y);
		rightgreengr = (((color2 >> 8) & 0xff) - ((color1 >> 8) & 0xff)) / (middle.y - top.y);
		rightbluegr = ((color2 & 0xff) - (color1 & 0xff)) / (middle.y - top.y);
		rightcolor = color1;
		MathWiz::InterpolateColorOnce(rightcolor, rightredgr, rightgreengr, rightbluegr);
	}

	unsigned int color = leftcolor;
	double redgr, greengr, bluegr;

	redgr = (((rightcolor >> 16) & 0xff) - ((leftcolor >> 16) & 0xff)) / (rightpoint - leftpoint);
	greengr = (((rightcolor >> 8) & 0xff) - ((leftcolor >> 8) & 0xff)) / (rightpoint - leftpoint);
	bluegr = ((rightcolor & 0xff) - (leftcolor & 0xff)) / (rightpoint - leftpoint);

	for (int y = top.y + 1; y < middle.y; y++) {
		for (int x = leftpoint; x <= rightpoint - 1; x++) {
			drawable->setPixel(x, y, color);
			MathWiz::InterpolateColorOnce(color, redgr, greengr, bluegr);
		}
		leftpoint += lgradient;
		rightpoint += rgradient;

		MathWiz::InterpolateColorOnce(leftcolor, leftredgr, leftgreengr, leftbluegr);
		MathWiz::InterpolateColorOnce(rightcolor, rightredgr, rightgreengr, rightbluegr);

		redgr = (((rightcolor >> 16) & 0xff) - ((leftcolor >> 16) & 0xff)) / (rightpoint - leftpoint);
		greengr = (((rightcolor >> 8) & 0xff) - ((leftcolor >> 8) & 0xff)) / (rightpoint - leftpoint);
		bluegr = ((rightcolor & 0xff) - (leftcolor & 0xff)) / (rightpoint - leftpoint);

		color = leftcolor;
	}



	if (leftIsVar) {
		lgradient = MathWiz::GetReverseGradient(middle, bottom);
		if (middle.x == bottom.x) {
			lgradient = 0;
		}
		leftpoint = middle.x;

		leftcolor = color2;

		leftredgr = (((color3 >> 16) & 0xff) - ((color2 >> 16) & 0xff)) / abs(bottom.y - middle.y);
		leftgreengr = (((color3 >> 8) & 0xff) - ((color2 >> 8) & 0xff)) / abs(bottom.y - middle.y);
		leftbluegr = ((color3 & 0xff) - (color2 & 0xff)) / abs(bottom.y - middle.y);
	}
	else {
		rgradient = MathWiz::GetReverseGradient(middle, bottom);
		if (middle.x == bottom.x) {
			rgradient = 0;
		}
		rightpoint = middle.x;

		rightcolor = color2;

		rightredgr = (((color3 >> 16) & 0xff) - ((color2 >> 16) & 0xff)) / abs(bottom.y - middle.y);
		rightgreengr = (((color3 >> 8) & 0xff) - ((color2 >> 8) & 0xff)) / abs(bottom.y - middle.y);
		rightbluegr = ((color3 & 0xff) - (color2 & 0xff)) / abs(bottom.y - middle.y);
	}

	redgr = (((rightcolor >> 16) & 0xff) - ((leftcolor >> 16) & 0xff)) / abs(rightpoint - leftpoint);
	greengr = (((rightcolor >> 8) & 0xff) - ((leftcolor >> 8) & 0xff)) / abs(rightpoint - leftpoint);
	bluegr = ((rightcolor & 0xff) - (leftcolor & 0xff)) / abs(rightpoint - leftpoint);

	for (int y = middle.y; y < bottom.y; y++) {
		for (int x = leftpoint; x <= rightpoint - 1; x++) {
			drawable->setPixel(x, y, color);
			MathWiz::InterpolateColorOnce(color, redgr, greengr, bluegr);
		}
		leftpoint += lgradient;
		rightpoint += rgradient;

		MathWiz::InterpolateColorOnce(leftcolor, leftredgr, leftgreengr, leftbluegr);
		MathWiz::InterpolateColorOnce(rightcolor, rightredgr, rightgreengr, rightbluegr);

		redgr = (((rightcolor >> 16) & 0xff) - ((leftcolor >> 16) & 0xff)) / abs(rightpoint - leftpoint);
		greengr = (((rightcolor >> 8) & 0xff) - ((leftcolor >> 8) & 0xff)) / abs(rightpoint - leftpoint);
		bluegr = ((rightcolor & 0xff) - (leftcolor & 0xff)) / abs(rightpoint - leftpoint);

		color = leftcolor;
	}
}
