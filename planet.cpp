#include "planet.h"

Planet::Planet(vec3 a_center, float a_radius, glm::vec4 a_color)
{
	position = a_center;
	radius = a_radius;
	color = a_color;
}

void Planet::SetScale()
{

}

void Planet::SetRotation(vec3 v)
{
	v_orbit = v;
}

void Planet::SetTranslate(vec3 a_v)
{
	translate = a_v;
}

void Planet:: Update(float ct)
{
	//localTrans = glm::rotate(ct, vec3(0, 1, 0)) /** glm::translate(translate)*/;
	//orbit = glm::rotate(ct, vec3(0, 1, 0));

	orbit = glm::rotate(ct, vec3(0,1,0)) * glm::translate(v_orbit);
	if (parent != NULL)
	{
		orbit = parent->orbit * orbit;
	}
	localTrans *= glm::rotate(10.0f, vec3(0, 1, 0)); 

	// rotate around parent
	// translate to rotate around that place
	//if (parent != NULL)
	//{
	//	localTrans *= glm::translate(parent->translate) /** glm::translate(translate)*/;
	//	orbit =  glm::rotate(ct, vec3(0, 1, 0)) * glm::translate(parent->translate);
	//}
	
	
}

void Planet::Draw()
{
	Gizmos::addSphere(position, radius, 20, 20, color, &(orbit*localTrans));
}

void Planet::SetParent(Planet *p)
{
	parent = p;
}