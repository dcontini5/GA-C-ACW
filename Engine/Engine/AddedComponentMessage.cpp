#include "AddedComponentMessage.h"
#include "System.h"

AddedComponentMessage::AddedComponentMessage(ComponentType& pComponent, std::shared_ptr<GameObject>& pSender): Message(MessageTypes::ADDED_COMPONENT, pSender), mComponentType(pComponent){}
