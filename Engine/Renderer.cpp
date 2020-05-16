#include "Renderer.h"

//void Renderer::Draw(RenderComponent* pRC, glm::mat4 pMVM){
//
//	if (rc->ShouldDraw())
//	{
//		MVM = glm::translate(MVM, glm::vec3(rc->GetPosition().x(), rc->GetPosition().y(), 0));
//		MVM = glm::rotate(MVM, -rc->GetAngle(), glm::vec3(0, 0, 1)); // Rotates anti-clockwise
//		MVM = glm::scale(MVM, glm::vec3(rc->GetScale(), rc->GetScale(), 1));
//
//		if (rc->GetMesh())
//		{
//			Draw(rc->GetMesh(), MVM, rc->GetColour());
//		}
//	}
//	
//}
