#include <vector>

#include <iostream>

class Menu{
public:
	std::vector<uint8_t> data;
	std::vector<uint8_t> dataRs;
	std::vector<uint8_t> dataBch;
	std::vector<uint8_t> dataTripling;
	std::vector<uint8_t> dataRsG;
	std::vector<uint8_t> dataBchG;
	std::vector<uint8_t> dataTriplingG;
	int bscInPromils;
	int symbols;

	Menu();
	static int cinInt(int max);
	void display();
	void loadValues();
	void dataEncode();
	void dataDecode();
	
	void chanel();

	void showValuesByte(std::vector<uint8_t> &data);

	~Menu();
};