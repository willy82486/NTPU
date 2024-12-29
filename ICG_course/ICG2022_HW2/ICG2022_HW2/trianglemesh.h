#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "headers.h"
#include "material.h"

// VertexPTN Declarations.
struct VertexPTN
{
	VertexPTN() {
		position = vec3(0.0f, 0.0f, 0.0f);
		texcoord = vec2(0.0f, 0.0f);
		normal = vec3(0.0f, 1.0f, 0.0f);
	}
	VertexPTN(vec3 p, vec2 uv, vec3 n) {
		position = p;
		normal = n;
		texcoord = uv;
	}
	vec3 position;
	vec2 texcoord;
	vec3 normal;
	
};

// SubMesh Declarations.
struct SubMesh
{
	SubMesh() {
		material = nullptr;
		iboId = 0;
	}
	PhongMaterial* material;
	GLuint iboId;
	vector<unsigned int> vertexIndices;
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

	void CreateBuffers();

	void Draw(const SubMesh &submesh_Obj);
	
	// Show model information.
	void ShowInfo();

	// -------------------------------------------------------
	// Feel free to add your methods or data here.
	// -------------------------------------------------------

	int GetNumVertices() const { return numVertices; }
	int GetNumTriangles() const { return numTriangles; }
	int GetNumSubMeshes() const { return (int)subMeshes.size(); }

	vec3 GetObjCenter() const { return objCenter; }
	vec3 GetObjExtent() const { return objExtent; }

	float GetSubMeshesMaterialNs(int index) const { return subMeshes[index].material->GetNs(); };
	vec3 GetSubMeshesMaterialKa(int index) const { return subMeshes[index].material->GetKa(); };
	vec3 GetSubMeshesMaterialKd(int index) const { return subMeshes[index].material->GetKd(); };
	vec3 GetSubMeshesMaterialKs(int index) const { return subMeshes[index].material->GetKs(); };
	SubMesh GetSubMeshes(int index) const { return subMeshes[index]; };
	void ReleaseMaterialinSubmesh(int index) { delete subMeshes[index].material, subMeshes[index].material = nullptr, subMeshes[index].vertexIndices.clear(); };

private:
	// -------------------------------------------------------
	// Feel free to add your methods or data here.
	// -------------------------------------------------------

	// TriangleMesh Private Data.
	GLuint vboId;
	GLuint iboId;
	vector<VertexPTN> vertices;
	// For supporting multiple materials per object, move to SubMesh.
	// GLuint iboId;
	// vector<unsigned int> vertexIndices;
	vector<SubMesh> subMeshes;
	
	map<string, PhongMaterial> pMaterial_lib;
	map<tuple<unsigned int, unsigned int, unsigned int>, unsigned int> vertices_lib;
	vector<vec3> vp_lib;
	vector<vec3> vn_lib;
	vector<vec2> vt_lib;

	float verticeTotalPositionX;
	float verticeTotalPositionY;
	float verticeTotalPositionZ;
	
	int numKindsOfVertices;
	int numVertices;
	int numTriangles;

	vec3 objCenter;
	vec3 objExtent;



	// Spilt string
	vector<string> splitString(const string& str, const vector<string>& pattern);
	// Do vertex position normalize
	void VertexPositionNormalize();
};


#endif
