#include <iostream>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
#include <QApplication>

int main() {

    ConverterJson converter;
    InvertedIndex idx;
    idx.UpdateDocumentBase(converter.GetTextDocuments());
    SearchServer currentServer(idx);
    auto tempResult = currentServer.search(converter.GetRequests(),converter.GetResponsesLimit());
    std::vector<std::vector<std::pair<int, float>>> searchResult;
    for(auto tmpPart : tempResult){
        std::vector <std::pair<int,float>>searchResultPart;
        for(auto tmpRltiveIdx : tmpPart){
            std::pair<int,float> tmpPair;

           tmpPair.first = tmpRltiveIdx.doc_id;
           tmpPair.second = tmpRltiveIdx.rank;
           searchResultPart.push_back(tmpPair);
        }
    searchResult.push_back(searchResultPart);
    }
    converter.putAnswers(searchResult);

}
