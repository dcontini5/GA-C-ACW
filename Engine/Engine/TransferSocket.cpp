#include "TransferSocket.h"

#include <vector>

#include "ResourceManager.h"
//void TransferSocket::Send(){}


void TransferSocket::Send(){

	const auto message = ResourceManager::Instance()->ParseData({ glm::vec3(0.f, 0.f, 0.f) });
	
	if (send(mSocket, message.c_str(), message.size(), 0) == SOCKET_ERROR) {
		
		std::cerr << "Send failed with " << WSAGetLastError() << std::endl;
		
	}

	
}

void TransferSocket::Connect(const Peer& pPeer) const{

	if (connect(mSocket, reinterpret_cast<sockaddr*>(&pPeer.Get()), sizeof(pPeer)) == SOCKET_ERROR) {
		std::cerr << "Connect to peer failed with " << WSAGetLastError() << std::endl;
	}
	
}

//void TransferSocket::Receive(std::string& pMessage){}

void TransferSocket::Receive(){

	const int maxSize = 4096;
	std::vector<char> buffer(maxSize);
	
	if (recv(mSocket, &buffer[0], maxSize, 0) == SOCKET_ERROR) {
		
		std::cerr << "Receive failed with " << WSAGetLastError() << std::endl;
		return;
		
	}
	
	std::string message;
	message.assign(buffer.cbegin(), buffer.cend());
	
	
}
