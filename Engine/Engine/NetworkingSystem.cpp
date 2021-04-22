#include "NetworkingSystem.h"

#include "ThreadManager.h"




void NetworkingSystem::Send() {

	//const auto message = ParseData({ glm::vec3(0.f, 0.f, 0.f) });
	std::string message;

	CreateMessage(message);
	
	if (send(mTransferSocket.GetSocket(), message.c_str(), message.size(), 0) == SOCKET_ERROR) {

		std::cerr << "Send failed with " << WSAGetLastError() << std::endl;

	}

}

//void TransferSocket::Receive(std::string& pMessage){}

void NetworkingSystem::Receive() {

	const int maxSize = 4096;
	std::vector<char> buffer(maxSize);

	
	if (recv(mTransferSocket.GetSocket(), &buffer[0], maxSize, 0) == SOCKET_ERROR) {

		std::cerr << "Receive failed with " << WSAGetLastError() << std::endl;
		return;

	}

	std::string message;
	message.assign(buffer.cbegin(), buffer.cend());

	ParseMessage(message);

}

void NetworkingSystem::Start() {


}
