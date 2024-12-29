#ifndef LIGHT_H
#define LIGHT_H

#include "headers.h"


// VertexP Declarations.
struct VertexP
{
	VertexP() { position = vec3(0.0f, 0.0f, 0.0f); }
	VertexP(vec3 p) { position = p; }
	vec3 position;
};

// PointLight Declarations.
class PointLight
{
public:
	// PointLight Public Methods.
	PointLight() {
		position = vec3(1.5f, 1.5f, 1.5f);
		intensity = vec3(1.0f, 1.0f, 1.0f);
		CreateVisGeometry();
	}
	PointLight(const vec3 p, const vec3 I) {
		position = p;
		intensity = I;
		CreateVisGeometry();
	}

	vec3 GetPosition()  const { return position;  }
	vec3 GetIntensity() const { return intensity; }
	
	void Draw() {
		glPointSize(16.0f);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexP), 0);
		glDrawArrays(GL_POINTS, 0, 1);
		glDisableVertexAttribArray(0);
		glPointSize(1.0f);
	}

	void MoveLeft (const float moveSpeed) { position += moveSpeed * vec3(-0.1f,  0.0f, 0.0f); }
	void MoveRight(const float moveSpeed) { position += moveSpeed * vec3( 0.1f,  0.0f, 0.0f); }
	void MoveUp   (const float moveSpeed) { position += moveSpeed * vec3( 0.0f,  0.1f, 0.0f); }
	void MoveDown (const float moveSpeed) { position += moveSpeed * vec3( 0.0f, -0.1f, 0.0f); }
	void MoveForward(const float moveSpeed) { position += moveSpeed * glm::vec3(0.0f, 0.0f, 0.1f); }
	void MoveBackward(const float moveSpeed) { position += moveSpeed * glm::vec3(0.0f, 0.0f, -0.1f); }

protected:
	// PointLight Protected Methods.
	void CreateVisGeometry() {
		VertexP lightVtx = vec3(0, 0, 0);
		const int numVertex = 1;
		glGenBuffers(1, &vboId);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexP) * numVertex, &lightVtx, GL_STATIC_DRAW);
	}

	// PointLight Private Data.
	GLuint vboId;
	vec3 position;
	vec3 intensity;
};



// SpotLight Declarations.
class SpotLight : public PointLight
{
public:
	// SpotLight Public Methods.
	SpotLight() {
		position = vec3(0.0f, 2.0f, 0.0f);
		intensity = vec3(1.0f, 1.0f, 1.0f);
		// -------------------------------------------------------
		// Add your initialization code here.
		// -------------------------------------------------------
		direction = vec3(0.0f, -1.0f, 0.0f);
		cutoffstart = 30.0f;
		totalwidth = 45.0f;
		CreateVisGeometry();
	}
	SpotLight(const vec3 p, const vec3 I, const vec3 D, const float cutoffDeg, const float totalWidthDeg) {
		position = p;
		intensity = I;
		// -------------------------------------------------------
		// Add your initialization code here.
		// -------------------------------------------------------
		direction = D;
		cutoffstart = cutoffDeg; // cos
		totalwidth = totalWidthDeg;
		CreateVisGeometry();
	}

	// -------------------------------------------------------
	// Add your methods or data here.
	// -------------------------------------------------------
	vec3 GetDirection() const { return direction; }
	float GetCutoffStart() const { return cutoffstart; }
	float GetTotalWidth() const { return totalwidth; }

private:
	// SpotLight Public Data.
	// -------------------------------------------------------
	// Add your methods or data here.
	// -------------------------------------------------------
	vec3 direction;
	float cutoffstart;
	float totalwidth;
};



// DirectionalLight Declarations.
class DirectionalLight
{
public:
	// DirectionalLight Public Methods.
	DirectionalLight() {
		direction = vec3(1.5f, 1.5f, 1.5f);
		radiance = vec3(1.0f, 1.0f, 1.0f);
	};
	DirectionalLight(const vec3 dir, const vec3 L) {
		direction = normalize(dir);
		radiance = L;
	}

	vec3 GetDirection() const { return direction; }
	vec3 GetRadiance()  const { return radiance;  }

private:
	// DirectionalLight Private Data.
	vec3 direction;
	vec3 radiance;
};

#endif
