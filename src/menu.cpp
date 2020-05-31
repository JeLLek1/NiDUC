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
	std::cout<<"Uswawienia: \nMaksymalna ilość symboli: "<<CODE_N<<"\nDługosc slowa kodowego: "<<CODE_K<<"\nmozliwosc korekcyjna BSC: "<<CODE_T<<"\n";
	
		std::cout<<"Podaj ilość danych do przetestowania: ";

		this->symbols=this->cinInt(CODE_K);

		std::cout<<"Podaj szanse na zmiane bitu w kanale BSC [promile]: ";
		this->bscInPromils=this->cinInt(1000);
		std::cout<<"Podaj szanse na zmiane bitu w kanale Gilberta (dobra seria)[promile]: ";
		this->prop1=this->cinInt(1000);
		std::cout<<"Podaj szanse na zmiane bitu w kanale Gilberta (zla seria)[promile]: ";
		this->prop2=this->cinInt(1000);

		this->loadValues();

		this->dataEncode();
		std::cout<<"\n";
		this->showValuesByte(this->data);
		std::cout<<"\n";
		this->showValuesByte(this->dataTripling);
		std::cout<<"\n";
		this->channel();
		this->showValuesByte(this->dataTripling);
		std::cout<<"\n";

		this->dataDecode();
		this->showValuesByte(this->dataTripling);
		std::cout<<"\n";

		this->checkBer();
}

long Menu::errorCount(std::vector<uint8_t> dataTest){
	long counter = 0;

	for(size_t i = 0; i<dataTest.size(); i++){
		uint8_t test = dataTest[i]^this->data[i];
		while(test>0){
			if(test%2==1){
				counter++;
			}
			test>>=1;
		}
	}

	return counter;
}

userBer Menu::checkBer(){
	size_t dataLength = this->data.size()*8;
	userBer ber;
	ber.rsBsc = static_cast<double>(this->errorCount(this->dataRs))/dataLength;
	ber.bchBsc = static_cast<double>(this->errorCount(this->dataBch))/dataLength;
	ber.tripleBsc = static_cast<double>(this->errorCount(this->dataTripling))/dataLength;
	ber.rsGil = static_cast<double>(this->errorCount(this->dataRsG))/dataLength;
	ber.bchGil = static_cast<double>(this->errorCount(this->dataBchG))/dataLength;
	ber.tripleGil = static_cast<double>(this->errorCount(this->dataTriplingG))/dataLength;

	std::cout<<"\nBer: "<<ber.tripleBsc<<" "<<this->errorCount(this->dataTripling)<<"\n";

	return ber;
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

void Menu::channel(){
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

	//Tripling::decode(dataTriplingG);
}

void Menu::showValuesByte(std::vector<uint8_t> &data){

	for(unsigned int i=0; i<data.size(); i++){
		std::bitset<8> x(data.at(i));
		std::cout<<x<<" ";
	}
}
void Menu::tests(size_t number,int prop1,int prop2)
{
	userBer ber;
	ber.rsBsc=0;
	ber.bchBsc=0; 
	ber.tripleBsc=0;
	ber.rsGil=0; 
	ber.bchGil=0; 
	ber.tripleGil=0;
	for(unsigned int i=0;i<number;i++)
	{
		

		this->symbols=this->cinInt(CODE_K);

		this->bscInPromils=this->cinInt(prop1);

		this->prop1=this->cinInt(prop1);

		this->prop2=this->cinInt(prop2);

		this->loadValues();

		this->dataEncode();

		this->channel();

		this->dataDecode();
		userBer temp=this->checkBer();
		ber.rsBsc+=temp.rsBsc;
		ber.bchBsc+=temp.bchBsc; 
		ber.tripleBsc+=temp.tripleBsc;
		ber.rsGil+=temp.rsGil; 
		ber.bchGil+=temp.bchGil; 
		ber.tripleGil+=temp.tripleGil;
		this->clearVector();
	}
	ber.rsBsc=ber.rsBsc/number;
	ber.bchBsc=ber.bchBsc/number; 
	ber.tripleBsc=ber.tripleBsc;
	ber.rsGil=ber.rsGil/number; 
	ber.bchGil=ber.bchGil/number; 
	ber.tripleGil=ber.tripleGil/number;
}
void Menu::clearVector()
{
	this->data.clear();
	this->dataRs.clear();
	this->dataBch.clear();
	this->dataTripling.clear();
	this->dataRsG.clear();
	this->dataBchG.clear();
	this->dataTriplingG.clear();
}

Menu::~Menu(){

}