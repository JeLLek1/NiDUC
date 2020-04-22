#include "menu.h"
#include <ezpwd/rs>
#include <ezpwd/bch>
#include <ctime>
#include <cmath>
#include <bitset>


#include "tripling.cpp"
#include "bsc.cpp"

Menu::Menu(){
	this->parity = 0;
	this->symbols = 0;

}

int Menu::cinInt(){
	int value;
	std::cin>>value;
	while(std::cin.good()==false){
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout<<"Podaj wartosc calkowita: ";
		std::cin >> value;
	}
	return value;
}

void Menu::display(){
	std::cout<<"Podaj ilość danych do przetestowania: ";

	this->symbols=this->cinInt();

	std::cout<<"Podaj ilość symbolów parzystości dla kodu rs: ";

	this->parity=this->cinInt();

	this->loadValues();

	this->dataEncode();

	std::cout<<"Dane wprowadzone i zakodowane: \n";

	this->showValuesByte();

	this->chanel();

	this->showValuesByte();

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
	Bsc::noise(this->data,1000);
}

void Menu::dataEncode(){
	Tripling::encode(dataTripling);
}

void Menu::showValuesByte(){
	std::cout<<"\nDane losowe przed zakodowaniem: \n";
	for(unsigned int i=0; i<data.size(); i++){
		std::bitset<8> x(data.at(i));
		std::cout<<x<<" ";
	}
	std::cout<<"\nDane zakodowane rs: \n";
	for(unsigned int i=0; i<data.size(); i++){
		std::bitset<8> x(data.at(i));
		std::cout<<x<<" ";
	}
	std::cout<<"\nDane zakodowane bch: \n";
	for(unsigned int i=0; i<data.size(); i++){
		std::bitset<8> x(data.at(i));
		std::cout<<x<<" ";
	}
	std::cout<<"\nDane zakodowane kodem potrojeniowym: \n";
	for(unsigned int i=0; i<data.size(); i++){
		std::bitset<8> x(data.at(i));
		std::cout<<x<<" ";
	}
	std::cout<<"\n";
}

Menu::~Menu(){

}