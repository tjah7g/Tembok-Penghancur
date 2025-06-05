
#ifndef LEVEL_H
#define LEVEL_H

#ifdef _MSC_VER
#pragma once
#endif  

#include "Instance.h"

class Level : public Instance
{
	vector<int> brickType;
	vector<Brick> bricks;
	
public:

	Level();
	Level(vector<int>& brickType);
	void render();
	void update();

private:
	void draw();
	void buildBricks();
};
#endif

