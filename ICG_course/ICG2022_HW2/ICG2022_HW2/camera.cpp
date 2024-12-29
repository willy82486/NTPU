#include "camera.h"

Camera::Camera(const float aspectRatio)
{
	// Default camera pose and parameters.
	position = vec3(0.0f, 0.0f, 3.0f);
	target = vec3(0.0f, 0.0f, 0.0f);
	fovy = 45.0f;
	nearPlane = 0.1f;
	farPlane = 1000.0f;
	UpdateView(position, target, vec3(0.0f, 1.0f, 0.0f));
	UpdateProjection(fovy, aspectRatio, nearPlane, farPlane);
}

Camera::~Camera() 
{}

void Camera::UpdateView(const vec3 newPos, const vec3 newTarget, const vec3 up)
{
	position = newPos;
	target = newTarget;
	viewMatrix = lookAt(position, target, up);
}

void Camera::UpdateProjection(const float fovyInDegree, const float aspectRatio, const float zNear, const float zFar)
{
	fovy = fovyInDegree;
	nearPlane = zNear;
	farPlane = zFar;
	projMatrix = perspective(radians(fovyInDegree), aspectRatio, nearPlane, farPlane);
}