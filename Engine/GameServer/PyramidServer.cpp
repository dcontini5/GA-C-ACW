#include "PyramidServer.h"
#include "ThreadManager.h"
#include "gtx/string_cast.hpp"

PyramidServer::PyramidServer():Server(){}

void PyramidServer::CreateMessage(std::string& pMessage){

	for(const auto& obj : mGameObjects){

		std::shared_lock<std::shared_mutex> lk(ThreadManager::Instance()->GetSharedMutex());

		const auto pos = glm::to_string(obj->GetPos());
		const auto scale = glm::to_string(obj->GetScale());
		
		pMessage += "P: ";
		pMessage += pos;
		pMessage += " S: ";
		pMessage += scale;
		pMessage += " - ";
		
		
	}

	
}

void PyramidServer::ParseMessage(std::string& pMessage){

	std::cout << pMessage << std::endl;

	
}
