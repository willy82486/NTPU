#ifndef CAMERA_H
#define CAMERA_H

#include "headers.h"

// Camera Declarations.
class Camera {
public:
	// Camera Public Methods.
	Camera(const float aspectRatio);
	~Camera();

	vec3 GetCameraPos() const { return position; }
	mat4x4 GetViewMatrix() const { return viewMatrix; }
	mat4x4 GetProjMatrix() const { return projMatrix; }

	void UpdateView(const vec3 newPos, const vec3 newTarget, const vec3 up);
	void UpdateProjection(const float fovyInDegree, const float aspectRatio, const float zNear, const float zFar);

private:
	// Camera Private Data.
	vec3 position;
	vec3 target;
	
	float fovy;	// in degree.
	float aspectRatio;
	float nearPlane;
	float farPlane;

	mat4x4 viewMatrix;
	mat4x4 projMatrix;
};

#endif
