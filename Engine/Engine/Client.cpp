#include "Client.h"

#include <chrono>

void Client::Init(){

	mTransferSocket.Init(2, 0);
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

	auto start = std::chrono::high_resolution_clock::now();
	const auto size = sizeof(char) * 5;

	auto totsize = 0;
	
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	Echo("Echo");
	totsize += size;
	mTransferSocket.Send("");

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = end - start;

	std::cout << size / elapsed.count() << std::endl;
	
	std::cout << "Finished..." << std::endl;
}

void Client::Echo(const std::string& pMessage){

	mTransferSocket.Send(pMessage);
	std::string message;
	mTransferSocket.Receive(message);

	std::cout << message;
		
}
