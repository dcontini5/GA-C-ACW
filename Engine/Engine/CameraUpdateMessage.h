#pragma once
#include <vec2.hpp>


#include "Message.h"

class CameraUpdateMessage : public Message{

	//Structors
public:
	CameraUpdateMessage(const glm::vec2& pUpdateVector, const bool& pIsRotating, const int8_t& pZoom)
		:Message(MessageTypes::CAMERA_UPDATE), mUpdateVector(pUpdateVector), mIsRotating(pIsRotating), mZoom(pZoom) {}
	CameraUpdateMessage(const CameraUpdateMessage&);
	CameraUpdateMessage(CameraUpdateMessage&&); //exchange members here;
	~CameraUpdateMessage() = default;

	//Accessors
public:
	glm::vec2 GetUpdateVector() const { return mUpdateVector; }
	bool IsRotating() const { return mIsRotating; }
	int8_t GetZoomValue() const { return mZoom; }
	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	CameraUpdateMessage& operator=(const CameraUpdateMessage& pOther) = delete;

	CameraUpdateMessage& operator=(const CameraUpdateMessage&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	glm::vec2 mUpdateVector{0.f};
	bool mIsRotating{false};
	int8_t mZoom{0};
	
	
};
