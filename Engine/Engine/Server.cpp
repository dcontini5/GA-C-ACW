#include "Server.h"
#include "ThreadManager.h"

Server::Server(): NetworkingSystem({}){}

void Server::Init() {

	mListenSocket.Init(2, 2);
	mListenSocket.Create();
	mListenSocket.Bind(mPeer);

}

void Server::Start(){

	ThreadManager::Instance()->AddThread(&Server::Listen, this);

}

void Server::Listen(){

	while(true){

		auto socket = mListenSocket.Listen();
		
		
		if (socket != SOCKET_ERROR) {
			TransferSocket transferSocket(socket);
			mClients.push_back(transferSocket);
			ThreadManager::Instance()->AddThread(&TransferSocket::Receive, transferSocket);
			ThreadManager::Instance()->AddThread(&TransferSocket::Send, transferSocket);
			
		}
	}
	
}

//void Server::Send(){
//
//	while( mClients.empty() ) std::this_thread::yield();
//	
//	while (true){
//
//		for(auto& client : mClients){
//
//			client.Send("Message");
//			
//		}
//		
//	}
//
//}

//void Server::Receive(TransferSocket& pClient){}


//void Server::Receive(){
//
//
//	while (mClients.empty()) std::this_thread::yield();
//
//	while(true){
//
//		for (auto& client : mClients){
//
//			std::string message;
//			client.Receive(message);
//			
//		}
//		
//	}
//
//	
//}




void Server::Echo(std::string& pMessage){

	//std::string message;

	//mTransferSocket.Receive(pMessage);
	//std::cout << pMessage;
	//mTransferSocket.Send(pMessage);

	
}
