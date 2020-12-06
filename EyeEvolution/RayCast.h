#pragma once
#include<SFML/Graphics/Shape.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace sf;
class Hit
{
public:
	bool bHit;
	double hitDist;
	Vector2f hitPos;
	Hit()
	{
		bHit = false;
		hitDist = 0;
		hitPos = Vector2f(0, 0);
	}
	Hit(bool bh, double hd, Vector2f hp)
	{
		bHit = bh;
		hitDist = hd;
		hitPos = hp;
	}
};
class Ray
{
public:
	VertexArray line;
	Ray()
	{
		VertexArray line(LinesStrip, 2);

	}
};
class DirectionVec
{
	int xVec, yVec;
public:
	DirectionVec(float x, float y)
	{
		xVec = x; yVec = y;
	}
	float getXDir()
	{
		if (xVec > 0) return 0.1;
		return -0.1;
	}
	float getYDir()
	{
		if (yVec > 0) return 0.1;
		return -0.1;
	}
};
DirectionVec getVec(float spriteposx, float spriteposy, float blockposx, float blockposy)
{
	float xDiff, yDiff;
	xDiff = spriteposx - blockposx;
	yDiff = spriteposy = blockposy;
	DirectionVec thisDirectionVec(xDiff, yDiff);
	return thisDirectionVec;
}