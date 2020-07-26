#include "TransferSocket.h"

#include <vector>

void TransferSocket::Send(){



	
}


void TransferSocket::Send(const std::string pMessage){


	if (send(mSocket, pMessage.c_str(), pMessage.size(), 0) == SOCKET_ERROR) {
		
		std::cerr << "Send failed with " << WSAGetLastError() << std::endl;
		
	}

	
}

void TransferSocket::Connect(const Peer& pPeer) const{

	if (connect(mSocket, reinterpret_cast<sockaddr*>(&pPeer.Get()), sizeof(pPeer)) == SOCKET_ERROR) {
		std::cerr << "Connect to peer failed with " << WSAGetLastError() << std::endl;
	}
	
}

void TransferSocket::Receive(std::string& pMessage){

	const int maxSize = 4096;
	std::vector<char> buffer(maxSize);
	
	if (recv(mSocket, &buffer[0], maxSize, 0) == SOCKET_ERROR) {
		
		std::cerr << "Receive failed with " << WSAGetLastError() << std::endl;
		return;
		
	}
	pMessage.assign(buffer.cbegin(), buffer.cend());
	//pMessage.append(buffer.cbegin(), buffer.cend());
	
}
