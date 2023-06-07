
// Created by Андрей on 22.03.2023.

#ifndef SEARCHENGINE_LIBRARY_CONVERTERJSON_H
#define SEARCHENGINE_LIBRARY_CONVERTERJSON_H
#include <iostream>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"
#include "config_exception.h"
#include <QWidget>
#pragma once
/**
 * @brief config
 * Структура конфигурации проекта
 */
struct config{
    /**
     * @brief config конструктор
     *
     * @param _name имя поискового движка
     * @param _version версия поискового движка
     * @param _mResponses мах количество ответов на запрос
     */
    config (std::string _name, std::string _version,int _mResponses);
    /**
     * @brief config конструктор со стандартным количеством ответов = 5
     *
     * @overload
     */
    config (std::string _name, std::string _version) : config(_name,_version, 5){}

    std::string name;       ///имя поискового движка
    std::string version;    ///версия поискового движка
    int max_responses;      ///мах количество ответов на запрос
};


/**
 * @brief ConverterJson
 * Класс для работы с JSON файлами
 */
class ConverterJson{
    config *myConfig;   /// указатель на конфигурацию проекта.
    nlohmann::json buffer;  /// буфер для хранения информации json формата.
    std::ifstream file;     /// поток для работы с файлами.

public:
    /// Сандартный конструктор ConverterJson
    ConverterJson ();

    /// Конструктор ConverterJson принимающий путь\имя файла конфигурации
    ConverterJson (std::string file);

    ///Конструктор копирования
    ConverterJson (const ConverterJson & oth);

    ///Конструктор присвоения
    ConverterJson& operator =(const ConverterJson &oth);

    /**
     * @brief GetTextDocuments
     * Метод для получения текста документов из ресурсных файлов,
     * перечисленных в файле конфигурации config.json
     *
     * @throws ConfigException если отутствует какой-либо файл русурсов
     * @throw ConfigException если слов в тексте больше 1000
     * @throw ConfigException если количество символов больше 100
     *
     * @exception strong
     *
     * @return возвращает вектор, по строке для каждого ресурсного файла
     */
    std::vector<std::string> GetTextDocuments();


    /**
     * @brief GetResponsesLimit
     * Метод считывает поле max_responses для определения предельного
     * количества ответов на один запрос
     *
     * @return возвращает мах число ответов
     */
    int GetResponsesLimit();

    /**
     * @brief GetRequests
     * Метод для получения запросов из файла requests.json
     *
     * @overload
     */
    std::vector<std::string> GetRequests ();

    /**
     * @brief GetRequests
     * Метод для получения запросов из файла
     *
     * @throw ConfigException если отсутствует файл запросов
     * @throw ConfigException если файл запроса пуст
     * @throw ConfigException есил количество слов в запросе больше 10 и длина слова больше 100 символов
     * @throw ConfigException если количество запросов больше 1000
     *
     * @exception strong
     *
     * @param file_name имя файла запроса
     * @return возвращает список запросов из файла
     */
    std::vector<std::string> GetRequests(const std::string& file_name);

    /**
     * @brief putAnswers
     * Метод помещающий результаты запросов в файл ответов answers.json
     *
     * @param возвращает вектор по каждому запросу с вектором пар (номер каждого ресурсного файла и его релевантность)
     */
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);

    /**
     * checkConfig
     * Метод для проверки наличия и коректности файла конфигурации
     *
     * @throw ConfigException если отсутствует файл конфигурации
     * @throw ConfigException если файл конфигурации пуст
     * @throw ConfigException если отсутсвует имя поискового движка
     * @throw ConfigException конфликт версии поискового движка
     *
     * @exception strong
     * @tparam file_name путь\имя файла конфигурации
     * @return возвращает название поискового движка или строку FAILURE при выбросе исключения
     */
    std::string checkConfig(const std::string& file_name) ;

    ///Деструктор ConverterJson
    ~ConverterJson();
};
#endif //SEARCHENGINE_LIBRARY_CONVERTERJSON_H
