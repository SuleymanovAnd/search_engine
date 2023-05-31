//
// Created by Андрей on 23.03.2023.
//

#ifndef SEARCH_ENGINE_LIB_CONFIG_EXCEPTION_H
#define SEARCH_ENGINE_LIB_CONFIG_EXCEPTION_H
#include <exception>
/**
 * @brief The ConfigException class
 * унаследованный от стандартного класса исключений, для реализации исключений в проекте
 */
class ConfigException : public std::exception{
    const char* message; ///сообщение при выбросе исключения
public:
    /**
     * @brief ConfigException конструктор класса
     * @param exception сообщение о типе исключения
     */
    ConfigException(const char*  exception) :message(exception){}
    /**
     * @brief what переопределенный метод типа исключения
     *
     * @return возвращает сообщение об исключении
     */
    const char*  what ()const noexcept override{
        return message;
    }
};
#endif //SEARCH_ENGINE_CONFIG_EXCEPTION_H
