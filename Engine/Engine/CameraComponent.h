#pragma once
#include <vec3.hpp>

#include "GameObjectComponent.h"

class CameraComponent : public GameObjectComponent {

	//Structors
public:
	CameraComponent(GameObjectPtr& pParent): GameObjectComponent(pParent, ComponentTypes::CAMERA) {}
	CameraComponent(const CameraComponent&);
	CameraComponent(CameraComponent&&); //exchange members here;
	~CameraComponent() = default;

	//Accessors
public:
	glm::vec3 GetForward() const { return mForward; }
	glm::vec3 GetUp() const { return mUp; }
	glm::vec3 GetLeft() const { return mLeft; }
	float GetCameraSpeed() const { return mCameraSpeed; }
	
	//Mutators
public:

	void SetForward(const glm::vec3& pForward) { mForward = pForward; }
	void SetUp(const glm::vec3& pUp) { mUp = pUp; }
	void SetLeft(const glm::vec3& pLeft) { mLeft = pLeft; }
	void SetCameraSpeed(const float& pCameraSpeed) { mCameraSpeed = pCameraSpeed; }
	
	// Public Functions
public:
	void OnMessage(std::shared_ptr<Message>& pMessage) override{}
	// Private Functions 
private:

	//Operators
public:
	CameraComponent& operator=(const CameraComponent& pOther) = delete;
	CameraComponent& operator=(const CameraComponent&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
protected:

	glm::vec3 mForward{ 0.f, 0.f, 1.f };
	glm::vec3 mUp{ 0.f, 1.f, 0.f };
	glm::vec3 mLeft{ 1.f, 0.f, 0.f };
	float mCameraSpeed{ 0.01f };
	
};
