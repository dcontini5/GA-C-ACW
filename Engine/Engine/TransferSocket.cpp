﻿#include "TransferSocket.h"

#include <vector>

#include "ResourceManager.h"
//void TransferSocket::Send(){}


void TransferSocket::Connect(const Peer& pPeer){

	if (connect(mSocket, reinterpret_cast<sockaddr*>(&pPeer.Get()), sizeof(pPeer)) == SOCKET_ERROR) {
		std::cerr << "Connect to peer failed with " << WSAGetLastError() << std::endl;
		return;
	}

	mConnected = true;
	mResetted = true;
}


