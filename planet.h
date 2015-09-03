#ifndef _PLANET_H_
#define _PLANET_H_

#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <aie\Gizmos.h>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::vec2;

class Planet
{
	// local transform
	mat4 orbit = mat4(1);
	mat4 localTrans = mat4(1);

	// planet data
	vec3 position{ 0,0,0 };
	float radius;
	vec4 color{ 0,0,0,0 };
	
	vec3 v_orbit{ 0,0,0 };
	vec3 translate{ 0,0,0 };
	vec3 scale{ 0,0,0 };

	Planet *parent = NULL; // glm::translate(parent.position) * transform;

public:

	Planet() {};
	Planet(vec3 center, float radius, glm::vec4 color);

	void SetPosition();
	void SetRotation(vec3 v);
	void SetScale();
	void SetTranslate(vec3 a_v);
	void SetParent(Planet *p);


	void Update(float ct);
	void Draw();

	~Planet();
};
// order: squish, spin, wobble, orbital offset, orbiting, anchor
// mult scale, translate, rotation matrix
// then mult parent transform


#endif