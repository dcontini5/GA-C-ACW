#include "CameraComponent.h"
#include "CameraUpdateMessage.h"
#include "GameObject.h"


void CameraComponent::OnMessage(std::shared_ptr<Message>& pMessage){

	const std::shared_ptr<CameraUpdateMessage> cuMsg = std::reinterpret_pointer_cast<CameraUpdateMessage>(pMessage);

	if(cuMsg->GetZoomValue() != 0){

		const glm::vec3 newPos = mParent->GetPos() + mForward * static_cast<float>(cuMsg->GetZoomValue());
		mParent->SetPos(newPos);
		return;
		
	}
	
	if(cuMsg->IsRotating()){

		//rotate
		glm::vec3 newRot( mParent->GetRot() );
		newRot.x -=	cuMsg->GetUpdateVector().x * mCameraSpeed;
		newRot.y += cuMsg->GetUpdateVector().y * mCameraSpeed;
		mParent->setRot(newRot);
		
	}else{

		const glm::vec3 dir(cuMsg->GetUpdateVector(), 0.f);
		const glm::vec3 newPos = mParent->GetPos() + (mUp - mLeft) * dir * mCameraSpeed;
		mParent->SetPos(newPos);
		
	}


	
}
