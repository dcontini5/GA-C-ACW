#include "RemovedComponentMessage.h"
RemovedComponentMessage::RemovedComponentMessage(ComponentType& pComponent, std::shared_ptr<GameObject>& pSender) : Message(MessageTypes::REMOVED_COMPONENT, pSender), mComponentType(pComponent) {}
