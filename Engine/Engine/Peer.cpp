#include "Peer.h"



Peer::Peer() {

	mPeer.sin_family = AF_INET;
	mPeer.sin_port = htons(9171);
	mPeer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	
}

Peer::Peer(const std::string& pIP, const int& pPort){

	mPeer.sin_family = AF_INET;
	mPeer.sin_port = htons(pPort);
	inet_pton(mPeer.sin_family, pIP.c_str(), &mPeer.sin_addr);
	
	
}

Peer::Peer(const Peer& pOther) : mPeer(pOther.mPeer){}
Peer::Peer(Peer&& pOther) noexcept : mPeer(std::move(pOther.mPeer)) {}
