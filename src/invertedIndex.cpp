#include "InvertedIndex.h"
#include <fstream>

InverterIndex::InverterIndex() = default;
InverterIndex::~InverterIndex(){

}
void InverterIndex::UpdateDocumentBase(std::vector<std::string> input_docs){
std::ifstream file;
    for (auto fileName : input_docs){

       file.open(fileName);
       if (!file.is_open()) break;
       else{char buffer [100000];
           file.getline(buffer,sizeof(buffer));
           docs.push_back(buffer);}

    }
}
std::vector<Entry> InverterIndex::GetWordCount(const std::string& word){
  std::vector<  Entry > a;
return a;
}
