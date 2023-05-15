#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H
#include <map>
#include <vector>
#include <iostream>
#include <QMutex>
#include <QMutexLocker>
#include <ConverterJSON.h>

#pragma once

struct Entry {
size_t doc_id, count;
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};


class InvertedIndex {
private:
QMutex *dictionaryAcces;
std::map<std::string, std::vector<Entry>> freq_dictionary;
std::vector<std::string> docs;


void UpdateBaseForDocument(const size_t documentNumber,const std::string document);
void UpdateFreqDictionary (const std::string word,const size_t documentNumber, std::map <std::string,size_t> wordCount);

public:

InvertedIndex();
~InvertedIndex()=default;
void UpdateDocumentBase(std::vector<std::string> input_docs);
std::vector<Entry> GetWordCount(const std::string& word);
};

#endif // INVERTEDINDEX_H
