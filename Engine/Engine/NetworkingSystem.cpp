#include "NetworkingSystem.h"

#include "ThreadManager.h"




void NetworkingSystem::Send(const TransferSocketPtr& pTransferSocket) {

	while (pTransferSocket->IsConnected()){
		
		std::string message;

		CreateMessage(message);

		if (send(pTransferSocket->GetSocket(), message.c_str(), message.size(), 0) == SOCKET_ERROR) {

			std::cerr << "Send failed with " << WSAGetLastError() << std::endl;
			pTransferSocket->Disconnect();
			ThreadManager::Instance()->DetachThread(pTransferSocket->GetReceiveThreadID());
			return;
			
		}
	}

}


void NetworkingSystem::Receive(const TransferSocketPtr& pTransferSocket) {

	std::string message;
	
	while ( message != "DISCONNECT" ){
		
		const auto maxSize = 4096;
		std::vector<char> buffer(maxSize);


		if (recv(pTransferSocket->GetSocket(), &buffer[0], maxSize, 0) == SOCKET_ERROR) {

			std::cerr << "Receive failed with " << WSAGetLastError() << std::endl;
			pTransferSocket->Disconnect();
			ThreadManager::Instance()->DetachThread(pTransferSocket->GetReceiveThreadID());
			return;

		}

		std::cout << "Received\n";
		
		message.assign(buffer.cbegin(), buffer.cend());

		ParseMessage(message);
		
	}


}




