#include "trianglemesh.h"

// Constructor of a triangle mesh.
TriangleMesh::TriangleMesh()
{
	// -------------------------------------------------------
	// Add your initialization code here.
	// -------------------------------------------------------
	vboId = 0;

	numVertices = 0;
	numTriangles = 0;
	numKindsOfVertices = 0;
	verticeTotalPositionX = 0.0f;
	verticeTotalPositionY = 0.0f;
	verticeTotalPositionZ = 0.0f;
	objCenter = vec3(0.0f, 0.0f, 0.0f);
	objExtent = vec3(0.0f, 0.0f, 0.0f);
}

// Destructor of a triangle mesh.
TriangleMesh::~TriangleMesh()
{
	// -------------------------------------------------------
	// Add your release code here.
	// -------------------------------------------------------
	for (int i = 0; i < GetNumSubMeshes(); i++) {
		if (GetSubMeshes(i).material != nullptr) {
			ReleaseMaterialandTextureinSubmesh(i);
		}
	}
	glDeleteBuffers(1, &vboId);
	for (int i = 0; i < subMeshes.size(); i++) {
		glDeleteBuffers(1, &subMeshes[i].iboId);
	}
	vertices.clear();
	subMeshes.clear();
	pMaterial_lib.clear();
	vertices_lib.clear();
	vp_lib.clear();
	vn_lib.clear();
	vt_lib.clear();
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

// Load the geometry and material data from an OBJ file.
bool TriangleMesh::LoadFromFile(const string& filePath, const bool normalized)
{
	// Parse the OBJ file.
	// ---------------------------------------------------------------------------
	// Add your implementation here (HW1 + read *.MTL).
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
		while (true) {		// read line
			getline(ifsObj, tmp_str);
			if (ifsObj.eof() == true)
				break;

			if (tmp_str.size() == 0);
			else {
				spilt_str = splitString(tmp_str, delimiter);	// spilt string	
				if (spilt_str[0] == "mtllib") {
					vector<string> openMtlFile_delimiter;
					openMtlFile_delimiter.push_back(".");
					vector<string> mtl_filename = splitString(spilt_str[1], openMtlFile_delimiter);
					string mtl_filepath = mtl_filename[0] + ".mtl";

					// ---------------------------------------------------------------------------
					// Read MtlFile
					// ---------------------------------------------------------------------------
					ifstream ifsMtl;
					ifsMtl.open(mtl_filepath);
					if (!ifsMtl.is_open()) {
						cout << "Failed to open mtl_file.\n";
						exit(1);
					}
					else {
						cout << "Successed to open mtl_file.\n";

						string mtl_tmp_str;
						vector<string> mtl_delimiter;
						mtl_delimiter.push_back(" ");

						while (true) {
							getline(ifsMtl, mtl_tmp_str);
							if (ifsMtl.eof() == true)
								break;

							vector<string> mtl_value = splitString(mtl_tmp_str, mtl_delimiter);

							if (mtl_value.size() == 0)
								continue;
							else {
								if (mtl_value[0] == "newmtl") {
									PhongMaterial pMaterial_Obj;
									string material_Name = mtl_value[1];
									pMaterial_Obj.SetName(material_Name);
									while (true) {
										getline(ifsMtl, mtl_tmp_str);
										vector<string> mtl_value = splitString(mtl_tmp_str, mtl_delimiter);

										if (mtl_value.size() == 0 ) {
											pMaterial_lib.insert(make_pair(material_Name, pMaterial_Obj));
											break;
										}
										if (mtl_value[0] == "Ns") {
											float tmp_NsValue = stof(mtl_value[1]);
											pMaterial_Obj.SetNs(tmp_NsValue);
										}
										else if (mtl_value[0] == "Ka") {
											vec3 tmp_KaValue = vec3(stof(mtl_value[1]), stof(mtl_value[2]), stof(mtl_value[3]));
											pMaterial_Obj.SetKa(tmp_KaValue);
										}
										else if (mtl_value[0] == "Kd") {
											vec3 tmp_KdValue = vec3(stof(mtl_value[1]), stof(mtl_value[2]), stof(mtl_value[3]));
											pMaterial_Obj.SetKd(tmp_KdValue);
										}
										else if (mtl_value[0] == "Ks") {
											vec3 tmp_KsValue = vec3(stof(mtl_value[1]), stof(mtl_value[2]), stof(mtl_value[3]));
											pMaterial_Obj.SetKs(tmp_KsValue);
										}
										else if (mtl_value[0] == "map_Kd") {
											cout << "map_Kd" << endl;
											string texture_path = mtl_value[1];
											ImageTexture* imagetexture_Obj = new ImageTexture(texture_path);
											pMaterial_Obj.SetMapKd(imagetexture_Obj);
										}
										if (ifsMtl.eof()) {
											pMaterial_lib.insert(make_pair(material_Name, pMaterial_Obj));
											break;
										}
									}
								}
							}

						}
						/*map<string, PhongMaterial>::iterator iter;
						for (iter = pMaterial_lib.begin(); iter != pMaterial_lib.end(); iter++) {
							cout << iter->second.GetName() << endl;
							cout << iter->second.GetNs() << endl;
							cout << iter->second.GetKa().x << iter->second.GetKa().y << iter->second.GetKa().z << endl;
							cout << iter->second.GetKd().x << iter->second.GetKd().y << iter->second.GetKd().z << endl;
							cout << iter->second.GetKs().x << iter->second.GetKs().y << iter->second.GetKs().z << endl;
							cout << "---------------------------------------------------------------------------" << endl;
						}*/

					}
					ifsMtl.close();

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
	//cout << "Close file first time." << endl;

	// Normalize the geometry data.
	if (normalized) {
		// -----------------------------------------------------------------------
		// Add your normalization code here (HW1).
		// -----------------------------------------------------------------------
		VertexPositionNormalize();
		//cout << "Do Vertex Position Normalization " << endl;
	}

	//-----------------------------------------------------------------------------------
	// Push Vertex Index into Vector (Submeshes)
	//-----------------------------------------------------------------------------------
	ifsObj.open(filePath, ios::in);
	if (!ifsObj.is_open()) {
		cout << "Failed to open obj_file.\n";
		exit(1);
	}

	vector<string> spilt_str;
	vector<string> delimiter;
	delimiter.push_back(" ");
	delimiter.push_back("/");
	string tmp_str;


	while (true) {
		getline(ifsObj, tmp_str);	// read line

		if (ifsObj.eof() == true)
			break;

		spilt_str = splitString(tmp_str, delimiter);	// spilt string	
		if (tmp_str.size() == 0)
			continue;
		else {
			if (spilt_str[0] == "usemtl") {
				SubMesh submesh_Obj;
				vector<unsigned int> vertexIndices;
				map<string, PhongMaterial>::iterator iter;
				iter = pMaterial_lib.find(spilt_str[1]);
				submesh_Obj.material = &iter->second;

				while (true) {
					getline(ifsObj, tmp_str);	// read line
					spilt_str = splitString(tmp_str, delimiter);	// spilt string	

					if (tmp_str.size() == 0) {
						break;
					}
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
							map<tuple<unsigned int, unsigned int, unsigned int>, unsigned int>::iterator iter;

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
					if (ifsObj.peek() != 'f') {
						submesh_Obj.vertexIndices = vertexIndices;
						subMeshes.push_back(submesh_Obj);
						break;
					}
				}
			}
		}
	}
	/*for (int i = 0; i < subMeshes.size(); i++) {
		cout << subMeshes[i].material->GetName() << endl;
		for (int j = 0; j < subMeshes[i].vertexIndices.size(); j++) {
			cout << subMeshes[i].vertexIndices[j] << " ";
		}
		cout << endl;
	}*/
	ifsObj.close();
	numTriangles = numVertices / 3;

	return true;
}

void TriangleMesh::CreateBuffers() {
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPTN) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	for (int i = 0; i < subMeshes.size(); i++) {
		glGenBuffers(1, &subMeshes[i].iboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, subMeshes[i].iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * subMeshes[i].vertexIndices.size(), &subMeshes[i].vertexIndices[0], GL_STATIC_DRAW);
	}
}

void TriangleMesh::Draw(const SubMesh& submesh_Obj)
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	// Vertex stores Position, Texture, and Normal sequentially(I change VertexPTN from VertexPTN(vec3 p, vec3 n, vec2 uv)  to  VertexPTN(vec3 p, vec2 uv, vec3 n). )
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPTN), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPTN), (const GLvoid*)12);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPTN), (const GLvoid*)20);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, submesh_Obj.iboId);
	glDrawElements(GL_TRIANGLES, (GLsizei)(submesh_Obj.vertexIndices.size()), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
// Show model information.
void TriangleMesh::ShowInfo()
{
	map<string, PhongMaterial>::iterator iter;
	for (iter = pMaterial_lib.begin(); iter != pMaterial_lib.end(); iter++) {
		cout << iter->second.GetName() << endl;
		cout << iter->second.GetNs() << endl;
		cout << iter->second.GetKa().x << " " << iter->second.GetKa().y << " " << iter->second.GetKa().z << endl;
		cout << iter->second.GetKd().x << " " << iter->second.GetKd().y << " " << iter->second.GetKd().z << endl;
		cout << iter->second.GetKs().x << " " << iter->second.GetKs().y << " " << iter->second.GetKs().z << endl;
		if (iter->second.GetMapKd() != nullptr) {
			cout << iter->second.GetMapKd()->GetPath() << endl;
		}
		cout << "---------------------------------------------------------------------------" << endl;
	}
	cout << "# Vertices: " << vertices.size() << endl;
	cout << "# Triangles: " << numTriangles << endl;
	cout << "Total " << subMeshes.size() << " subMeshes loaded" << endl;
	for (unsigned int i = 0; i < subMeshes.size(); ++i) {
		const SubMesh& g = subMeshes[i];
		cout << "SubMesh " << i << " with material: " << g.material->GetName() << endl;
		cout << "Num. triangles in the subMesh: " << g.vertexIndices.size() / 3 << endl;
	}
	cout << "Model Center: " << objCenter.x << ", " << objCenter.y << ", " << objCenter.z << endl;
	cout << "Model Extent: " << objExtent.x << " x " << objExtent.y << " x " << objExtent.z << endl;
}