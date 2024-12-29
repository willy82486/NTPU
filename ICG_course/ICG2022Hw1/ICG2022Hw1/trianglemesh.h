#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <Windows.h>
// OpenGL and FreeGlut headers.
#include <glew.h>
#include <freeglut.h>

// GLM.
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

// C++ STL headers.
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace glm;

// VertexPTN Declarations.
struct VertexPTN
{
	VertexPTN() {
		position = vec3(0.0f, 0.0f, 0.0f);
		normal = vec3(0.0f, 1.0f, 0.0f);
		texcoord = vec2(0.0f, 0.0f);
	}
	VertexPTN(vec3 p, vec2 uv ,vec3 n) {
		position = p;
		normal = n;
		texcoord = uv;
	}
	vec3 position;		// Vertex position.
	vec3 normal;		// Vertex normal.
	vec2 texcoord;		// Vertex texture coordinate (will be used later HWs)
};

// TriangleMesh Declarations.
class TriangleMesh
{
public:
	// TriangleMesh Public Methods.
	TriangleMesh();
	~TriangleMesh();

	// Load the model from an *.OBJ file.
	bool LoadFromFile(const string& filePath, const bool normalized = true);

	// Apply transform on CPU.
	void ApplyTransformCPU(const mat4x4& mvpMatrix);

	// Show model information.
	void ShowInfo();

	void CreateBuffers();

	void Draw();
	// ---------------------------------------------------------------------------
	// Add new methods if needed.
	// ---------------------------------------------------------------------------

	// Spilt string
	vector<string> splitString(const string& str, const vector<string>& pattern);

	// Do vertex position normalize
	void VertexPositionNormalize();

private:
	// TriangleMesh Private Methods.
	// ---------------------------------------------------------------------------
	// Add new methods if needed.
	// ---------------------------------------------------------------------------

	// TriangleMesh Private Data.
	GLuint vboId;
	GLuint iboId;
	vector<VertexPTN> vertices;
	map<tuple<unsigned int, unsigned int, unsigned int>, unsigned int> vertices_lib;
	vector<unsigned int> vertexIndices;
	vector<vec3> vp_lib;
	vector<vec3> vn_lib;
	vector<vec2> vt_lib;
	int numVertices;
	int numTriangles;
	int numKindsOfVertices;
	float verticeTotalPositionX;
	float verticeTotalPositionY;
	float verticeTotalPositionZ;


	vec3 objCenter;
	vec3 objExtent;
	// ---------------------------------------------------------------------------
	// Add new data if needed.
	// ---------------------------------------------------------------------------
};

#endif
