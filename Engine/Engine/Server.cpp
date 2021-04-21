#include "Server.h"

#include <ws2tcpip.h>

#include "Game.h"
#include "ThreadManager.h"
#include "NewPlayerConnectedMessage.h"
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

	while(Game::Instance()->GetQuitFlag()){
		
		SOCKET newSocket;
		sockaddr_in address;
		int addlen = sizeof(address);
					
		mListenSocket.Listen(newSocket, address, addlen);
				
		if (newSocket != SOCKET_ERROR) {

			
			//TransferSocket newClientSocket(newSocket, address, addlen);
			std::string ipAdd;
			inet_ntop(AF_INET, &address.sin_addr, &ipAdd[0], sizeof(ipAdd));

			auto client = mClients[ipAdd];
			
			if (client.IsConnected()){

				//close socket;
				continue;
			}
				
			client.SetSocket(newSocket);

			std::shared_ptr<Message> msg = std::make_shared<NewPlayerConnectedMessage>();
			
			Game::Instance()->OnMessage(msg);
			
			//new connection message
			//send message to scene
			
			//create client
			//ThreadManager::Instance()->AddThreadWithArgs(&Server::Receive, this, newSocket);
			//ThreadManager::Instance()->AddThreadWithArgs(&Server::Send, this, newClient);
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
