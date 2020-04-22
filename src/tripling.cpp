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
	
}