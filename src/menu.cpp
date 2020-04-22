#include "menu.h"
#include <ctime>
#include <cmath>
#include <bitset>
#include <stdexcept>


#include "tripling.cpp"
#include "bsc.cpp"
#include "gilbert.cpp"

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
		std::cout<<"Podaj szanse na zmiane bitu w kanale Gilberta (dobra seria)[promile]: ";
		this->prop1=this->cinInt(1000);
		std::cout<<"Podaj szanse na zmiane bitu w kanale Gilberta (zla seria)[promile]: ";
		this->prop2=this->cinInt(1000);

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

		std::cout<<"kanal bsc: \n";

		std::cout<<"\nDane zakodowane kodem bsh: \n";
		this->showValuesByte(this->dataBch);
		std::cout<<"\nDane zakodowane kodem rs: \n";
		this->showValuesByte(this->dataRs);
		std::cout<<"\nDane zakodowane kodem potrojeniowym: \n";
		this->showValuesByte(this->dataTripling);

		std::cout<<"\n\nkanal gilberta: \n";
		std::cout<<"\nDane zdekodowane kodem bsh: \n";
		this->showValuesByte(this->dataBchG);
		std::cout<<"\nDane zdekodowane kodem rs: \n";
		this->showValuesByte(this->dataRsG);
		std::cout<<"\nDane zdekodowane kodem potrojeniowym: \n";
		this->showValuesByte(this->dataTriplingG);
		
		std::cout<<"\n\n[Dekodowanie danych oraz odrzucanie nadmiarowych bitow..]\n\n";

		this->dataDecode();

		std::cout<<"kanal bsc: \n";
		std::cout<<"\nDane zdekodowane kodem bsh: \n";
		this->showValuesByte(this->dataBch);
		std::cout<<"\nDane zdekodowane kodem rs: \n";
		this->showValuesByte(this->dataRs);
		std::cout<<"\nDane zdekodowane kodem potrojeniowym: \n";
		this->showValuesByte(this->dataTripling);


		std::cout<<"\n\nkanal gilberta: \n";
		std::cout<<"\nDane zdekodowane kodem bsh: \n";
		this->showValuesByte(this->dataBchG);
		std::cout<<"\nDane zdekodowane kodem rs: \n";
		this->showValuesByte(this->dataRsG);
		std::cout<<"\nDane zdekodowane kodem potrojeniowym: \n";
		this->showValuesByte(this->dataTriplingG);
		std::cout<<"\n";
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
	dataRsG.insert(dataRsG.end(), dataRs.begin(), dataRs.end());
	dataBchG.insert(dataBchG.end(), dataBch.begin(), dataBch.end());
	dataTriplingG.insert(dataTriplingG.end(), dataTripling.begin(), dataTripling.end());

	Bsc::noise(dataRs,this->bscInPromils);
	Bsc::noise(dataBch,this->bscInPromils);
	Bsc::noise(dataTripling,this->bscInPromils);

	Gilbert::noiseG(dataRsG, this->prop1, this->prop2);
	Gilbert::noiseG(dataBchG, this->prop1, this->prop2);
	Gilbert::noiseG(dataTriplingG, this->prop1, this->prop2);
}

void Menu::dataEncode(){
	Tripling::encode(dataTripling);
	

	rs.encode(dataRs);
	bch.encode(dataBch);

}

void Menu::dataDecode(){

	int size = rs.nroots();
	rs.decode(dataRs);
	rs.decode(dataRsG);
	dataRs.resize(dataRs.size() - size);
	dataRsG.resize(dataRsG.size() - size);


	size = bch.ecc_bytes();
	bch.decode(dataBch);
	dataBch.resize(dataBch.size()- size);
	bch.decode(dataBchG);
	dataBchG.resize(dataBchG.size()- size);

	Tripling::decode(dataTripling);

	Tripling::decode(dataTriplingG);
}

void Menu::showValuesByte(std::vector<uint8_t> &data){

	for(unsigned int i=0; i<data.size(); i++){
		std::bitset<8> x(data.at(i));
		std::cout<<x<<" ";
	}
}

Menu::~Menu(){

}