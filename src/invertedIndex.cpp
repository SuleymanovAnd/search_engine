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
       else{char bufer [100000];
           file.getline(bufer,sizeof(bufer));
           docs.push_back(bufer);}

    }
}
std::vector<Entry> InverterIndex::GetWordCount(const std::string& word){
  std::vector<  Entry > a;
return a;
}
