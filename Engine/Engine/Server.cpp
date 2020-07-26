#include "Server.h"
#include "ThreadManager.h"

void Server::Init() {

	mListenSocket.Init(2, 2);
	mListenSocket.Create();
	mListenSocket.Bind(mPeer);

}

void Server::Start(){

	ThreadManager::Instance()->AddThread(&Server::Listen, this);
	ThreadManager::Instance()->AddThread(&Server::Send, this);

}

void Server::Listen(){

	while(true){

		auto transferSocket = mListenSocket.Listen();
		if (transferSocket != SOCKET_ERROR) {
			mClients.emplace_back(transferSocket);
			ThreadManager::AddThread(&receive, std::ref(transferSocket));
		}
	}
	
}

void Server::Send(){

	while( mClients.empty() ) std::this_thread::yield();
	
	while (true){

		for(auto& client : mClients){

			client.Send("Message");
			
		}
		
	}

}


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

	mTransferSocket.Receive(pMessage);
	std::cout << pMessage;
	mTransferSocket.Send(pMessage);

	
}
