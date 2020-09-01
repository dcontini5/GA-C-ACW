#include "Client.h"

#include "ThreadManager.h"

void Client::Init(){

	mTransferSocket.Init(2, 2);
	mTransferSocket.Create();
	
}

void Client::Connect(){


	mTransferSocket.Connect(mPeer);

	
}



//void Client::Echo(const std::string& pMessage){
//
//	mTransferSocket.Send(pMessage);
//	std::string message;
//	mTransferSocket.Receive();
//	//mTransferSocket.Receive(message);
//
//	std::cout << message;
//		
//}
