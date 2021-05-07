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
	std::string newMessage;
	
	while ( message != "DISCONNECT" ){
		
		
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
			recvMessage.shrink_to_fit();
			size_t msgDelimeter = recvMessage.find('\0');
			
			message += (msgDelimeter != std::string::npos) ? recvMessage.substr(0, msgDelimeter + 1) : recvMessage;
			recvMessage.erase(0, msgDelimeter + 1);
			newMessage = (recvMessage[0] != '\0')? recvMessage : "";
			
		} while (message[message.size() - 1] != 0);
		
		
		ParseMessage(message, pTransferSocket);

		message.clear();
		message = newMessage;
		newMessage.clear();
		
	}


}


void NetworkingSystem::CreateMessageInfo(std::string& pMessage){

	std::string info;
	info += "ML: ";
	//const int digitsInMsgLength = log10(pMessage.size());
	const int digitsInMsgLength = log10(pMessage.size() + log10(pMessage.size()));
	info += std::to_string(digitsInMsgLength);
	//auto size = (digitsInMsgLength < actualSize) ? actualSize + 1 : actualSize;
	info += '#';
	
	pMessage = info + pMessage;

	
}