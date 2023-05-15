//
// Created by Андрей on 22.03.2023.
//

#include "ConverterJSON.h"

#include <utility>

ConverterJson::ConverterJson() {

    myConfig = new config("", "0.1");
   std::cout << checkConfig("config.json") << std::endl;
}

ConverterJson::ConverterJson(std::string file){
     myConfig = new config("", "0.1");
     std::cout << checkConfig(file) << std::endl;
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
           file.close();
           if (buffer["config"] == nullptr){
               throw ConfigException("config file is empty");

           }else if(buffer["config"]["name"] == nullptr){
               throw ConfigException ("Search Engine name is empty");
           }else if (buffer["config"]["version"] != myConfig->version ){
               throw ConfigException ("config.json has incorrect file version.");
           } else {
               myConfig->name = buffer["config"]["name"];
               return buffer["config"]["name"];
           }
       }
    }
    catch (const ConfigException &fail) {
        std::cerr << fail.what() << std::endl;
    }
    return "FAILURE";
}

std::vector<std::string> ConverterJson::GetTextDocuments() {
    std::vector <std::string> filesContent;
        int i = 0;
        for(auto const f : buffer ["files"]){
            try{
                std::string fileName = f.dump();
            file.open (fileName);
            if (!file.is_open()){
                throw ConfigException("resources file is missing.");
            }else {
                nlohmann::json content;
                file >> content;
                file.close();
              filesContent.push_back(content.dump());

            }
            }catch (const ConfigException &fail) {
                std::cerr << fail.what() << std::endl;
            }

            if (i >=1000){
                throw ConfigException ("exceeding the number of requests");
            }
            i++;
        }
    return filesContent;
}

int ConverterJson::GetResponsesLimit() {
    if (buffer ["config"]["max_responses"] != nullptr) {
        myConfig->max_responses = buffer ["config"]["max_responses"];
    }
    return myConfig->max_responses;
}

void ConverterJson::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {
    std::ofstream answersFile("answers.json");
    nlohmann::json jAnswers;

    for (int j = 0; j < answers.size(); j++) {
        std::vector <std::pair <int, float>> relevance;
        relevance = answers [j];

        std::pair <std::string, bool> result;
        result.first = "result";
        if(relevance.size() > 0) {
            result.second = true;
        } else {
            result.second = false;
        }

        jAnswers["answers"]["requests" + std::to_string(j)][result.first] = result.second;
        std::vector <std::pair <std::pair <std::string, int>,std::pair <std::string,float>>> relevanceArr;
        for (int i = 0; i < relevance.size(); i++) {

            std::pair <std::pair <std::string, int>,std::pair <std::string,float>> relevance_to_output;
            relevance_to_output.first = {"docid",relevance[i].first};
            relevance_to_output.second = {"rank", (relevance[i].second)};
            relevanceArr.push_back(relevance_to_output);
        }  

        if(relevanceArr.size() == 0){
            jAnswers ["answers"]["requests" + std::to_string(j)] ["relevance"] = 0;
        }else{
            jAnswers ["answers"]["requests" + std::to_string(j)] ["relevance"] = relevanceArr;
        }
    }
    answersFile << jAnswers;
    answersFile.close();
}
std::vector<std::string> ConverterJson::GetRequests (){
   return GetRequests("requests.json");
}
std::vector<std::string> ConverterJson::GetRequests(std::string file_name) {
    std::vector <std::string> requests;
    try{
    file.open (file_name);
    if (!file.is_open()){
        throw ConfigException("requests file is missing.");
    } else {
        buffer.clear();
        file >> buffer;
        file.close();
        if (buffer["requests"] == nullptr){
            throw ConfigException ("requests file is empty.");
        }else {
            for (auto r : buffer["requests"]){
                requests.push_back(r);
            }
        }
    }

    }
    catch (const ConfigException &fail) {
        std::cerr << fail.what() << std::endl;
    }
    return requests;
}

config::config(std::string _name, std::string _version,int _mResponses) {
    name = std::move(_name);
    version = std::move(_version);
    max_responses = _mResponses;
}
