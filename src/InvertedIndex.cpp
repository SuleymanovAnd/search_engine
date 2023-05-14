#include "InvertedIndex.h"
#include <fstream>
#include <algorithm>
#include <QElapsedTimer>
#include <QFuture>
#include <QtConcurrent>

void InvertedIndex::UpdateFreqDictionary (const std::string word,const size_t documentNumber, std::map <std::string,size_t> wordCount){
    if(freq_dictionary.count(word) == 0 ){ // если в базе не найдено
        freq_dictionary[word].push_back({documentNumber,wordCount[word]}); // обновляем базу по слову
     }else{
       bool found = false;
       for (auto entryVector : freq_dictionary[word]){ // проверяем, есть ли по данному слову нужный документ
            if(entryVector.doc_id == documentNumber ) {found = true;}
       }
        if(found){ // если есть
            freq_dictionary[word][documentNumber] = {documentNumber,wordCount[word]}; // обновляем базу по документу
        } else {freq_dictionary[word].push_back({documentNumber,wordCount[word]});} // иначе добавляем документ
    }
}
void InvertedIndex::UpdateBaseForDocument(const size_t& documentNumber, const std::string& document) {
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
    QElapsedTimer timer;
    // создание потоков
    QList<QFuture<void>> handlers;
    // выпоолнение UpdateBaseForDocument в отдельных потоков
    for (auto &document  : docs){
        handlers.append(QtConcurrent::run(this,&InvertedIndex::UpdateBaseForDocument,documentNumber,document));
        documentNumber++;
    }
    for (auto &f: handlers){ // ожидание окончания потоков
        f.waitForFinished();
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word){
            return freq_dictionary[word];
}
