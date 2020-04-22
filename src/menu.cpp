#include "menu.h"
#include <ezpwd/rs>
#include <ezpwd/bch>
#include <ctime>
#include <cmath>
#include <bitset>
#include <stdexcept>


#include "tripling.cpp"
#include "bsc.cpp"

#define MAXSYMBOLS 255
#define	PARITYSYMBOLS 16
#define BCHCAPACITY 2

Menu::Menu(){
	this->bscInPromils = 0;
	this->symbols = 0;

}

int Menu::cinInt(int max){
	int value;
	std::cin>>value;
	while(std::cin.good()==false){
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout<<"Podaj wartosc calkowita: ";
		std::cin >> value;
	}

	while(value>max || value<0){
		std::cout<<"Podaj wartosc w przedziale [0;"<<max<<"]: ";
		std::cin>>value;
		while(std::cin.good()==false){
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout<<"Podaj wartosc calkowita: ";
			std::cin >> value;
		}
	}
	return value;
}

void Menu::display(){
	std::cout<<"Uswawienia: \nMaksymalna ilość symboli: "<<MAXSYMBOLS<<"\nIlość symboli nadmiarowych: "<<PARITYSYMBOLS<<"\nmożliwość korekcyjna BSC: "<<BCHCAPACITY<<"\n";
	
		std::cout<<"Podaj ilość danych do przetestowania: ";

		this->symbols=this->cinInt(MAXSYMBOLS-PARITYSYMBOLS);

		std::cout<<"Podaj szanse na zmiane bitu w kanale BSC [promile]: ";
		this->bscInPromils=this->cinInt(1000);

		this->loadValues();

		this->dataEncode();

		std::cout<<"Dane wprowadzone i zakodowane: \n";

		std::cout<<"Dane przed zakodowaniem: \n";
		this->showValuesByte(this->data);
		std::cout<<"\nDane zakodowane kodem bsh: \n";
		this->showValuesByte(this->dataBch);
		std::cout<<"\nDane zakodowane kodem rs: \n";
		this->showValuesByte(this->dataRs);
		std::cout<<"\nDane zakodowane kodem potrojeniowym: \n";
		this->showValuesByte(this->dataTripling);

		std::cout<<"\n\n[Przesyłanie kanałem transmisyjnym...]: \n\n";

		this->chanel();

		std::cout<<"\nDane zakodowane kodem bsh: \n";
		this->showValuesByte(this->dataBch);
		std::cout<<"\nDane zakodowane kodem rs: \n";
		this->showValuesByte(this->dataRs);
		std::cout<<"\nDane zakodowane kodem potrojeniowym: \n";
		this->showValuesByte(this->dataTripling);

		std::cout<<"\n\n[Dekodowanie danych oraz odrzucanie nadmiarowych bitow..]\n\n";
}

void Menu::loadValues(){
	std::srand(time(nullptr));
	for(int i=0; i<this->symbols; i++){
		this->data.push_back(static_cast<uint8_t>(std::rand()%256));
	}
	dataRs.insert(dataRs.end(), data.begin(), data.end());
	dataBch.insert(dataBch.end(), data.begin(), data.end());
	dataTripling.insert(dataTripling.end(), data.begin(), data.end());
}

void Menu::chanel(){
	dataRsG.insert(dataRsG.end(), data.begin(), data.end());
	dataBchG.insert(dataBchG.end(), data.begin(), data.end());
	dataTriplingG.insert(dataTriplingG.end(), data.begin(), data.end());

	Bsc::noise(dataRsG,this->bscInPromils);
	Bsc::noise(dataBchG,this->bscInPromils);
	Bsc::noise(dataTriplingG,this->bscInPromils);
}

void Menu::dataEncode(){
	Tripling::encode(dataTripling);
	ezpwd::RS<MAXSYMBOLS, MAXSYMBOLS-PARITYSYMBOLS> rs;
	ezpwd::BCH<MAXSYMBOLS,MAXSYMBOLS-PARITYSYMBOLS,BCHCAPACITY> bch;

	rs.encode(dataRs);
	bch.encode(dataBch);

}

void Menu::dataDecode(){

}

void Menu::showValuesByte(std::vector<uint8_t> &data){

	for(unsigned int i=0; i<data.size(); i++){
		std::bitset<8> x(data.at(i));
		std::cout<<x<<" ";
	}
}

Menu::~Menu(){

}