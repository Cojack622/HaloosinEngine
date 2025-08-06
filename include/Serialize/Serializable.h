#pragma once
///#include "Component.h"

#include "../Serialize/Reflector.h"
#include "../Serialize/SerialPrintHelpers.h"

#include <entt/entt.hpp>
#include <entt/entity/registry.hpp>

#include <entt/fwd.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <entt/core/hashed_string.hpp>

#include <rfl.hpp>
#include <rfl/json.hpp>

#include <string>
#include <map>



// Helper macros for concatenation and stringification
#define CONCAT_INNER(a, b) a##b
#define CONCAT(a, b) CONCAT_INNER(a, b)
#define STRINGIFY_INNER(x) #x
#define STRINGIFY(x) STRINGIFY_INNER(x)


// Registration macro for type declaration
#define REGISTER_TYPE(StructName) \
    namespace ComponentSerialize { \
        template <> \
        struct TypeDeclare<StructName> { \
            using Type = StructName; \
        }; \
    }



// The registration macro for components
#define REGISTER_COMPONENT(StructName) \
    namespace ComponentSerialize { \
        struct CONCAT(StructName, _registrar) { \
            CONCAT(StructName, _registrar)() { \
                entt::meta_factory<StructName>{}.type(entt::literals::operator""_hs(STRINGIFY(StructName), sizeof(STRINGIFY(StructName)) - 1)); \
                ComponentSerialize::SerializeFunctions.insert({ STRINGIFY(StructName), ComponentSerialize::SerialFunctions{&ComponentSerialize::Serialize<StructName>, &ComponentSerialize::Deserialize<StructName>} }); \
            } \
        }; \
        static CONCAT(StructName, _registrar) CONCAT(StructName, _instance); \
    }




#define COMPONENT(StructName) \
    REGISTER_COMPONENT(StructName) \


class Serializable {
    virtual void OnInit() = 0;
};


namespace ComponentSerialize {
    //Defines a pointer to function of type string f(void*)
    //Perhaps later return wrapper for rfl::named_tuple? No need to then define two functions for string serialization and MVVM view serialization 
    typedef std::string(*SerializeTypeFunction)(void*);
    typedef void(*DeserializeTypeFunction)(entt::registry&, entt::entity, std::string);


    struct SerialFunctions {
        SerializeTypeFunction Serialize;
        DeserializeTypeFunction Deserialize;
    };

    //Get Serialize function by name
    inline std::map<std::string, SerialFunctions> SerializeFunctions;

    template<typename T>
    struct TypeDeclare;

    /**
    * Serializes Component of type T
    *
    * @param component
    *   Void pointer to component of type T
    *
    * @returns std string representing component
    */
    template <typename T>
    inline std::string Serialize(void* component) {
        //Cast from void * to T
        T* componentType = static_cast<T*>(component);

        const auto view = rfl::to_view(componentType);

        //c_Blank
        std::string serialized = "";
        addTab(serialized, 1);
        serialized += getNameFromTypeID<T>();


        //c_Blank : {
        serialized += ":(\n";
        //addTab(serialized, 1);

        ////Start serializing via serialization format
        view.apply([&serialized](const auto& f_Ptr) {
            // f is an rfl::Field pointing to the original field.



            addTab(serialized, 2);

            serialized += "\"" + std::string(f_Ptr.name()) + "\":";

            auto field = *f_Ptr.value();

            using fieldType = decltype(field);

            //If Field is a pointer
            if constexpr (std::is_pointer_v<fieldType>) {
                //Dereference it
                using fieldTypeNoPointer = std::remove_pointer_t<decltype(*field)>;

                //If Field is Serializable Object
                if constexpr (has_serialized_fields<std::remove_reference_t<fieldTypeNoPointer>>) {
                    //Get Serializable 
                    serialized += getNameFromTypeID<fieldType>();
                    auto serialData = field->Get_Accessor();
                    serialized += rfl::json::write(*serialData);
                }
                else {
                    serialized += rfl::json::write(field);
                }
            }
            else {
                if constexpr (has_serialized_fields<std::remove_reference_t<fieldType>>) {
                    serialized += getNameFromTypeID<fieldType>();
                    auto serialData = field.Get_Accessor();
                    serialized += rfl::json::write(*serialData);
                }
                else {
                    serialized += rfl::json::write(field);

                }
            }

            serialized += ",\n";
            });

        addTab(serialized, 1);

        serialized += ")";

        return serialized;
    }

    /**
    *
    * Deserializes Component Value string into new Component of type T
    *
    * @param component
    *   String to deserialize. Takes form {field name 1:field value 1, ...} no whitespace
    *
    * @param entity
    *   entity to add component too
    *
    * @param reg
    *   Registry entity exists in
    */
    template<typename T>
    inline void Deserialize(entt::registry& reg, entt::entity e, std::string componentString) {
        //Passing in Registry/entity sucks and breaks the "one responsibility" principle. 
        //It SHOULD return a complete component of type T, which the caller can then do whatever they want with
        //However C++ rightfully doesn't like function pointers to template functions, So i dont know how to work around that without completely changing my serialization method (which is what i should do)

        std::unordered_map<std::string, std::string> componentPairs = getNameValuePair(componentString, 0);

        //As a component T should be default contsructorable
        //TODO: Check that T is default constructorable?
        T* component = new T();

        const auto view = rfl::to_view<T>(*component);



        view.apply([&componentPairs](const auto& f) {

            const std::string value = componentPairs[std::string(f.name())];
            //std::cout << f.name() << ":" << value << std::endl;
            using valueType = decltype((*f.value()));

            if constexpr (std::is_pointer_v<valueType>) {
                //Dereference it
                using fieldTypeNoPointer = std::remove_pointer_t<valueType>;
                using fieldType = std::remove_reference_t<fieldTypeNoPointer>;

                //If Field is Serializable Object
                if constexpr (has_serialized_fields<fieldType>) {
                    auto serialData = (*f.value())->Get_Accessor();

                    const auto serialView = rfl::to_view<fieldType::SerializedFields>(*serialData);

                    //Set value in member by
                    //1. Deserializing Field (since Accessor should return struct of pointers)
                    //2. 
                    std::unordered_map<std::string, std::string> accessorPairs = getJSONValuePair(value);

                    serialView.apply([&accessorPairs](const auto& f2) {
                        using accessorFieldType = decltype(*f2.value());
                        static_assert(std::is_pointer_v<std::remove_reference_t<accessorFieldType>>, "All Accessor Fields must be raw pointers to class data members");

                        using fieldRawType = decltype(*(*f2.value()));
                        *(*f2.value()) = rfl::json::read<std::remove_reference_t<fieldRawType>>(accessorPairs[std::string(f2.name())]).value();
                        //::cout << f2.name() << ":" << *f2.value() << std::endl;

                        });

                    (*f.value())->OnInit();
                }
                else {
                    *(*f.value()) = rfl::json::read<fieldType>(value);

                }

                //reg.emplace<T>(entity, component);
            }
            else {
                using fieldType = std::remove_reference_t<valueType>;

                if constexpr (has_serialized_fields<std::remove_reference_t<fieldType>>) {
                    auto serialData = (*f.value()).Get_Accessor();

                    const auto serialView = rfl::to_view<fieldType::SerializedFields>(*serialData);


                    std::unordered_map<std::string, std::string> accessorPairs = getJSONValuePair(value);

                    serialView.apply([&accessorPairs](const auto& f2) {
                        using accessorFieldType = decltype(*f2.value());
                        static_assert(std::is_pointer_v<std::remove_reference_t<accessorFieldType>>, "All Accessor Fields must be raw pointers to class data members");

                        using fieldRawType = decltype(*(*f2.value()));
                        *(*f2.value()) = rfl::json::read<std::remove_reference_t<fieldRawType>>(accessorPairs[std::string(f2.name())]).value();
                        //::cout << f2.name() << ":" << *f2.value() << std::endl;

                        });

                    (*f.value()).OnInit();
                }
                else {
                    *f.value() = rfl::json::read<fieldType>(value);
                    std::cout << f.name() << ":" << *f.value() << std::endl;
                }

            }



            });

        reg.emplace<T>(e, *component);

        delete(component);
    }

}




