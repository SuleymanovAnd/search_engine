#include "InvertedIndex.h"
#include <fstream>
#include <algorithm>
#include <QFuture>
#include <QtConcurrent>
InvertedIndex::InvertedIndex(){
    dictionaryAcces = new QMutex;
}



void InvertedIndex::UpdateFreqDictionary (const std::string word,const size_t documentNumber, std::map <std::string,size_t> wordCount){
    dictionaryAcces->lock();
    if(freq_dictionary.count(word) == 0 ){ // если в базе не найдено
        if(freq_dictionary[word].size() <= documentNumber ){
           freq_dictionary[word].push_back({documentNumber,wordCount[word]});
        }else{
            int imputPlace = 0;
            for(auto it = freq_dictionary[word].begin(); it < freq_dictionary[word].end();it++){

                if(imputPlace == documentNumber){freq_dictionary[word].insert (it, {documentNumber,wordCount[word]});}
            imputPlace++;
            }

        }

     }else{
       bool found = false;
       for (auto it = freq_dictionary[word].begin(); it < freq_dictionary[word].end();it++){ // проверяем, есть ли по данному слову нужный документ
            if(it->doc_id == documentNumber ) {
                found = true;
                auto docPosition =  std::distance(freq_dictionary[word].begin(), it);
               if(wordCount[word]>0) freq_dictionary[word][docPosition] = {documentNumber,wordCount[word]}; // и обновляем его, если он есть
            }
       }
         if (!found){
             if(freq_dictionary[word].size() <= documentNumber ){
                 freq_dictionary[word].push_back({documentNumber,wordCount[word]}); // обновляем базу по слову
             }else{
                 int imputPlace = 0;
                 for(auto it = freq_dictionary[word].begin(); it < freq_dictionary[word].end();it++){
                     // иначе добавляем документ
                     if(imputPlace == documentNumber){freq_dictionary[word].insert (it, {documentNumber,wordCount[word]});}
                     imputPlace++;
                 }
             };
         }
    }

    dictionaryAcces->unlock();
}
void InvertedIndex::UpdateBaseForDocument(const size_t documentNumber, const std::string document) {
    std::map <std::string,size_t> wordCount;
    std::string word;
    auto final_iterator = document.end();
    auto iter = document.begin();
    for (auto symbol : document){ // разбиваем документ на слова посимвольно
        iter ++;
        if (symbol != ' '){
            word.push_back(symbol); // собираем слово
            if( iter == final_iterator){ // обновляем базу для последнего слова
                if (wordCount.count(word) == 0){
                    wordCount[word] = 1;
                }else {
                    wordCount[word] = wordCount[word] + 1 ;
                }
                UpdateFreqDictionary(word,documentNumber,wordCount);
            }
        } else { // обновляем базу
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

   for(auto doc :input_docs){ // разбиваем по документам
        docs.push_back(doc);
   }
    size_t documentNumber = 0;

    // создание потоков
    QList<QFuture<void>> handlers;
    // выпоолнение UpdateBaseForDocument в отдельных потоков
    for (auto document  : docs){
        handlers.append(QtConcurrent::run(this,&InvertedIndex::UpdateBaseForDocument,documentNumber,document));
        documentNumber++;
    }
    for (auto &f: handlers){ // ожидание окончания потоков
        f.waitForFinished();
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
            return freq_dictionary[word];
}
