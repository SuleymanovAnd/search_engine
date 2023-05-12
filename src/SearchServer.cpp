#include "SearchServer.h"

template<typename A, typename B>
std::pair<B,A> flipPair(const std::pair<A,B> &pair)
{
    return std::pair<B,A>(pair.second, pair.first);
}

template<typename A, typename B>
std::multimap<B,A> flipMap(const std::map<A,B> &src)
{
    std::multimap<B,A> invertedMap;
    std::transform(src.begin(), src.end(), std::inserter(invertedMap, invertedMap.begin()),
                   flipPair<A,B>);
    return invertedMap;
}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input){
    std::map <std::string, int> uniqueWords;
    std::vector<std::vector<RelativeIndex>> answers;

    for(auto request : queries_input ){

        std::string word;
        auto final_iterator = request.end();
        auto iter = request.begin();

        for (auto symbol : request){
            iter ++;
            if (symbol != ' '){
                word.push_back(symbol);
                if( iter == final_iterator){
                    auto wordIndex = _index.GetWordCount(word);
                    int countIndex = 0;
                        for (auto index : wordIndex){
                            countIndex += index.count;
                        }
                        uniqueWords[word] = countIndex;
                }
            }else {
                auto wordIndex = _index.GetWordCount(word);
                int countIndex = 0;
                    for (auto index : wordIndex){
                        countIndex += index.count;
                    }
                    uniqueWords[word] = countIndex;
            }
        }
         std::map <int,std::string> sortUniqueWords = flipMap(uniqueWords);
            for(auto uniqueWord :sortUniqueWords ){
                auto wordDocument = _index.GetWordCount(uniqueWord.second);
                std::vector<size_t> docs;
                std::map <std::string,std::vector<size_t>> wordDocsFound;
                std::map <std::string,bool> docsFound;
                for(auto document : wordDocument){
                    docs.push_back(document.doc_id);
                }
                if(docs.size()>0){
                    wordDocsFound[uniqueWord] = docs;
                    docsFound[uniqueWord] = true;
                } else {
                    docsFound[uniqueWord] = false;
                }
            }
    }

}
