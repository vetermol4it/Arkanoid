#pragma once

#include <cmath>
#include "brick.cpp"
#include "bit.cpp"

class ball {
public:
	bool isActive;

	ball()
	{
		coordX = 0;
		coordY = 290;
		directionX = 4;
		directionY = -4;
		radius = 2;
	}
	ball(float y, float rad) 
	{
		if (y > 300) coordY = 300;
		else if (y <= 0) coordY = 0;
		else coordY = y;

		if (rad > 10) radius = 10;
		else if (rad < 1) radius = 1;
		else radius = rad;

		isActive = false;
	}
	
	void move(bit b)
	{ //Движение мяча и проверка столкновения с границами и битой
		coordX += directionX;
		coordY += directionY;
		if (coordX - radius <= 0) //Приближение к границе по Х
		{
			coordX = radius;
			directionX *= -1;
		}
		else if (coordY - radius <= 0) //Приближение к границе по Y
		{
			coordY = radius;
			directionY *= -1;
		}
		else if (coordX + radius >= 300)  //Приближение к другой границе по X
		{
			coordX = 300 - radius;
			directionX *= -1;
		}
		else if (coordY + radius >= b.getCoordY() && coordY + radius <= b.getCoordY() + b.getHeight() && coordX > b.getCoordX() && coordX < b.getCoordX() + b.getWeight()) //Касание биты
		{
			coordY = b.getCoordY() - radius;
			directionY *= -1;
		}
		else if (coordY >= 300) //Приближение к нижней границe
			isActive = false;
	}
	bool isCollision(brick b)
	{
		if (b.isActive)
		{
			if (abs(coordX - b.getCol() * b.getWeight() - b.getWeight() / 2 - 2) <= radius + b.getWeight() / 2 && abs(coordY - b.getRow() * b.getHeight() - b.getHeight() / 2 - 2) <= radius + b.getHeight() / 2)
			{
				if (sqrt((b.getCol()*b.getWeight() + b.getWeight() / 2 - coordX)*(b.getCol()*b.getWeight() + b.getWeight() / 2 - coordX) + (b.getRow()*b.getHeight() + b.getHeight() / 2 - coordY)*(b.getRow()*b.getHeight() + b.getHeight() / 2 - coordY))
					- (b.getWeight() / 2 - 1)*sqrt(2.0) - radius > radius*(sqrt(2.0) - 1))
					return 0;
				else
					return 1;
			}
		}
		return 0;
	}

	void setCoordX(float coord)
	{
		if (coord > 300) coordX = 300;
		else if (coord < -300) coordX = -300;
		else coordX = coord;
	}
	void setCoordY(float coord)
	{
		if (coord > 300) coordY = 300;
		else if (coord <= 0) coordY = 0;
		else coordY = coord;
	}
	void setDirectionX(float direction)
	{
		if (direction > 10) directionX = 10;
		else if (direction < -10) directionX = -10;
		else directionX = direction;
	}
	void setDirectionY(float direction)
	{
		if (direction > 10) directionY = 10;
		else if (direction < -10) directionY = -10;
		else directionY = direction;
	}
	void setRadius(float rad) 
	{
		if (rad > 10) radius = 10;
		else if (rad < 1) radius = 1;
		else radius = rad;
	}
	float getCoordX()
	{
		return coordX;
	}
	float getCoordY()
	{
		return coordY;
	}
	float getDirectionX() 
	{
		return directionX;
	}
	float getDirectionY() 
	{
		return directionY;
	}
	float getRadius() 
	{
		return radius;
	}

private:
	float coordX, coordY, directionX, directionY, radius;
};