#include "InvertedIndex.h"
#include <fstream>
#include <algorithm>
#include <QElapsedTimer>
#include <QFuture>
#include <QtConcurrent>

void InvertedIndex::UpdateFreqDictionary (const std::string word,const size_t documentNumber, std::map <std::string,size_t> wordCount){
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
void InvertedIndex::UpdateBaseForDocument(const size_t& documentNumber, const std::string& document) {
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
                UpdateFreqDictionary(word,documentNumber,wordCount);
            }
        } else {
            if (wordCount.count(word) == 0){
                wordCount[word] = 1;}
            else {
                wordCount[word] = wordCount[word] + 1 ;
            }
            UpdateFreqDictionary(word,documentNumber,wordCount);
             word.clear();
        }
    }
}
void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs){

   for(auto doc :input_docs){
        docs.push_back(doc);
   }


    size_t documentNumber = 0;

    QElapsedTimer timer;
    timer.start();
    QList<QFuture<void>> handlers;

    for (auto &document  : docs){

        handlers.append(QtConcurrent::run(this,&InvertedIndex::UpdateBaseForDocument,documentNumber,document));
        documentNumber++;
    }
    for (auto &f: handlers){
        f.waitForFinished();
    }
std::cout << "Calc timer: " << timer.elapsed() << "mseconds" << std::endl;
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word){
            return freq_dictionary[word];
}
