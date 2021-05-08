#include "NetworkingSystem.h"



#include "CurrentSystemFrequencyMessage.h"
#include "Game.h"
#include "ThreadManager.h"


void NetworkingSystem::Send(const TransferSocketPtr& pTransferSocket) {
		
	while (pTransferSocket->IsConnected()){

		std::chrono::duration<double> lag = std::chrono::high_resolution_clock::now() - pTransferSocket->GetLastSendTime();

		while (lag < mTimeStep) {
			lag = std::chrono::high_resolution_clock::now() - pTransferSocket->GetLastSendTime();
		}

		//avgFps code taken from https://stackoverflow.com/questions/4687430/c-calculating-moving-fps
		
		const auto alpha = 0.8f;
		pTransferSocket->SetAverageSend(alpha * pTransferSocket->GetAverageSend() + (1.f - alpha) * 1 / lag.count());

		//std::shared_ptr<Message> msg = std::make_shared<CurrentSystemFrequencyMessage>(SystemTypes::NETWORKING, avgFps);
		//Game::Instance()->BroadcastMessage(msg);

		pTransferSocket->SetLastSendTime( std::chrono::high_resolution_clock::now());

		
		std::string message;

		CreateMessage(message, pTransferSocket);
		
		message += '\0';

		
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


		//std::chrono::duration<double> lag = std::chrono::high_resolution_clock::now() - mLastTimeReceive;
		//
		//while (lag < mTimeStep) {
		//	lag = std::chrono::high_resolution_clock::now() - mLastTimeReceive;
		//}
		//
		////avgFps code taken from https://stackoverflow.com/questions/4687430/c-calculating-moving-fps
		//static auto avgFps = 1.f;
		//const auto alpha = 0.8f;
		//avgFps = alpha * avgFps + (1.f - alpha) * 1 / lag.count();
		////
		//
		//std::shared_ptr<Message> msg = std::make_shared<CurrentSystemFrequencyMessage>(SystemTypes::NETWORKING, avgFps);
		//Game::Instance()->BroadcastMessage(msg);
		//
		//mLastTimeReceive = std::chrono::high_resolution_clock::now();
		
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
			const size_t msgDelimiter = recvMessage.find('\0');
			
			message += (msgDelimiter != std::string::npos) ? recvMessage.substr(0, msgDelimiter + 1) : recvMessage;
			recvMessage.erase(0, msgDelimiter + 1);
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