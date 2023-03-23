//
// Created by Андрей on 22.03.2023.
//

#include "ConverterJSON.h"

#include <utility>

ConverterJson::ConverterJson() {
    myConfig = new config("", "0.1");
   std::cout << checkConfig("config.json") << std::endl;
}

ConverterJson::~ConverterJson() {
    delete myConfig;
}

std::string ConverterJson::checkConfig(std::string file_name) {

    try{
        file.open(file_name);
       if (!file.is_open()){
           throw ConfigException("config file is missing.");
       } else {
           file >> buffer;
           if (buffer["config"] == nullptr){
               throw ConfigException("config file is empty");

           }else if(buffer["config"]["name"] == nullptr){
               throw ConfigException ("Search Engine name is empty");
           }else if (buffer["config"]["version"] != myConfig->version ){
               throw ConfigException ("config.json has incorrect file version.");
           } else {
               myConfig->name = buffer["config"]["name"];
               myConfig->max_responses = buffer ["config"]["max_responses"];
               return buffer["config"]["name"];
           }
       }
    }
    catch (const ConfigException &fail) {
        std::cerr << fail.what() << std::endl;
    }
    return "FAILURE";
}

config::config(std::string _name, std::string _version,int _mResponses) {
    name = std::move(_name);
    version = std::move(_version);
    max_responses = _mResponses;
}
