#include "trianglemesh.h"

// Constructor of a triangle mesh.
TriangleMesh::TriangleMesh()
{
	numVertices = 0;
	numTriangles = 0; 
	numKindsOfVertices = 0;
	verticeTotalPositionX = 0.0f;
	verticeTotalPositionY = 0.0f;
	verticeTotalPositionZ = 0.0f;
	objCenter = vec3(0.0f, 0.0f, 0.0f);
	objExtent = vec3(0.0f, 0.0f, 0.0f);
	// ---------------------------------------------------------------------------
	// Feel free to add codes.
	// ---------------------------------------------------------------------------
}

// Destructor of a triangle mesh.
TriangleMesh::~TriangleMesh()
{
	vertices.clear();
	vertexIndices.clear();
	// ---------------------------------------------------------------------------
	// Feel free to add codes.
	// ---------------------------------------------------------------------------
}

// Push Vertex content into Buffer which connecting with CPU and GPU
void TriangleMesh::CreateBuffers() {
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPTN) * numKindsOfVertices, &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * vertexIndices.size(), &vertexIndices[0], GL_STATIC_DRAW);
}

// Render ing using content in Buffer
void TriangleMesh::Draw() {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPTN), 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glDrawElements(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
}

// Load the geometry and material data from an OBJ file.
bool TriangleMesh::LoadFromFile(const std::string& filePath, const bool normalized)
{
	// Parse the OBJ file.
	// ---------------------------------------------------------------------------
	// Add your implementation.
	// ---------------------------------------------------------------------------
	ifstream ifsObj;
	ifsObj.open(filePath);
	if (!ifsObj.is_open()) {
		cout << "Failed to open obj_file.\n";
		exit(1);
	}
	else {
		cout << "Successed to open obj_file.\n";
		string tmp_str;
		vector<string> spilt_str;
		vector<string> delimiter;
		delimiter.push_back(" ");
		delimiter.push_back("/");
		while (getline(ifsObj, tmp_str)) {		// read line
			// cout << tmp_str << endl;
			if (tmp_str.size() == 0);
			else {
				spilt_str = splitString(tmp_str, delimiter);	// spilt string	
				if (spilt_str[0] == "mtllib") {
					/*
					vector<string> mtl_delimiter;
					mtl_delimiter.push_back(".");
					vector<string> mtl_file = splitString(spilt_str[1], delimiter);
					string mtl_filepath = "models/" + mtl_file[0] + "/" + mtl_file[0] + ".mtl";

					ifstream ifsMtl;
					ifsMtl.open(mtl_filepath);
					if (!ifsObj.is_open()) {
						cout << "Failed to open mtl_file.\n";
						exit(1);
					}
					else {
						cout << "Successed to open mtl_file.\n";
					}*/

				}
				else if (spilt_str[0] == "v") {
					vp_lib.push_back(vec3(stof(spilt_str[1]), stof(spilt_str[2]), stof(spilt_str[3])));
					verticeTotalPositionX += stof(spilt_str[1]);
					verticeTotalPositionY += stof(spilt_str[2]);
					verticeTotalPositionZ += stof(spilt_str[3]);
				}
				else if (spilt_str[0] == "vt") {
					vt_lib.push_back(vec2(stof(spilt_str[1]), stof(spilt_str[2])));
					//-----------------------------------------------------------------------------------

					//------------------------------------------------------------------------------------
				}
				else if (spilt_str[0] == "vn") {
					vn_lib.push_back(vec3(stof(spilt_str[1]), stof(spilt_str[2]), stof(spilt_str[3])));
				}
				else
					continue;
			}
		}
	}
	ifsObj.close();
	cout << "Close file first time." << endl;
	// Normalize the geometry data.
	if (normalized) {
		// -----------------------------------------------------------------------
		// Add your normalization code here (HW1).
		// -----------------------------------------------------------------------
		VertexPositionNormalize();
		cout << "Do Vertex Position Normalization " << endl;
	}

	//-----------------------------------------------------------------------------------
	// Push Vertex Index into Vector
	//-----------------------------------------------------------------------------------
	ifsObj.open(filePath, ios::in);
	if (!ifsObj.is_open()) {
		cout << "Failed to open obj_file.\n";
		exit(1);
	}
	string tmp_str;
	vector<string> spilt_str;
	vector<string> delimiter;
	delimiter.push_back(" ");
	delimiter.push_back("/");
	while (getline(ifsObj, tmp_str)) {		// read line
		spilt_str = splitString(tmp_str, delimiter);	// spilt string	
		if (tmp_str.size() == 0);
		else {
			if (spilt_str[0] == "f") {
				for (int i = 1; i < spilt_str.size(); i += 3) {

					tuple<unsigned int, unsigned int, unsigned int> tmp_tuple(abs(stoi(spilt_str[i])), abs(stoi(spilt_str[i + 1])), abs(stoi(spilt_str[i + 2])));
					if (vertices_lib.find(tmp_tuple) == vertices_lib.end()) {		// Add vertices into Lib if it doesn't exit in Lib
						vertices_lib.insert(make_pair(tmp_tuple, numKindsOfVertices));
						numKindsOfVertices++;
						VertexPTN tmp_VertexPTN(vp_lib[abs(stoi(spilt_str[i])) - 1], vt_lib[abs(stoi(spilt_str[i + 1])) - 1], vn_lib[abs(stoi(spilt_str[i + 2])) - 1]);
						vertices.push_back(tmp_VertexPTN);
					}
				}
				for (int end = 9; end < spilt_str.size(); end += 3) {
					map<tuple<unsigned int, unsigned int, unsigned int>, unsigned int> ::iterator iter;

					tuple<unsigned int, unsigned int, unsigned int> tmp_tuple(abs(stoi(spilt_str[1])), abs(stoi(spilt_str[2])), abs(stoi(spilt_str[3])));
					unsigned int num;
					iter = vertices_lib.find(tmp_tuple);
					num = iter->second;
					vertexIndices.push_back(num);
					numVertices++;

					tuple<unsigned int, unsigned int, unsigned int> tmp_tuple1(abs(stoi(spilt_str[end - 5])), abs(stoi(spilt_str[end - 4])), abs(stoi(spilt_str[end - 3])));
					iter = vertices_lib.find(tmp_tuple1);
					num = iter->second;
					vertexIndices.push_back(num);
					numVertices++;

					tuple<unsigned int, unsigned int, unsigned int> tmp_tuple2(abs(stoi(spilt_str[end - 2])), abs(stoi(spilt_str[end - 1])), abs(stoi(spilt_str[end])));
					iter = vertices_lib.find(tmp_tuple2);
					num = iter->second;
					vertexIndices.push_back(num);
					numVertices++;
				}
			}
			else
				continue;
		}
	}
	ifsObj.close();
	numTriangles = numVertices / 3;
	
	return true;
}

// Apply transform to vertices using GPU.
void TriangleMesh::ApplyTransformCPU(const mat4x4& mvpMatrix)
{
	for (int i = 0; i < numKindsOfVertices; ++i) {
		vec4 p = mvpMatrix * vec4(vertices[i].position, 1.0f);
		if (p.w != 0.0f) {
			float inv = 1.0f / p.w;
			vertices[i].position.x = p.x * inv;
			vertices[i].position.y = p.y * inv;
			vertices[i].position.z = p.z * inv;
		}
	}
}

// Show model information.
void TriangleMesh::ShowInfo()
{
	std::cout << "# Vertices: " << numVertices << std::endl;
	std::cout << "# Triangles: " << numTriangles << std::endl;
	std::cout << "Model Center: " << objCenter.x << ", " << objCenter.y << ", " << objCenter.z << std::endl;
	std::cout << "Model Extent: " << objExtent.x << " x " << objExtent.y << " x " << objExtent.z << std::endl;
}

// Spilt string
vector<string> TriangleMesh::splitString(const string& str, const vector<string>& pattern)
{
	vector<string> result;
	string tmp_str = pattern[0];
	//string::size_type型別，left：左邊界位置  right：右邊界位置 
	string::size_type left, right;
	string::size_type tmp_right = str.find(pattern[0]);
	for (int i = 1; i < pattern.size(); i++) {
		if (str.find(pattern[i]) < tmp_right) {
			tmp_right = str.find(pattern[i]);
			tmp_str = pattern[i];
		}
	}
	right = tmp_right;
	left = 0;

	while (right != string::npos)
	{
		//以免字串首部就是分割依據，壓入長度為0的字串 
		if (right - left > 0)
		{
			//壓入起始位置為left，長度為（right-left）的字串 
			result.push_back(str.substr(left, right - left));
		}
		left = right + tmp_str.size();   //右邊界右移分割依據的長度，作為新的左邊界 
		tmp_right = str.find(pattern[0], left);   //從left這個位置開始find 
		for (int i = 1; i < pattern.size(); i++) {
			if (str.find(pattern[i], left) < tmp_right) {
				tmp_right = str.find(pattern[i], left);
				tmp_str = pattern[i];
			}
		}
		right = tmp_right;
	}

	//退出迴圈時，左邊界不是最後一個元素 
	if (left != str.length())
	{
		result.push_back(str.substr(left));
	}

	return result;
}

// Do vertex position normalize
void TriangleMesh::VertexPositionNormalize() {
	//-----------------------------------------------------------------
	// Translation
	objCenter = vec3(verticeTotalPositionX / vp_lib.size(), verticeTotalPositionY / vp_lib.size(), verticeTotalPositionZ / vp_lib.size());
	for (int i = 0; i < vp_lib.size(); i++) {	
		vp_lib[i].x -= verticeTotalPositionX / vp_lib.size();
		vp_lib[i].y -= verticeTotalPositionY / vp_lib.size();
		vp_lib[i].z -= verticeTotalPositionZ / vp_lib.size();
	}
	//-----------------------------------------------------------------
	//-----------------------------------------------------------------
	// Find Scale coefficient
	float maxverticePositionX = vp_lib[0].x;
	float minverticePositionX = vp_lib[0].x;
	float maxverticePositionY = vp_lib[0].y;
	float minverticePositionY = vp_lib[0].y;
	float maxverticePositionZ = vp_lib[0].z;
	float minverticePositionZ = vp_lib[0].z;
	for (int i = 0; i < vp_lib.size(); i++) {
		if (vp_lib[i].x > maxverticePositionX) {
			maxverticePositionX = vp_lib[i].x;
		}
		if (vp_lib[i].x < minverticePositionX) {
			minverticePositionX = vp_lib[i].x;
		}
		if (vp_lib[i].y > maxverticePositionY) {
			maxverticePositionY = vp_lib[i].y;
		}
		if (vp_lib[i].y < minverticePositionY) {
			minverticePositionY = vp_lib[i].y;
		}
		if (vp_lib[i].z > maxverticePositionZ) {
			maxverticePositionZ = vp_lib[i].z;
		}
		if (vp_lib[i].z < minverticePositionZ) {
			minverticePositionZ = vp_lib[i].z;
		}
	}
	float maxdistance = maxverticePositionX - minverticePositionX;
	if (maxverticePositionY - minverticePositionY > maxdistance) {
		maxdistance = maxverticePositionY - minverticePositionY;
	}
	if (maxverticePositionZ - minverticePositionZ > maxdistance) {
		maxdistance = maxverticePositionZ - minverticePositionZ;
	}
	//-----------------------------------------------------------------
	//----------------------------------------------------------------- 
	// Scale
	for (int i = 0; i < vp_lib.size(); i++) {	
		vp_lib[i].x /= maxdistance;
		vp_lib[i].y /= maxdistance;
		vp_lib[i].z /= maxdistance;
	}
	//-----------------------------------------------------------------
}