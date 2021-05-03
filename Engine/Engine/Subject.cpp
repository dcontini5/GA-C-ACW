#include "Subject.h"
#include "Message.h"
#include "Observer.h"

void Subject::Register(MessageType& pType, std::shared_ptr<Observer>& pObserver){

	ListenerMapIterator it = mListeners.find(pType);

	if(it == mListeners.end()){

		mListeners[pType] = std::vector<std::shared_ptr<Observer>>();
	
	}
	
	mListeners[pType].push_back(pObserver);

}

void Subject::Unregister(MessageType& pType, std::shared_ptr<Observer>& pObserver){

	ListenerMapIterator it = mListeners.find(pType);

	if(it != mListeners.end()){

		auto i = it->second.begin();
		for(const auto& observer : it->second){

			++i;
			
			if(observer == pObserver){

				it->second.erase(i);
				return;
			}
			
		}
		
	}
	
}

void Subject::OnMessage(std::shared_ptr<Message>& pMessage){

	auto it = mListeners.find(pMessage->GetType());

	if(it != mListeners.end()){

		for(const auto& observer : it->second){

			observer->OnMessage(pMessage);
			
		}
		
	}

	
}
