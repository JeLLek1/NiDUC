#include <vector>

#include <ezpwd/rs>
#include <ezpwd/bch>
#include <iostream>

#define MAXSYMBOLS 255
#define	PARITYSYMBOLS 16
#define BCHCAPACITY 2

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
	int prop1;
	int prop2;

	ezpwd::RS<MAXSYMBOLS, MAXSYMBOLS-PARITYSYMBOLS> rs;
	ezpwd::BCH<MAXSYMBOLS,MAXSYMBOLS-PARITYSYMBOLS,BCHCAPACITY> bch;

	Menu();
	static int cinInt(int max);
	void display();
	void loadValues();
	void dataEncode();
	void dataDecode();
	
	void chanel();

	void showValuesByte(std::vector<uint8_t> &data);

	void tests();
	
	~Menu();
};