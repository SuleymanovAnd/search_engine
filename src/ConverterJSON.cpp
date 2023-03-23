//
// Created by Андрей on 22.03.2023.
//

#include "ConverterJSON.h"

#include <utility>

ConverterJson::ConverterJson() {
    myConfig = new config("SkillboxSearchEngine", 0.1);
    if(checkConfig()){std::cout << "good";}
}

ConverterJson::~ConverterJson() {
    delete myConfig;
}

bool ConverterJson::checkConfig() {
    std::ifstream file ("config.json");
    file >> buffer;

    return true;
}

config::config(std::string _name, double _version,int _mResponses) {
    name = std::move(_name);
    version = std::move(_version);
    max_responses = _mResponses;
}
