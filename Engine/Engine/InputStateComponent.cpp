#include "InputStateComponent.h"

#include "InputStateMessage.h"


void InputStateComponent::OnMessage(std::shared_ptr<Message>& pMessage){

	const auto inpMsg = std::reinterpret_pointer_cast<InputStateMessage>(pMessage);

	const InputState inputState = inpMsg->GetInputState();

	Update(inputState);
	
}

void InputStateComponent::ResetStates(){

	mKeyStates.clear();
	
}
