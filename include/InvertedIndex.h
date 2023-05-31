#ifndef SEARCHENGINE_LIBRARY_INVERTEDINDEX_H
#define SEARCHENGINE_LIBRARY_INVERTEDINDEX_H
#include <map>
#include <vector>
#include <iostream>
#include <QMutex>
#include <QMutexLocker>
#include <QFuture>
#include <QtConcurrent>
#include <ConverterJSON.h>

#pragma once
/**
 * @brief Entry
 * Структура определяющая количство вхождения слова в документе
 */
struct Entry {
size_t doc_id, count; /// doc_id - Номер документа , count - Количество вхождений

/// Данный оператор необходим для проведения тестовых сценариев
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};

/**
 * @brief InvertedIndex
 * Класс хранящий и индексирующий слова документов, по которым ведется поиск
 */
class InvertedIndex {
private:    
QMutex *dictionaryAcces; /// Мьютекс для корректной работы потоков
std::map<std::string, std::vector<Entry>> freq_dictionary; /// частотный словарь слов
std::vector<std::string> docs; /// список содержимого документов

/**
 * @brief UpdateBaseForDocument
 * Метод определяет количество вхождений слова word в документе.
 * Вызывает метод UpdateFreqDictionary для каждого слова.
 *
 * @param documentNumber номер документа
 * @param document содержание документа
 */
void UpdateBaseForDocument(const size_t documentNumber,const std::string document);

/**
 * @brief UpdateFreqDictionary
 * Метод для обновления или добавления слова в частотный словарь.
 *
 * @param word слово словаря
 * @param documentNumber номер докуента
 * @param wordCount количество вхождений слова в документ
 */
void UpdateFreqDictionary (const std::string word,const size_t documentNumber, std::map <std::string,size_t> wordCount);

public:
/// конструктор класса
InvertedIndex();

/// конструктор копирования
InvertedIndex(const InvertedIndex &oth);

///Конструктор присвоения
InvertedIndex& operator = (const InvertedIndex & oth);

///Деструктор
~InvertedIndex();

/**
 * @brief UpdateDocumentBase
 * Обновить или заполнить базу документов, по которой будем совершать
 * поиск
 * @param texts_input содержимое документов
*/
void UpdateDocumentBase(std::vector<std::string> input_docs);

/**
 * @brief GetWordCount
 * Метод определяет количество вхождений слова word в загруженной базе
 * документов.
 * Вызывает метод UpdateBaseForDocument для каждого документа.
 *
 * @param word слово, частоту вхождений которого необходимо определить
 * @return возвращает подготовленный список с частотой слов
 */
std::vector<Entry> GetWordCount(const std::string& word);
};

#endif // SEARCHENGINE_LIBRARY_INVERTEDINDEX_H
