#include "Client.h"

#include "ThreadManager.h"

void Client::Init(){

	mTransferSocket.Init(2, 2);
	mTransferSocket.Create();
	mTransferSocket.Connect(mPeer);
	
}


void Client::Start() {

	mReceiveThreadID =  ThreadManager::Instance()->AddThread(&TransferSocket::Receive, mTransferSocket);
	mSendThreadID =  ThreadManager::Instance()->AddThread(&TransferSocket::Send, mTransferSocket);

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
