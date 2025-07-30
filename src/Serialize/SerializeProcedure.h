#pragma once

#include <unordered_map>
#include <string>
#include "Procedure.h"



#define CONCAT_INNER(a, b) a##b
#define CONCAT(a, b) CONCAT_INNER(a, b)
#define STRINGIFY_INNER(x) #x
#define STRINGIFY(x) STRINGIFY_INNER(x)

//// The registration macro for components
#define REGISTER_PROCEDURE(ProcedureName) \
    namespace ProcedureSerialize { \
        struct CONCAT(ProcedureName, _registrar) { \
            CONCAT(ProcedureName, _registrar)() { \
                ProcedureSerialize::SerializeProcedures.insert({ STRINGIFY(ProcedureName), new ProcedureName()}); \
            } \
        }; \
        static CONCAT(ProcedureName, _registrar) CONCAT(ProcedureName, _instance); \
    } \


namespace ProcedureSerialize {
    inline std::unordered_map<std::string, Procedure*> SerializeProcedures;
}