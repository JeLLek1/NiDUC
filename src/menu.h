#include <vector>

#include <iostream>

class Menu{
public:
	std::vector<uint8_t> data;
	std::vector<uint8_t> dataRs;
	std::vector<uint8_t> dataBch;
	std::vector<uint8_t> dataTripling;
	int parity;
	int symbols;

	Menu();
	static int cinInt();
	void display();
	void loadValues();
	void dataEncode();

	void showValuesByte();
	~Menu();
};