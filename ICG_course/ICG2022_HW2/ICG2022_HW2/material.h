#ifndef MATERIAL_H
#define MATERIAL_H

#include "headers.h"
#include "shaderprog.h"

// Material Declarations.
class Material
{
public:
	// Material Public Methods.
	Material() { name = "Default"; };
	~Material() {};

	void SetName(const string mtlName) { name = mtlName; }
	string GetName() const { return name; }

protected:	
	// Material Protected Data.
	string name;
};

// ------------------------------------------------------------------------------------------------

// PhongMaterial Declarations.
class PhongMaterial : public Material
{
public:
	// PhongMaterial Public Methods.
	PhongMaterial() {
		Ka = glm::vec3(0.0f, 0.0f, 0.0f);
		Kd = glm::vec3(0.0f, 0.0f, 0.0f);
		Ks = glm::vec3(0.0f, 0.0f, 0.0f);
		Ns = 0.0f;
	};
	~PhongMaterial() {};

	void SetKa(const glm::vec3 ka) { Ka = ka; }
	void SetKd(const glm::vec3 kd) { Kd = kd; }
	void SetKs(const glm::vec3 ks) { Ks = ks; }
	void SetNs(const float n) { Ns = n; }

	const glm::vec3 GetKa() const { return Ka; }
	const glm::vec3 GetKd() const { return Kd; }
	const glm::vec3 GetKs() const { return Ks; }
	const float GetNs() const { return Ns; }

private:
	// PhongMaterial Private Data.
	glm::vec3 Ka;
	glm::vec3 Kd;
	glm::vec3 Ks;
	float Ns;
};



#endif
