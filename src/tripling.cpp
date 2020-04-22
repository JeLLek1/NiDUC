#include "tripling.h"

void Tripling::encode(std::vector<uint8_t> data){
	int oldDataLength= data.size();
	for(int i=0; i<oldDataLength; i++){
		data.push_back(static_cast<uint8_t>(0));
	}
	for(int i=oldDataLength-1; i>=0; i--){
		//std::cout<<(char)data.at(i);
	}
}