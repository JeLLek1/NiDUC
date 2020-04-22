#include "src/menu.cpp"
int main()
{
	try{

	   	Menu *menu = new Menu(); 

	   	menu->display();

	   	delete menu;
   }catch(std::exception e){
		std::cout<<e.what();
	}
}
