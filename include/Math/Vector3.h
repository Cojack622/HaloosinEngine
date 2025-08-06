#pragma once

#include <glm/glm.hpp>

#include "../Serialize/Serializable.h"

/*Wrapper class for glm::vec3
Made to replicate function of glm::vec3 with concrete type so serializer can easily read it
*/
class Vector3 : Serializable{
	
public:

	struct SerializedFields {
		float* x;
		float* y;
		float* z;
	};

	void OnInit() {}

	Vector3(float _a) {
		vector = glm::vec3(_a);
		//updateVector();
	}

	Vector3(float _x, float _y, float _z) {
		vector = glm::vec3(_x, _y, _z);
		//updateVector();
	}

	Vector3(glm::vec3 _v) {
		vector = _v;
		//updateVector();
	}

	Vector3() {
		vector = glm::vec3();
	}

	//Maintains 
	void x(float _x) {
		vector.x = _x;
	}

	void y(float _y) {
		vector.y = _y;
	}

	void z(float _z) {
		vector.z = _z;
	}

	float x() const {
		return vector.x;
	}

	float y() const {
		return vector.y;
	}

	float z() const {
		return vector.z;
	}



	void operator = (Vector3 _vector) {
		vector = _vector.GetBaseVector();
		//updateVector();
	}

	Vector3 operator +(Vector3 _vector) const {
		return Vector3(vector + _vector.GetBaseVector());
	}

	void operator += (Vector3 _vector) {
		vector += _vector.GetBaseVector();
		//updateVector();
	}

	Vector3 operator -(Vector3 _vector) const {
		return Vector3(vector - _vector.GetBaseVector());
	}

	void operator -= (Vector3 _vector) {
		vector -= _vector.GetBaseVector();
		//updateVector();
	}

	Vector3 operator * (Vector3 _vector) const {
		return Vector3(vector * _vector.GetBaseVector());
	}

	void operator *= (Vector3 _vector) {
		vector *= _vector.GetBaseVector();
		//updateVector();
	}
	
	template<typename T>
	Vector3 operator * (T scalar) const {
		return Vector3(vector*scalar);
	}

	template<typename T>
	void operator *= (T scalar) {
		vector *= scalar;
		//updateVector();
	}

	Vector3 operator / (Vector3 _vector) const {
		return Vector3(vector / _vector.GetBaseVector());
	}

	void operator /= (Vector3 _vector) {
		vector /= _vector.GetBaseVector();
		//updateVector();
	}

	template<typename T>
	Vector3 operator / (T scalar) const {
		return Vector3(vector / scalar);
	}

	template <typename T>
	void operator /= (T scalar) {
		vector /= scalar;
	}


	glm::vec3 GetBaseVector() const {
		return vector;
	}

	SerializedFields* Get_Accessor() {
		return new SerializedFields{
			&(vector.x),
			&(vector.y),
			&(vector.z)
		};
	}
	

private:
	glm::vec3 vector;

	//void updateVector() {
	//	x = vector.x;
	//	y = vector.y;
	//	z = vector.z;
	//}
	
};

//namespace ComponentSerialize {
//	Reflector<Vector3> r_Vector3;
//}