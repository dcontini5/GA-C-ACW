#include "ClientPlayerComponent.h"
ClientPlayerComponent::ClientPlayerComponent(GameObjectPtr& pParent, TransferSocketPtr& pSocket)
: GameObjectComponent(pParent, ComponentTypes::PLAYER_CLIENT), mTransferSocket(pSocket){}

ClientPlayerComponent::ClientPlayerComponent(GameObjectPtr& pParent)
: GameObjectComponent(pParent, ComponentTypes::PLAYER_CLIENT), mTransferSocket(nullptr){}
