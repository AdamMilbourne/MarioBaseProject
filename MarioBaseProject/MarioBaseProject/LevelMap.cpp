#include "LevelMap.h"

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	//Allocate memory for level map
	m_map = new int* [MAP_HEIGHT];
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		m_map[i] = new int[MAP_WIDTH];
	}
	//populate the array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			m_map[i][j] = map[i][j];
		}
	}
}

LevelMap::~LevelMap()
{
	//delete all elements of the array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] m_map[i];
	}
	delete[]m_map;
}

int LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return m_map[h][w];
	}
	return 0;
}

void LevelMap::ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value)
{
	//row 9 
	//column 8 & 9

	//if mario/luigi collide with pow block (implement bottom of block later) 
	//change row 9 column 8 to 0 
	//change row 9 column 8 to 0

}

//void LevelMap::ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value)
//{
//	if (/*collision between 2 Rects? one being player one being the object*/)                   ATTEMPT AT THE ADDITIONAL TASK, NOT SURE HOW TO HAVE IT HAPPEN TO ANY SPACE NEEDED
//	{
//		ChangeTileAt(/*pos1, pos2, change to number*/)
//	}
//}