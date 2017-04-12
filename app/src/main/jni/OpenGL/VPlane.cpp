
#include "VPlane.h"
namespace Vel
{

	VPlane::VPlane()
	{
	}

	VPlane::VPlane(const glm::vec3 & Normal, const glm::vec3 & Pos)
	{
		this->Normal = Normal;
		Position = Pos;
		D = -glm::dot<float, glm::highp, glm::tvec3> (Normal, Pos);
	}

	VPlane::~VPlane()
	{
	}

	VPlane VPlane::FromPoints(const glm::vec3 & V1, const glm::vec3 & V2, const glm::vec3 & V3)
	{
		VPlane temp;
		glm::vec3 e1 = V2 - V1;
		glm::vec3 e2 = V3 - V1;
		temp.Normal = glm::normalize(glm::cross(e1, e2));
		temp.D = -glm::dot<float, glm::highp, glm::tvec3>(temp.Normal, V1);
		return temp;
	}

	GLfloat VPlane::GetDistance(const glm::vec3 & P)
	{
		return glm::dot<float, glm::highp, glm::tvec3>(Normal, P) + D;
	}
}