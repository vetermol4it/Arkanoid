#pragma once

class bit {
public:
	bit() {
		coordX = 150;
		coordY = 290;
		weight = 80;
		height = 8;
	}
	bit(float coordX_, float weight_, float height_) {
		if (coordX_ > 300) coordX = 300;
		else if (coordX_ < -300) coordX = -300;
		else coordX = coordX_;

		if (weight_ > 100) weight = 100;
		else if (weight_ < 10) weight = 10;
		else weight = weight_;

		if (height_ > 20) height = 20;
		else if (height_ < 1) height = 1;
		else height = height_;

		coordY = 290;
	}
	void setCoordX(float coord)
	{
		if (coord > 300) coordX = 300;
		else if (coord < -300) coordX = -300;
		else coordX = coord;
	}
	void setWeight(float w)
	{
		if (w > 100) weight = 100;
		else if (w < 10) weight = 10;
		else weight = w;
	}
	void setHeight(float h)
	{
		if (h > 20) height = 20;
		else if (h < 1) height = 1;
		else height = h;
	}
	float getCoordX()
	{
		return coordX;
	}
	float getCoordY()
	{
		return coordY;
	}
	float getWeight()
	{
		return weight;
	}
	float getHeight()
	{
		return height;
	}
private:
	float coordX, coordY, weight, height;
};