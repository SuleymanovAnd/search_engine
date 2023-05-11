#include "InvertedIndex.h"
#include <fstream>
#include <algorithm>

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs){

   for(auto doc :input_docs){
        docs.push_back(doc);
   }


    size_t documentNumber = 0;
    for (auto document  : docs){
        std::map <std::string,size_t> wordCount;
        std::string word;
        auto final_iterator = document.end();
        auto iter = document.begin();
        for (auto symbol : document){
            iter ++;
            if (symbol != ' '){
                word.push_back(symbol);
                if( iter == final_iterator){
                    if (wordCount.count(word) == 0){
                        wordCount[word] = 1;
                    }else {
                        wordCount[word] = wordCount[word] + 1 ;
                    }
                    if(freq_dictionary.find(word) == freq_dictionary.end() ){
                        freq_dictionary[word].push_back({documentNumber,wordCount[word]});
                     }else{
                       bool found = false;
                       for (auto entryVector : freq_dictionary[word]){
                            if(entryVector.doc_id == documentNumber ) {found = true;}
                       }
                        if(found){
                            freq_dictionary[word][documentNumber] = {documentNumber,wordCount[word]};
                        } else {freq_dictionary[word].push_back({documentNumber,wordCount[word]});}
                    }
                }
            } else {
                if (wordCount.count(word) == 0){
                    wordCount[word] = 1;}
                else {
                    wordCount[word] = wordCount[word] + 1 ;
                }
                if(freq_dictionary.find(word) == freq_dictionary.end() ){
                   freq_dictionary[word].push_back({documentNumber,wordCount[word]});
                }else {bool found = false;
                   for (auto entryVector : freq_dictionary[word]){
                        if(entryVector.doc_id == documentNumber ) {found = true;}
                   }
                    if(found){
                        freq_dictionary[word][documentNumber] = {documentNumber,wordCount[word]};
                    } else {freq_dictionary[word].push_back({documentNumber,wordCount[word]});}
               }
                 word.clear();
            }

        }

        documentNumber++;
    }

}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word){
            return freq_dictionary[word];
}
