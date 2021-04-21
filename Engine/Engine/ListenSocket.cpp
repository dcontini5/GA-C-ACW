#include "ListenSocket.h"



void ListenSocket::Bind(const Peer& pPeer){
	
	if (bind(mSocket, reinterpret_cast<sockaddr*>(&pPeer.Get()), sizeof(pPeer)) == SOCKET_ERROR) {

		std::cerr << "Bind failed with " << WSAGetLastError() << std::endl;

	}

}

SOCKET ListenSocket::Listen(){

	if(listen(mSocket, 5) == SOCKET_ERROR){
		
		std::cerr << "Listen failed with " << WSAGetLastError() << std::endl;
		return 0;
		
	}

	std::cout << "Waiting..." << std::endl;

	return accept(mSocket, nullptr, nullptr);
	
}

void ListenSocket::Listen(SOCKET& pSocket, sockaddr_in& pAddress, int& pAddressSize){

	if(listen(mSocket, 5) == SOCKET_ERROR){
		
		std::cerr << "Listen failed with " << WSAGetLastError() << std::endl;
		return;
		
	}

	std::cout << "Waiting..." << std::endl;

	pSocket = accept(mSocket, reinterpret_cast<sockaddr*>(&pAddress), &pAddressSize);
	
}


