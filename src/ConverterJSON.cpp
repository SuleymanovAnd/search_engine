//
// Created by Андрей on 22.03.2023.
//

#include "ConverterJSON.h"
#include <utility>
ConverterJson::ConverterJson () : ConverterJson ("../config/config.json"){}
ConverterJson::ConverterJson(std::string file){
     myConfig = new config("", "0.1");
     std::cout << "Search engine name: " << checkConfig(std::move(file)) << std::endl;
}
ConverterJson::ConverterJson (const ConverterJson & oth){
    buffer = oth.buffer;
    myConfig = new config(*oth.myConfig);
}
ConverterJson& ConverterJson::operator =(const ConverterJson &oth){
        if(this == &oth){
            return *this;
        }
        buffer = oth.buffer;
        if(myConfig != nullptr){
            delete myConfig;
        }
        myConfig = new config(*oth.myConfig);
        return *this;
}
ConverterJson::~ConverterJson() {
    delete myConfig;
}
std::string ConverterJson::checkConfig(const std::string& file_name) {

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
        for(auto const f : buffer ["files"]){
            try{
            bool correctWordsCount = true;
            bool correctWordsSize = true;
            std::string fileName = f;
            file.open (fileName);
            if (!file.is_open()){
                throw ConfigException("resources file is missing.");
            }else {

                std::string content;
                    int wordCount = 0;
                while(!file.eof()){
                   std::string tempStr;
                   bool correctWordSize = true;
                   file >> tempStr;
                   if(tempStr.size()>100){
                       correctWordSize = false;
                       correctWordsSize = false;
                   }
                   if(correctWordSize && correctWordsCount){
                       content += tempStr;
                       if(!file.eof())content += " ";
                   }
                   if(wordCount>1000){correctWordsCount = false;}
                   wordCount++;
                }
                file.close();
             if(correctWordsCount) filesContent.push_back(content);
             else filesContent.push_back("");

            }
            if(!correctWordsCount){throw ConfigException("words count > 1000");}
            if(!correctWordsSize){throw ConfigException("word length > 100 symbols");}
            }catch (const ConfigException &fail) {
                std::cerr << fail.what() << std::endl;
            }
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
    std::ofstream answersFile("../answers/answers.json");
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
   return GetRequests("../requests/requests.json");
}
std::vector<std::string> ConverterJson::GetRequests(const std::string& file_name) {
    std::vector <std::string> requests;
    try{
    bool correctRequests = true;
    bool correctCount = true;
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
            int requestsCount =0;
                for (auto request : buffer["requests"]){
                // проверка валидности запроса
                if(correctCount){
                    int wordCount = 0;
                    int symbolCount = 0;
                    bool correctRequest = true;
                    std::string strRequest = request;
                    for(auto word :strRequest){
                        if(word == ' '){
                            wordCount++;
                            symbolCount = 0;
                        }
                        if (word != ' ')symbolCount++;
                        if(symbolCount >= 100 || wordCount > 10){
                            correctRequest = false;
                            correctRequests = false;
                        }
                    }

                    //
                    if (correctRequest){
                        requestsCount ++;
                        if (requestsCount >=1000){
                            correctCount = false;
                        }
                        requests.push_back(request);
                    }
                }
            }
        }
    }
    if(!correctRequests)throw ConfigException ("uncorrect request");
    if(!correctCount)  throw ConfigException ("number of requests exceeded");
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
