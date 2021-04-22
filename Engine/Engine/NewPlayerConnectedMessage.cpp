#include "NewPlayerConnectedMessage.h"
NewPlayerConnectedMessage::NewPlayerConnectedMessage(const TransferSocketPtr& pTransferSocket):
Message(MessageTypes::PLAYER_CONNECTED), mTransferSocket(pTransferSocket){

	
}
