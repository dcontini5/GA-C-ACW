#include "Client.h"

void Client::Init(){

	mTransferSocket.Init(2, 2);
	mTransferSocket.Create();
	mTransferSocket.Connect(mPeer);
	
}


void Client::Start(){

	//mTransferSocket.Send("awpwpowipdaowidp[awoid[pawoid[paok[aespofi[eofies[poaifpeofisepaoiwudapowidupawoidupoiufposaiefjseoifjaiefjpasoifjpsofijaspeoifjapsoiefjp\toaisjpfoaeijfapseoijpoeifjpoaiejfpoiajsfoijspofaiejfpoiesjpfaoisejfpaosiejf\tpoisjfopiejfapefoijasiefjpaoseijfpaoiejfpoeijfpaosiejfpoiesjfpaosiejfpaoisejfpasoiefjposiefjpoaseifjpaseoifjpoaisejfpoiasjefpoisejfpoiesjfapoisefjpaoesifjpoiasejfpoiajsepofijspaoifjepfoiasjfpoiajespfoisjeafpoiejfpaoiejfpioajfpaoisejpoiajf\tpsoeijfpoiaejpfoijaespfiojespfoiajspfeifjsepoifjapsefijpseofijaepsfijeofiepofidspfoidfpoispeofi1");
	//std::string message;
	//mTransferSocket.Receive(message);
	//std::cout << message << std::endl;
	//mTransferSocket.Send("*");
	//mTransferSocket.Receive(message);
	//std::cout << message << std::endl;


	auto totsize = 0;
	
	Echo("Echo");

	mTransferSocket.Send("");

	
	std::cout << "Finished..." << std::endl;
}

void Client::Echo(const std::string& pMessage){

	mTransferSocket.Send(pMessage);
	std::string message;
	mTransferSocket.Receive(message);

	std::cout << message;
		
}
