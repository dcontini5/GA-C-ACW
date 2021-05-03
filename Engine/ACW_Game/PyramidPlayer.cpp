﻿#include "PyramidPlayer.h"

#include "InputKeys.h"
#include "InputStateMessage.h"

void Player::OnMessage(std::shared_ptr<Message>& pMessage) {

	auto inpMsg = std::reinterpret_pointer_cast<InputStateMessage>(pMessage);

	const InputState inputState = inpMsg->GetInputState();

	switch (inputState.key) {

	case R:
	{
		//reset scene


	}
	case T:
	{

		//increase Pyramid Size						

	}
	case G:
	{
		//decrease Pyramid Size
	}
	case U:
	{
		//increase Graphics Frequency
	}
	case J:
	{
		//decrease Graphics Frequency
	}
	case Y:
	{
		//increase network frequency
	}
	case H:
	{
		//decrease network frequency
	}
	case NUM1:
	{
		//fire small proj
	}
	case NUM2:
	{
		//fire big proj
	}
	case NUM3:
	{
		//fire grenade
	}
	case LEFT:
	{
		//move playback backward
	}
	case RIGHT:
	{
		//move playback forward
	}
	case UP:
	{
		//pause playback
	}
	case DOWN:
	{
		//unpause playback
	}

	default:;
	}



}
