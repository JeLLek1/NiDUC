#include "gilbert.h"

void Gilbert::noiseG(std::vector<uint8_t> &data,int prop1,int prop2)
{
	bool isB=false;
	for(unsigned int i=0; i<data.size();i++)
	{
		uint8_t bit=1;
		for(int j=0;j<8;j++)
		{	
			
			if(isB==false&&(rand()%1000)<prop1)
			{
				data[i] ^= bit;
				isB=true;
			}
			else 
			{
				if(isB==true&&(rand()%1000)<prop2)
				{
					data[i] ^= bit;
				}
				else
				{
					isB=false;
				}
			}
			bit<<=1;
		}
	}
}