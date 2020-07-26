#include "Socket.h"

void Socket::Init(const int& pMinVersion, const int& pMaxVersion) {

	const WORD wVersionRequested = MAKEWORD(pMinVersion, pMaxVersion);

	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData)) {

		std::cerr << "Soket initialization failed" << std::endl;


	}

}

void Socket::Create() {

	mSocket = socket(AF_INET, SOCK_STREAM, 6);

	if (mSocket == INVALID_SOCKET) {

		std::cerr << "Create socket failed with" << WSAGetLastError() << std::endl;

	}

}
