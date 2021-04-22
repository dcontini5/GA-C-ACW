#include "Server.h"

//#include <WS2tcpip.h>

#include "Game.h"
#include "ThreadManager.h"
#include "NewPlayerConnectedMessage.h"
#include "ClientPlayerComponent.h"	

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
		sockaddr_in address{};
		int addlen = sizeof(address);
					
		mListenSocket.Listen(newSocket, address, addlen);
				
		if (newSocket != SOCKET_ERROR) {

			std::string ipAdd;

			inet_ntop(AF_INET, &address.sin_addr, &ipAdd[0], sizeof(ipAdd));
			//auto component =  mClients[ipAdd]->GetComponent(ComponentTypes::PLAYER_CLIENT);

			TransferSocketPtr client;

				//if (component) client = std::dynamic_pointer_cast<ClientPlayerComponent>(component)->GetTransferSocket();
				//else client = std::make_shared<TransferSocket>();
			if(mClients.find(ipAdd) != mClients.end())	client = mClients[ipAdd];
			else	client = std::make_shared<TransferSocket>();
			
			if (client->IsConnected()) {

				// check if socket is closing it should
				closesocket(newSocket);
				//client->Disconnect();
				//terminate threads
				continue;
			}
				
			client->SetSocket(newSocket);
			client->SetClientAddress(ipAdd);

			mClients[ipAdd] = client;
			
			std::shared_ptr<Message> msg = std::make_shared<NewPlayerConnectedMessage>(client);
			
			Game::Instance()->OnMessage(msg);

			
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

	/*
	 * 

void Server::Echo(std::string& pMessage){

	//std::string message;

	//mTransferSocket.Receive(pMessage);
	//std::cout << pMessage;
	//mTransferSocket.Send(pMessage);

	
}
	 */