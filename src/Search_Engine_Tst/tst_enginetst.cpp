#include <QtTest>

// add necessary includes here
#include <ConverterJSON.h>
#include <InvertedIndex.h>


class EngineTst : public QObject
{
    Q_OBJECT

public:
    EngineTst();
    ~EngineTst();

private slots:

    void TestCheckConfig ();
    void TestGetTextDocuments();
    void TestGetResponsesLimit();
    void TestPutAnswers();
    void TestGetRequests();
    void TestInvertedIndexBasic();
    void TestInvertedIndexBasic2();
    void TestInvertedIndexMissingWord ();
};

EngineTst::EngineTst()
{

}
EngineTst::~EngineTst()
{

}
// #################################### Тестирование класса ConverterJson ################################################

void EngineTst::TestCheckConfig() {
        // создание тестовых файлов
    nlohmann::json testFileContent;
    std::ofstream testFile ("config_test1.json"); // файл с ошибкой в названии "config"
    testFileContent["configs"]["name"] = "SkillboxSearchEngine";
    testFileContent["configs"]["version"] = "0.1";
    testFileContent["configs"]["max_responses"] = 5;
    testFileContent["files"] = {"../resources/file001.txt",
                                "../resources/file002.txt",
                                "../resources/file003.txt"};
    testFile << testFileContent;
    testFile.close();
    testFileContent.clear();

    testFile.open("config_test2.json"); // файл с отсутствующим именем
    testFileContent["config"]["version"] = "0.1";
    testFileContent["config"]["max_responses"] = 3;
    testFileContent["files"] = {"../resources/file001.txt",
                                "../resources/file002.txt",
                                "../resources/file003.txt"};
    testFile << testFileContent;
    testFile.close();

    testFile.open("config_test3.json"); // файл с неправильной версией
    testFileContent["config"]["name"] = "SkillboxSearchEngine";
    testFileContent["config"]["version"] = "0.2";
    testFile << testFileContent;
    testFile.close();

    testFile.open("config.json"); // стандартный конфиг
    testFileContent["config"]["version"] = "0.1";
    testFileContent["config"]["max_responses"] = 5;
    testFile << testFileContent;
    testFile.close();
    // тестирование
    ConverterJson converter;
 QVERIFY2(converter.checkConfig("c.json")== "FAILURE","config file is missing -");
 QVERIFY2(converter.checkConfig("config_test1.json")== "FAILURE", "config is empty -");
 QVERIFY2(converter.checkConfig("config_test2.json")=="FAILURE", "config \"name\" is empty -");
 QVERIFY2(converter.checkConfig("config_test3.json")=="FAILURE", "version incorrect -");
 QVERIFY2(converter.checkConfig("config.json")!="FAILURE", "config fail");
}
void EngineTst::TestGetTextDocuments()
{
    ConverterJson converter ("config_test1.json");
    QVERIFY2(converter.GetTextDocuments().size() == 3, "unable to get list of documents" );
    QVERIFY2(converter.GetTextDocuments().front() == "../resources/file001.txt","incorrect reading of file names");
}
void EngineTst::TestGetResponsesLimit(){
    ConverterJson converter ("config_test2.json");
    QVERIFY2(converter.GetResponsesLimit() == 3, "wrong reading Responses Limit");

}
void EngineTst::TestPutAnswers(){
    nlohmann::json testFile;
    std::vector<std::vector<std::pair<int, float>>> answers = {{{10,15.3},{13,12.2}}, {{5,3.2}},{}};
    ConverterJson converter;
    converter.putAnswers(answers);
    std::ifstream file ("answers.json");
    file >> testFile;
    file.close();

    QVERIFY2(testFile["answers"]["requests0"]["result"] == true,"requsts 0 is empty");
    QVERIFY2(testFile["answers"]["requests0"]["relevance"].size() == 2, "uncorrect size in requsts 0 ");
    QVERIFY2(testFile["answers"]["requests2"]["result"] == false, "request 2 does not empty");
}
void EngineTst::TestGetRequests(){
    nlohmann::json testFileContent;
    std::ofstream testFile ("requests.json");
    testFileContent["requests"] = {  "some words..","some words..","some words..","some words.."};
    testFile << testFileContent;
    testFile.close();

     ConverterJson converter;
    QVERIFY2(converter.GetRequests("requests.json").size() == 4, "requests file is empty");
}
// ############################### Окончание тестирование класса ConverterJson ###########################################

void EngineTst::TestInvertedIndexBasic() {
    const std::vector<std::string> docs = {"london is the capital of great britain",
                             "big ben is the nickname for the Great bell of the striking clock"};
    const std::vector<std::string> requests = {"london", "the"};
    const std::vector<std::vector<Entry>> expected = {{{0, 1}}, {{0, 1}, {1, 3}}};

        std::vector<std::vector<Entry>> result;
        InvertedIndex idx;
        idx.UpdateDocumentBase(docs);
            for(auto& request : requests) {
                std::vector<Entry> word_count = idx.GetWordCount(request);
                result.push_back(word_count);
            }

            QVERIFY2 (result == expected,"TestBasic Failed");

}
void EngineTst::TestInvertedIndexBasic2(){
    const std::vector<std::string> docs = {
        "milk milk milk milk water water water",
        "milk water water",
        "milk milk milk milk milk water water water water water",
        "americano cappuccino"};
    const std::vector<std::string> requests = {"milk", "water", "cappuccino"};
    const std::vector<std::vector<Entry>> expected = {{{0, 4}, {1, 1}, {2, 5}}, {{0, 3}, {1, 2}, {2, 5}}, {{3, 1}}};

    std::vector<std::vector<Entry>> result;
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    for(auto& request : requests) {
        std::vector<Entry> word_count = idx.GetWordCount(request);
        result.push_back(word_count);
    }

        QVERIFY2 (result == expected,"TestBasic2 Failed");

}
void EngineTst::TestInvertedIndexMissingWord (){
    const std::vector<std::string> docs = {"a b c d e f g h i j k l","statement"};
    const std::vector<std::string> requests = {"m", "statement"};
    const std::vector<std::vector<Entry>> expected = {{},{{1, 1}}};

    std::vector<std::vector<Entry>> result;
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    for(auto& request : requests) {
        std::vector<Entry> word_count = idx.GetWordCount(request);
        result.push_back(word_count);
    }

        QVERIFY2 (result == expected,"MissingWord Failed");

}

QTEST_APPLESS_MAIN(EngineTst)

#include "tst_enginetst.moc"
