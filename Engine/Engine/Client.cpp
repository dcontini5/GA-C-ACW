#include "Client.h"


#include "Game.h"
#include "ThreadManager.h"
#include "PlayerConnectedMessage.h"

void Client::Init(){

	mTransferSocket->Init(2, 2);
	mTransferSocket->Create();
	const Peer myPeer(ResourceManager::Instance()->GetClientAddress(), ResourceManager::Instance()->GetPort());
	mTransferSocket->Bind(myPeer);
	
}

void Client::Start(){

	while (Game::Instance()->GetQuitFlag()){

		mTransferSocket->Connect(mPeer);

		if (mTransferSocket->IsConnected()) {

			std::shared_ptr<Message> msg = std::make_shared<PlayerConnectedMessage>(mTransferSocket);

			Game::Instance()->BroadcastMessage(msg);

			const auto sendID = ThreadManager::Instance()->AddThreadWithArgs(&NetworkingSystem::Send, this, mTransferSocket);
			//mTransferSocket->SetSendThreadID(sendID);
			const auto receiveID = ThreadManager::Instance()->AddThreadWithArgs(&NetworkingSystem::Receive, this, mTransferSocket);
			//mTransferSocket->SetReceiveThreadID(receiveID);
			//ThreadManager::Instance()->TeminateThread(receiveID);
			while (true) { std::this_thread::sleep_for(std::chrono::duration<float>(10)); }
		}
		else {
							
			mTransferSocket->Disconnect();
			mTransferSocket->Create();
			std::this_thread::sleep_for(std::chrono::duration <double>(10.f));
			
		}
		
		
	}

	
}



