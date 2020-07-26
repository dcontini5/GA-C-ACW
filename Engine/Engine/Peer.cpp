#include "Peer.h"

#include <ws2tcpip.h>

Peer::Peer() {

	mPeer.sin_family = AF_INET;
	mPeer.sin_port = htons(9171);
	mPeer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

}

Peer::Peer(const std::string& pIP){

	mPeer.sin_family = AF_INET;
	mPeer.sin_port = htons(9171);
	inet_pton(mPeer.sin_family, pIP.c_str(), &mPeer.sin_addr);
	
	
};