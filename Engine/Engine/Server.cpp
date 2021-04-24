#include "Server.h"

//#include <WS2tcpip.h>

#include "Game.h"
#include "ThreadManager.h"
#include "PlayerConnectedMessage.h"
#include "ClientPlayerComponent.h"	

Server::Server(): NetworkingSystem({}){}

void Server::Init() {

	mListenSocket.Init(2, 2);
	mListenSocket.Create();
	mListenSocket.Bind(mPeer);

}

void Server::Start(){

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
				//terminate threads ?
			
				continue;
			}
				
			client->SetSocket(newSocket);
			client->SetClientAddress(ipAdd);

			if (mClients.find(ipAdd) == mClients.end())	{
				
				mClients[ipAdd] = client;
				
				std::shared_ptr<Message> msg = std::make_shared<PlayerConnectedMessage>(client);
				
				Game::Instance()->BroadcastMessage(msg);
				
			}
					

			//const auto sendID = ThreadManager::Instance()->AddThreadWithArgs(&NetworkingSystem::Send, this, client);
			//client->SetSendThreadID(sendID);
			const auto receiveID = ThreadManager::Instance()->AddThreadWithArgs(&NetworkingSystem::Receive, this, client);
			client->SetReceiveThreadID(receiveID);
		}
		
	}

	
}


