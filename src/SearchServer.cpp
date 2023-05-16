#include "SearchServer.h"
// функции замены ключа на значение в std::map
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

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input, int responsesLimit){

    std::vector<std::vector<RelativeIndex>> answers;

    for(auto request : queries_input ){ // выбираем по одному запросу из списка
        std::map <std::string, int> uniqueWords;
        std::string word;
        auto final_iterator = request.end();
        auto iter = request.begin();

        for (auto symbol : request){                        //делим запрос на слова
            iter ++;
            if (symbol != ' '){
                word.push_back(symbol);
                if( iter == final_iterator){                // если конец запроса, то
                    auto wordIndex = _index.GetWordCount(word);  // ищем индексы для данного слова
                    int countIndex = 0;
                        for (auto index : wordIndex){           // считаем количество всех повторений слова в документах
                            countIndex += index.count;
                        }
                        uniqueWords[word] = countIndex;         //добавляем в uniqueWords пару: (слово / подсчитанный индекс)
                        word.clear();
                }
            }else { // если не конец запроса и пробел
                auto wordIndex = _index.GetWordCount(word);  // тоже ищем индксы и добавляем в uniqueWords
                int countIndex = 0;
                    for (auto index : wordIndex){
                        countIndex += index.count;
                    }
                    uniqueWords[word] = countIndex;
                    word.clear();
            }  
        } // после разбития и нахождения всех слов с их индексом
         std::multimap <int,std::string> sortUniqueWords = flipMap(uniqueWords); // переворачиваем std::map - сортируем по значению
         std::map <std::string,std::vector<size_t>> wordDocsFound;
         std::map <std::string,bool> docsFound;
            for(auto uniqueWord :sortUniqueWords ){ // начиная с самого редкого слова проходим по всем

                auto wordDocument = _index.GetWordCount(uniqueWord.second); // ищем документы для слова
                std::vector<size_t> docs;

                for(auto document : wordDocument){  // для данного слова
                    docs.push_back(document.doc_id); // добавляем все найденные для него документы
                }
                if(docs.size()>0){ // если найден хоть один документ
                    wordDocsFound[uniqueWord.second] = docs;
                    docsFound[uniqueWord.second] = true;
                } else {
                    docsFound[uniqueWord.second] = false;
                }
            }
            std::map <size_t,size_t> absoluteRelevance;
            for(auto it = docsFound.begin(); it != docsFound.end();it++){ // проходим по всем найденым словам
               if (it->second){ // если документы для сслова найдены, то считаем релевантсноть
                   auto relevantDocs = wordDocsFound[it->first];

                        for (auto relevance : relevantDocs){
                            size_t currentRel = 0;
                            for(auto docCount :_index.GetWordCount(it->first)){
                                if (docCount.doc_id == relevance) currentRel = docCount.count;
                            }
                            if ( absoluteRelevance.count(relevance) == 0){
                                absoluteRelevance[relevance] = currentRel;
                            } else {
                                size_t previousRel =  absoluteRelevance[relevance];
                                absoluteRelevance[relevance] = previousRel + currentRel;
                            }
                        }
               }
            }
            size_t maxRelevance = 0; // ищем мах абсолютную релевантность
            for (auto relevance : absoluteRelevance ){
                if (maxRelevance < relevance.second) maxRelevance = relevance.second;
            }
            std::vector <RelativeIndex>  relativeRelevance; // считаем относительную релеванстность
            for (auto relevance : absoluteRelevance){
                RelativeIndex tempIndex;
                tempIndex.doc_id = relevance.first;
                tempIndex.rank = float(float(relevance.second)/float(maxRelevance));
                auto iteratorMax = relativeRelevance.end();
                for(auto i = relativeRelevance.begin(); i < relativeRelevance.end(); i++){
                    if(i->rank < tempIndex.rank){
                         iteratorMax = i;
                         break;
                     } else if(i->rank == tempIndex.rank && i->doc_id > tempIndex.doc_id){
                        iteratorMax = i;
                        break;
                    }


                }
               relativeRelevance.emplace(iteratorMax,tempIndex);
            }


            answers.push_back(relativeRelevance);
    }
    std::vector<std::vector<RelativeIndex>> finalAnswers;

    {    for(auto resultPart : answers ){
            int i = responsesLimit;
            std::vector<RelativeIndex> tempPart;
            for(auto relevanceDocument : resultPart){
                if(i >0){
                    tempPart.push_back(relevanceDocument);
                i--;
                }
            }
            finalAnswers.push_back(tempPart);
        }}
    return finalAnswers;
}
