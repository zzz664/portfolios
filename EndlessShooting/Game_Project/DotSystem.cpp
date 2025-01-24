#include "DotSystem.h"
#include "Game2D.h"

using namespace jm;

DotSystem::DotSystem(int (*data)[16], float dot_size)
{
	w = h = 16;

	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			this->data[i][j] = data[i][j];
		}
	}

	this->dot_size = dot_size;
}

DotSystem::~DotSystem()
{

}

void DotSystem::render()
{
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			translate(dot_size, 0.0f);

			if (data[i][j] == 1)
			{
				drawFilledBox(Colors::black, dot_size, dot_size);
			}
			if (data[i][j] == 2)
			{
				drawFilledBox(Colors::skyblue, dot_size, dot_size);
			}
			if (data[i][j] == 3)
			{
				drawFilledBox(Colors::red, dot_size, dot_size);
			}
			if (data[i][j] == 4)
			{
				drawFilledBox(Colors::gray, dot_size, dot_size);
			}
			if (data[i][j] == 5)
			{
				drawFilledBox(Colors::orange, dot_size, dot_size);
			}
			if (data[i][j] == 6)
			{
				drawFilledBox(Colors::yellow, dot_size, dot_size);
			}
			if (data[i][j] == 7)
			{
				drawFilledBox(Colors::whiteblue, dot_size, dot_size);
			}
			if (data[i][j] == 8)
			{
				drawFilledBox(Colors::white, dot_size, dot_size);
			}
		}
		translate(-(dot_size * 16), -dot_size);
	}
}
