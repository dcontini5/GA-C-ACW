#include "PyramidCameraComponent.h"

#include "CameraUpdateMessage.h"
#include "GameObject.h"
#include "ThreadManager.h"

void PyramidCameraComponent::OnMessage(std::shared_ptr<Message>& pMessage) {

	const std::shared_ptr<CameraUpdateMessage> cuMsg = std::reinterpret_pointer_cast<CameraUpdateMessage>(pMessage);

	if (cuMsg->GetZoomValue() != 0) {

		{
			std::unique_lock<std::shared_mutex> lk(ThreadManager::Instance()->GetSharedMutex());
			const glm::vec3 newPos = mParent->GetPos() + (mForward + mParent->GetRot()) * static_cast<float>(cuMsg->GetZoomValue());
			mParent->SetPos(newPos);
		}

		return;

	}

	if (cuMsg->IsRotating()) {
		{
			std::unique_lock<std::shared_mutex> lk(ThreadManager::Instance()->GetSharedMutex());
			glm::vec3 newRot(mParent->GetRot());
			newRot.x -= cuMsg->GetUpdateVector().x * mCameraSpeed;
			newRot.y += cuMsg->GetUpdateVector().y * mCameraSpeed;
			mParent->setRot(newRot);
		}

	}
	else {
		{
			std::unique_lock<std::shared_mutex> lk(ThreadManager::Instance()->GetSharedMutex());
			glm::vec3 dir(cuMsg->GetUpdateVector(), 0.f);
			const glm::vec3 newPos = mParent->GetPos() + dir * mCameraSpeed;
			mParent->SetPos(newPos);
		}

	}

}
