#include "NewPlayerConnectedMessage.h"
NewPlayerConnectedMessage::NewPlayerConnectedMessage(const TransferSocket& pTransferSocket): Message(MessageTypes::PLAYER_CONNECTED), mTransferSocket(std::make_shared<TransferSocket>(pTransferSocket)){

	
}
