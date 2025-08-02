#pragma once

#include "Serialize/Serializable.h"
#include "Asset/Shader.h"
#include "Asset/ShaderLibrary.h"

/**
Designated Reference to existing shader in scene
Allows for easy serialization/Access to global scene data
*/
class ShaderReference : Serializable {


	//Sick and twisted dependency injection/singleton hybrid
	inline static ShaderLibrary* lib = 0;


	Shader* _shader = nullptr;
	std::string ShaderName = "";


public:
	struct SerializedFields {
		std::string* Shader_Name;
	};

	// Dereference operator (*)
	Shader& operator*() const {
		return *_shader;  // Return a reference to the pointed object
	}

	// Arrow operator (->)
	Shader* operator->() const {
		return _shader;  // Return the actual pointer
	}


	ShaderReference() = default;

	ShaderReference(std::string name) {
		ShaderName = name;

		OnInit();
	}

	static void SetLibrary(ShaderLibrary* libPtr) { ShaderReference::lib = libPtr; };

	SerializedFields* Get_Accessor() {
		return new SerializedFields{ &ShaderName };

	}

	void OnInit() {
		assert((lib != nullptr, "Shader Library not set"));
		_shader = lib->getShader(ShaderName);
	}
};

