#include "PlayerConnectedMessage.h"
PlayerConnectedMessage::PlayerConnectedMessage(const TransferSocketPtr& pTransferSocket):
Message(MessageTypes::PLAYER_CONNECTED), mTransferSocket(pTransferSocket){

	
}
