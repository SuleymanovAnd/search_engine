
// Created by Андрей on 22.03.2023.

#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H
#include <iostream>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"
#include "config_exception.h"
struct config{
    config (std::string _name, double _version,int _mResponses);
    config (std::string _name, double _version) : config(_name,_version, 5){};

    std::string name;
    double version;
    int max_responses;
};

class ConverterJson {
    config *myConfig;
    nlohmann::json buffer;
public:
    ConverterJson ();
    bool checkConfig();
    ~ConverterJson();
};
#endif //SEARCH_ENGINE_CONVERTERJSON_H
