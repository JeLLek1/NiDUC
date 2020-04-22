#include "tripling.h"

void Tripling::encode(std::vector<uint8_t> &data){
	int oldDataLength= data.size();
	for(int i=0; i<oldDataLength*2; i++){
		data.push_back(static_cast<uint8_t>(0));
	}
	
	int bitIndex = 0;
	size_t newSize= data.size();
	for(int i=oldDataLength-1; i>=0; i--){
		uint8_t temp = data[i];
		data[i] = 0;

		for(int j=0; j<8; j++){
			
			uint8_t bit = 1;
			bit<<=j;

			bit&=temp;

			if(bit!=0){
				uint8_t bitNew=1;
				bitNew<<=(bitIndex%8);
				data[newSize-(bitIndex>>3)-1]+=bitNew;
				bitIndex++;
				bitNew = 1;
				bitNew<<=(bitIndex%8);
				data[newSize-(bitIndex>>3)-1]+=bitNew;
				bitIndex++;
				bitNew = 1;
				bitNew<<=(bitIndex%8);
				data[newSize-(bitIndex>>3)-1]+=bitNew;
				bitIndex++;
			}else{
				 bitIndex+=3;
			}
			
		}
	}
}

void Tripling::decode(std::vector<uint8_t> &data){
	unsigned int length=(data.size()<<3)/3;
	for(unsigned int i=0; i<length; i++){
		int count = 0;

		uint8_t bit = 1;
		bit<<=(7-((3*i)%8));
		size_t index = (i*3)>>3;
		uint8_t bit1 = data[index]&bit;
		if(bit1!=0){
			count++;
			data[index]-=bit;
		}

		bit = 1;
		bit<<=(7-((3*i+1)%8));
		index = (i*3+1)>>3;
		if(bit1!=0){
			count++;
			data[index]-=bit;
		}

		bit = 1;
		bit<<=(7-((3*i+2)%8));
		index = (i*3+2)>>3;
		bit1 = data[index]&bit;
		if(bit1!=0){
			count++;
			data[index]-=bit;
		}
		if(count>=2){
			bit = 1;
			bit<<=(7-(i%8));
			index = i>>3;
			data[index]+=bit;
		}
	}
	data.resize((data.size()/3));
}