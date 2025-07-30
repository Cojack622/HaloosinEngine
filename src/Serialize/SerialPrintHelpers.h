#pragma once

#include <string>

inline void addTab(std::string& str, int tabLevel) {
    for (int i = 0; i < tabLevel; i++) { str += "\t"; }
}

template<typename T>
inline std::string getNameFromTypeID() {
    std::string idName = typeid(T).name();

    size_t firstSpace = idName.find(' ');
    size_t secondSpace = idName.find(' ', firstSpace + 1);

    std::string Name = idName.substr(firstSpace + 1, secondSpace - firstSpace);

    //Theres decent guarantee that the strings used here will follow the correct format, but jsut incase


    return Name;
}

inline std::unordered_map<std::string, std::string> getNameValuePair(std::string componentString, int offset) {
    std::unordered_map<std::string, std::string> nameValuePair;

    const char* cArray = componentString.c_str();
    std::string name;
    //Simple creation of field/value strings map
    //Already sucks we have to use a map
    //Start at 1 "{" end before len - 1 "}"
    size_t leftPos = offset;
    for (size_t c = offset; c < componentString.length() - offset; c++) {
        if (cArray[c] == ':') {
            //+1/-1 to get without ""
            name = componentString.substr(leftPos + 1, c - leftPos - 2);
            leftPos = c + 1;
        }

        if (cArray[c] == '{') {
            size_t r = componentString.find('}', c);
            c = r;
        }

        if (cArray[c] == ',') {
            nameValuePair.insert({ name, componentString.substr(leftPos, c - leftPos) });
            leftPos = c + 1;
        }
    }

    return nameValuePair;
}

inline std::unordered_map <std::string, std::string> getJSONValuePair(std::string accessorString) {
    std::unordered_map<std::string, std::string> nameValuePair;

    const char* cArray = accessorString.c_str();
    std::string name;
    //Simple creation of field/value strings map
    //Already sucks we have to use a map
    //Start at 1 "{" end before len - 1 "}"
    size_t leftPos = accessorString.find_first_of("{") + 1;;
    for (size_t c = leftPos; c < accessorString.length() - 1; c++) {
        if (cArray[c] == ':') {
            //+1/-1 to get without ""
            name = accessorString.substr(leftPos + 1, c - leftPos - 2);
            leftPos = c + 1;
        }

        if (cArray[c] == ',') {
            nameValuePair.insert({ name, accessorString.substr(leftPos, c - leftPos) });
            leftPos = c + 1;
        }
    }

    nameValuePair.insert({ name, accessorString.substr(leftPos, accessorString.size() - leftPos - 1) });


    return nameValuePair;
}