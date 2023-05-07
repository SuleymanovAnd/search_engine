#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H
#include <map>
#include <vector>
#include <iostream>

struct Entry {
size_t doc_id, count;
};

class InverterIndex {
private:
std::map<std::string, std::vector<Entry>> freq_dictionary;
std::vector<std::string> docs;

public:
InverterIndex();
~InverterIndex();
void UpdateDocumentBase(std::vector<std::string> input_docs);
std::vector<Entry> GetWordCount(const std::string& word);
};

#endif // INVERTEDINDEX_H
