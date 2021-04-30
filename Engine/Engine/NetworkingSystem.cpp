#include "NetworkingSystem.h"

#include "ThreadManager.h"


void NetworkingSystem::Send(const TransferSocketPtr& pTransferSocket) {
		
	while (pTransferSocket->IsConnected()){
		
		std::string message;

		CreateMessage(message, pTransferSocket);

		message += '\0';

		//std::cout << message << "\n";
		
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

		//todo: send data size with the first packet
		//https://stackoverflow.com/questions/55178026/reading-more-than-one-message-from-recv
		do{
			const auto maxSize = 65535;
			std::vector<char> buffer(maxSize);
			std::string recvMessage;

			if (recv(pTransferSocket->GetSocket(), &buffer[0], maxSize, 0) == SOCKET_ERROR) {

				std::cerr << "Receive failed with " << WSAGetLastError() << std::endl;
				pTransferSocket->Disconnect();
				ThreadManager::Instance()->DetachThread(pTransferSocket->GetReceiveThreadID());
				return;

			}
			
			recvMessage.assign(buffer.cbegin(), buffer.cend());
			//message.assign(buffer.cbegin(), buffer.cend());

			message += recvMessage;
			
		} while (message[message.size() - 1] != 0);
		
		
		ParseMessage(message, pTransferSocket);

		message.clear();
		
	}


}




