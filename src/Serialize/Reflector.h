#pragma once
#include <concepts>

namespace ComponentSerialize {


	template <typename SerializableObject>
	//&& makes argument truly generic (can be literally any kind of rvalue)
	concept has_serialized_fields = requires(SerializableObject && s) {
		SerializableObject();
		typename SerializableObject::SerializedFields;
		{ s.Get_Accessor() } -> std::same_as<typename SerializableObject::SerializedFields*>;

	};


	template<has_serialized_fields T>
	struct Reflector;
}


#define VERIFY_SERIAL(StructName) \
    namespace ComponentSerialize { \
        Reflector<StructName> CONCAT(r_, StructName); \
    } \


//namespace rfl {
//	template <typename T>
//	struct Reflector;
//
//	namespace internal {
//
//		template <typename Type>
//		concept has_write_reflector = requires(Type && item) {
//			Reflector<Type>::from(item);
//		};
//
//		template <typename Type>
//		concept has_read_reflector =
//			requires(const typename Reflector<Type>::ReflType & item) {
//			Reflector<Type>::to(item);
//		};
//
//	}  // namespace internal
//}  // namespace rfl

