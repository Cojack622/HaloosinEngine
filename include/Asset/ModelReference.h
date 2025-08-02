#pragma once

#include "Serialize/Serializable.h"
#include "Asset/Model.h"
#include "Asset/ModelLibrary.h"

/**
Designated Reference to existing shader in scene
Allows for easy serialization/Access to global scene data
*/
class ModelReference : Serializable {


	//Sick and twisted dependency injection/singleton hybrid
	inline static ModelLibrary* lib = 0;

	Model* _model = nullptr;

	std::string ModelName = "";



public:
	static void SetLibrary(ModelLibrary* libPtr) { ModelReference::lib = libPtr; };


	ModelReference() {
	};

	ModelReference(std::string name) {
		ModelName = name;

		OnInit();
	}

	// Dereference operator (*)
	Model& operator*() const {
		return *_model;  // Return a reference to the pointed object
	}

	// Arrow operator (->)
	Model* operator->() const {
		return _model;  // Return the actual pointer
	}

	struct SerializedFields {
		std::string* Model_Name;
	};

	SerializedFields* Get_Accessor() {
		return new SerializedFields{ &ModelName };

	}

	void OnInit() {
		assert((lib != nullptr, "Shader Library not set"));
		_model = lib->getModel(ModelName);
	}
};