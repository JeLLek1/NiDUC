#include <vector>

#include <ezpwd/rs>
#include <ezpwd/bch>
#include <iostream>

#define CODE_N 255	//n - slowo kodowe
#define	CODE_K 239	//k - blok danych zakodowanych
#define CODE_T 2   	//t - korekcja

struct userBer{
	double rsBsc, bchBsc, tripleBsc, rsGil, bchGil, tripleGil;
};

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

	ezpwd::RS<CODE_N, CODE_N-CODE_T> rs;
	ezpwd::BCH<CODE_N,CODE_K,CODE_T> bch;

	Menu();
	static int cinInt(int max);
	void display();
	void loadValues();
	void dataEncode();
	void dataDecode();
	long errorCount(std::vector<uint8_t> dataTest);
	userBer checkBer();

	void channel();

	void showValuesByte(std::vector<uint8_t> &data);

	void tests(size_t number);

	void clearVector();
	
	~Menu();
};