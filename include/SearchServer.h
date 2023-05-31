#ifndef SEARCHENGINE_LIBRARY_SEARCHSERVER_H
#define SEARCHENGINE_LIBRARY_SEARCHSERVER_H
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#pragma once
/**
 * @brief RelativeIndex
 * Структура индекса релевантности документа по слову
 */
struct RelativeIndex{
    size_t doc_id; /// номер документа
    float rank;    /// ранг релевантности документа

    /// Данный оператор необходим для проведения тестовых сценариев
    bool operator ==(const RelativeIndex& other) const {
    return (doc_id == other.doc_id && rank == other.rank);
}
};

class SearchServer {

public:
    /**
     * @brief SearchServer конструктор принимающий ссылкуна класс InvertedIndex,
     * чтобы SearchServer мог узнать частоту слов встречаемых в запросе
     *
     * @param idx ссылка на класс InvertedIndex
     */
    SearchServer(InvertedIndex& idx) : _index(idx){ }


    /**
     * @brief search
     * Метод обработки поисковых запросов
     *
     * @param queries_input поисковые запросы взятые из файла requests.json
     * @param responsesLimit максимальное количество ответов на запрос (стандартно = 5)
     *
     * @return возвращает отсортированный список релевантных ответов для заданных запросов
     */
    std::vector<std::vector<RelativeIndex>> search(const
    std::vector<std::string>& queries_input, int responsesLimit = 5);

private:
    InvertedIndex _index; ///копия класса InvertedIndex с частноным словарем
};
#endif // SEARCHENGINE_LIBRARY_SEARCHSERVER_H
