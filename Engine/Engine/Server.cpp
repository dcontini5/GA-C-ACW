#include "Server.h"
void Server::Init() {

	mListenSocket.Init(2, 0);
	mListenSocket.Create();
	mListenSocket.Bind(mPeer);

}

void Server::Start(){

	auto transfSocket = mListenSocket.Listen();
	mTransferSocket.SetSocket(transfSocket);
	std::string message = "";
	
	//while (!message.empty()){
	//
	//	message.clear();
	//	mTransferSocket.Receive(message);
	//	std::cout << message << std::endl;
	//	mTransferSocket.Send("Hi");
	//
	//} 
	do{
		
		Echo(message);
		
	} while (!message.empty());
	
	
	std::cout << "Finished..." << std::endl;
	
}

void Server::Echo(std::string& pMessage){

	//std::string message;

	mTransferSocket.Receive(pMessage);
	std::cout << pMessage;
	mTransferSocket.Send(pMessage);

	
}
