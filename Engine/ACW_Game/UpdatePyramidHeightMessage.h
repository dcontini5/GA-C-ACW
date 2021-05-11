#pragma once
#include <cstdint>
#include "Message.h"
#include "PyramidClientMessageTypes.h"

class UpdatePyramidHeightMessage : public Message{

	//Structors
public:
	UpdatePyramidHeightMessage(const uint8_t& pHeight) : Message(PyramidClientMessageTypes::UPDATE_PYRAMID_HEIGHT), mHeight(pHeight){}
	UpdatePyramidHeightMessage(const UpdatePyramidHeightMessage&);
	UpdatePyramidHeightMessage(UpdatePyramidHeightMessage&&); //exchange members here;
	~UpdatePyramidHeightMessage() = default;

	//Accessors
public:
	uint8_t GetHeight() const { return mHeight; }
	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	UpdatePyramidHeightMessage& operator=(const UpdatePyramidHeightMessage& pOther) = delete;
	UpdatePyramidHeightMessage& operator=(const UpdatePyramidHeightMessage&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	uint8_t mHeight;
	
};
