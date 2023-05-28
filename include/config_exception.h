//
// Created by Андрей on 23.03.2023.
//

#ifndef SEARCH_ENGINE_LIB_CONFIG_EXCEPTION_H
#define SEARCH_ENGINE_LIB_CONFIG_EXCEPTION_H
#include <exception>
class ConfigException : public std::exception{
    const char* message;
public:
    ConfigException(const char*  exception) :message(exception){}

    const char*  what ()const noexcept override{
        return message;
    }
};
#endif //SEARCH_ENGINE_CONFIG_EXCEPTION_H
