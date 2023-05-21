# search_engine

- [Описание проекта](#описание-проекта)
- [Описание стека используемых технологий](#описание-стека-используемых-технологий)
- [Запуск проекта](#запуск-проекта)



## Описание проекта
   **Тема проекта** — *«Реализация системы поиска по корпоративному порталу компании*».\
\
    Проект представляет собой консольное приложение, осуществляющее поиск наиболее релевантных документов по запросу и имеющее возможность настройки через файлы формата
   JSON. \
    \
   Принцип работы:
1. В конфигурационном файле перед запуском приложения задаются названия
  файлов, по которым движок будет осуществлять поиск.
2. Поисковый движок самостоятельно обходит все файлы и
  индексирует их так, чтобы потом по любому поисковому запросу находить наиболее
  релевантные документы.
3. Пользователь задаёт запрос через JSON-файл requests.json. Запрос — это
  набор слов, по которым нужно найти документы.
4. Запрос трансформируется в список слов.
5. В индексе ищутся те документы, на которых встречаются все эти слова.
6. Результаты поиска ранжируются, сортируются и отдаются пользователю,
  максимальное количество возможных документов в ответе задаётся в
  конфигурационном файле.
7. В конце программа формирует файл answers.json, в который записывает
  результаты поиска.

## Описание стека используемых технологий
**Язык программирования :** С++\
**Система сборки:** CMake\
**IDE:** CLion 2022.1, QtCreator 9.0.1\
**Используемый компилятор:** mingw81_64\
**Дополнительные библиотеки:** 
- [nlohmann-json](https://github.com/nlohmann/json)
- Qt5::Core
- Qt5::Gui
- Qt5::Widgets
- Qt5::Test
- Qt5::Concurrent

## Запуск проекта
В системных переменных PATH необходимо указать путь к библиотекам Qt.\
Для запуска скомпилируйте программу и запуститие search_engine_m.exe
из терминала. \
Команда запускающая поиск - "start"\
Для корректной работы программы необходимо указать файлы по которым будет вестись поиск в config/config.json в поле "files":\
Запросы пишутся в файле requests/requests.json.\
Файлы, по которым будет вестись поиск, расположить в папке resources.


