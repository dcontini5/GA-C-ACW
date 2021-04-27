#include "Socket.h"

void Socket::Init(const int& pMinVersion, const int& pMaxVersion) {

	const WORD wVersionRequested = MAKEWORD(pMinVersion, pMaxVersion);

	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData)) {

		std::cerr << "Socket initialization failed" << std::endl;


	}

}

void Socket::Create() {

	
	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (mSocket == INVALID_SOCKET) {

		std::cerr << "Create socket failed with" << WSAGetLastError() << std::endl;

	}

}
