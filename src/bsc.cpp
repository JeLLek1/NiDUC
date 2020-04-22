#include "bsc.h"
#include <ctime>
#include <cmath> 

void Bsc::noise(std::vector<uint8_t> &data,int prop)
{
	std::srand(time(nullptr));
	for(unsigned int i=0; i<data.size();i++)
	{
		uint8_t bit=1;
		for(int j=0;j<8;j++)
		{	
			
			if((rand()%1000)<prop)
			{
				data[i] ^= bit;
			}
			bit<<=1;
		}
	}
}
