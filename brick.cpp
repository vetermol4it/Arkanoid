#pragma once

class brick
{
public:
	bool isActive;

	brick()
	{
		weight = 20;
		height = 20;
		hit = 2;
		isActive = false;
	}
	brick(short row_, short col_, float hit_) 
	{
		if (row_ > 10) row = 10;
		else if (row_ < 0) row = 0;
		else row = row_;
		
		if (col_ > 15) col = 15;
		else if (col_ < 0) col = 0;
		else col = col_;

		if (hit_ > 2) hit = 2;
		else if (hit_ <= 0) hit = 0;
		else hit = hit_;
	}
	
	void setRow(float row_) 
	{
		if (row_ > 10) row = 10;
		else if (row_ < 0) row = 0;
		else row = row_;
	}
	void setCol(float col_) 
	{
		if (col_ > 15) col = 15;
		else if (col_ < 0) col = 0;
		else col = col_;
	}
	void setHit(float h)
	{
		if (h > 2) hit = 2;
		else if (h <= 0) hit = 0;
		else hit = h;
	}
	short getHit()
	{
		return hit;
	}
	short getRow()
	{
		return row;
	}
	short getCol()
	{
		return col;
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
	short hit;
	float weight, height;
	short row, col;
};