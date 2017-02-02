#include "PolyFill.h"
#include "LineRender.h"

void PolyFill::Triangle(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2) {
	unsigned int color = 0xff000000;
	int currentIter;
	//PolyFill::LongestTriLine package1 = DetermineLongest(origin, endpoint1, endpoint2);

	LineRenderer::FillPack line11 = LineRenderer::PolyDDArender(drawable, origin, endpoint1, color);
	LineRenderer::FillPack line22 = LineRenderer::PolyDDArender(drawable, origin, endpoint2, color);
	LineRenderer::FillPack line33 = LineRenderer::PolyDDArender(drawable, endpoint1, endpoint2, color);
	PolyFill::LongestTriLine package = LineRenderer::FindLongest(line11, line22, line33);

	LineRenderer::FillPack longestline = LineRenderer::PolyDDArender(drawable, package.longest.origin, package.longest.endpoint, color);
	LineRenderer::FillPack line2 = LineRenderer::PolyDDArender(drawable, package.shorter1.origin, package.shorter1.endpoint, color);
	LineRenderer::FillPack line3 = LineRenderer::PolyDDArender(drawable, package.shorter2.origin, package.shorter2.endpoint, color);
	int something;

	if (longestline.xiter) {
		for (int i = 0; i < line2.map.size(); i++) {
			if (line2.xiter) {
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.x + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
				else {
					currentIter = package.shorter1.origin.x - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
			}
			else {     //line2 = yiter
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.y + i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], color);
				}
				else {
					currentIter = package.shorter1.origin.y - i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], color);
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
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
				else {
					currentIter = package.shorter2.origin.x - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
			}
			else {       //line3 = yiter
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.y + i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line3.map[currentIter], currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], color);
				}
				else {
					currentIter = package.shorter2.origin.y - i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line3.map[currentIter], currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], color);
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
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], line2.map[currentIter], color);
				}
				else {
					currentIter = package.shorter1.origin.x - i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], line2.map[currentIter], color);
				}
			}
			else {     //line2 is a yiter
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.y + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
				}
				else {
					currentIter = package.shorter1.origin.y - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
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
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], line3.map[currentIter], color);
				}
				else {
					currentIter = package.shorter2.origin.x - i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], line3.map[currentIter], color);
				}
			}
			else {      //line3 is a yiter
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.y + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line3.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
				}
				else {
					currentIter = package.shorter2.origin.y - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line3.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
				}
			}
		}
		
	}
}
/*
PolyFill::LongestTriLine PolyFill::DetermineLongest(OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2) {
	
	double dist1 = MathWiz::PointDistance(origin, endpoint1);
	double dist2 = MathWiz::PointDistance(origin, endpoint2);
	double dist3 = MathWiz::PointDistance(endpoint1, endpoint2);
	
	LinePair pair1 = LinePair(origin, endpoint1);
	LinePair pair2 = LinePair(origin, endpoint2);
	LinePair pair3 = LinePair(endpoint1, endpoint2);

	int s1 = abs(pair1.endpoint.y - pair1.origin.y);
	int s2 = abs(pair2.endpoint.y - pair2.origin.y);
	int s3 = abs(pair3.endpoint.y - pair3.origin.y);

	int q1 = abs(pair1.endpoint.x - pair1.origin.x);
	int q2 = abs(pair2.endpoint.x - pair2.origin.x);
	int q3 = abs(pair3.endpoint.x - pair3.origin.x);

	double largest = MathWiz::LargestOfThree(dist1, dist2, dist3);
	double largest2 = MathWiz::LargestOfThree(s1, s2, s3);
	/*
	if (s1 >= s2 && s1 >= s3) {
		return LongestTriLine(pair1, pair2, pair3);
	}
	else if (s2 >= s1 && s2 >= s3) {
		return LongestTriLine(pair2, pair1, pair3);
	}
	else {
		return LongestTriLine(pair3, pair1, pair2);
	}
	*/
	/*
	if (largest == dist1) {
		if ((s1 >= s2 && s1 >= s3) || (q1 >= q2 && q1 >= q3)) {
			return LongestTriLine(pair1, pair2, pair3);
		}
		else {
			if (s1 >= s2 && s1 >= s3) {
				return LongestTriLine(pair1, pair2, pair3);
			}
			else if (s2 >= s1 && s2 >= s3) {
				return LongestTriLine(pair2, pair1, pair3);
			}
			else {
				return LongestTriLine(pair3, pair1, pair2);
			}
		}
	}
	else if (largest == dist2) {
		if ((s2 >= s1 && s2 >= s3) || (q2 >= q1 && q2 >= q3)) {
			return LongestTriLine(pair2, pair1, pair3);
		}
		else {
			if (s1 >= s2 && s1 >= s3) {
				return LongestTriLine(pair1, pair2, pair3);
			}
			else if (s2 >= s1 && s2 >= s3) {
				return LongestTriLine(pair2, pair1, pair3);
			}
			else {
				return LongestTriLine(pair3, pair1, pair2);
			}
		}
	}
	else {
		if ((s3 >= s1 && s3 >= s2) || (q3 >= q1 && q3 >= q2)) {
			return LongestTriLine(pair3, pair1, pair2);
		}
		else {
			if (s1 >= s2 && s1 >= s3) {
				return LongestTriLine(pair1, pair2, pair3);
			}
			else if (s2 >= s1 && s2 >= s3) {
				return LongestTriLine(pair2, pair1, pair3);
			}
			else {
				return LongestTriLine(pair3, pair1, pair2);
			}
		}
	}
}
*/

/*
PolyFill::LongestTriLine PolyFill::FindLongest(LineRenderer::FillPack line1, LineRenderer::FillPack line2, LineRenderer::FillPack line3) {
	LinePair pair1 = LinePair(line1.origin, line1.endpoint);
	LinePair pair2 = LinePair(line2.origin, line2.endpoint);
	LinePair pair3 = LinePair(line3.origin, line3.endpoint);
	
	bool trial1 = TestForLongest(line1, line2, line3);
	bool trial2 = TestForLongest(line2, line1, line3);
	bool trial3 = TestForLongest(line3, line1, line2);

	if (trial1) {
		return LongestTriLine(pair1, pair2, pair3);
	}
	else if (trial2) {
		return LongestTriLine(pair2, pair1, pair3);
	}
	else {
		return LongestTriLine(pair3, pair1, pair2);
	}
}
*/
/*
bool PolyFill::TestForLongest(LineRenderer::FillPack line1, LineRenderer::FillPack line2, LineRenderer::FillPack line3) {
	bool flag = true;
	int currentIter;

	if (line1.xiter) {
		for (int i = 0; i < line2.map.size(); i++) {
			if (line2.xiter) {
				if (line2.movepositive) {
					currentIter = line2.origin.x + i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line2.origin.x - i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
			else {     //line2 = yiter
				if (line2.movepositive) {
					currentIter = line2.origin.y + i;
					if (line1.map.find(line2.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line2.origin.y - i;
					if (line1.map.find(line2.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
		}
		for (int i = 0; i < line3.map.size(); i++) {
			if (line3.xiter) {
				if (line3.movepositive) {
					currentIter = line3.origin.x + i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line3.origin.x - i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
			else {       //line3 = yiter
				if (line3.movepositive) {
					currentIter = line3.origin.y + i;
					if (line1.map.find(line3.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line3.origin.y - i;
					if (line1.map.find(line3.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
		}

	}
	else {    //longestline is a yiter
		for (int i = 0; i < line2.map.size(); i++) {
			if (line2.xiter) {
				if (line2.movepositive) {
					currentIter = line2.origin.x + i;
					if (line1.map.find(line2.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line2.origin.x - i;
					if (line1.map.find(line2.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
			else {     //line2 is a yiter
				if (line2.movepositive) {
					currentIter = line2.origin.y + i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line2.origin.y - i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
		}
		for (int i = 0; i < line3.map.size(); i++) {
			if (line3.xiter) {
				if (line3.movepositive) {
					currentIter = line3.origin.x + i;
					if (line1.map.find(line3.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line3.origin.x - i;
					if (line1.map.find(line3.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
			else {      //line3 is a yiter
				if (line3.movepositive) {
					currentIter = line3.origin.y + i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line3.origin.y - i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
		}
	}
	return flag;
}
*/