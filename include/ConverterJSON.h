
// Created by Андрей on 22.03.2023.

#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H
#include <iostream>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"
#include "config_exception.h"
#include <QWidget>

struct config{
    config (std::string _name, std::string _version,int _mResponses);
    config (std::string _name, std::string _version) : config(_name,_version, 5){};

    std::string name;
    std::string version;
    int max_responses;
};

class ConverterJson{
    config *myConfig;
    nlohmann::json buffer;
    std::ifstream file;

public:
    ConverterJson ();
    ConverterJson (std::string file);
    std::vector<std::string> GetTextDocuments(); //  список файлов
    int GetResponsesLimit(); // получить лимит
    std::vector<std::string> GetRequests(std::string file_name); // список запросов
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
    std::string checkConfig(std::string file_name);
    ~ConverterJson();
};
#endif //SEARCH_ENGINE_CONVERTERJSON_H