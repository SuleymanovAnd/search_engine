#include <QtTest>

// add necessary includes here
#include <ConverterJSON.h>

class EngineTst : public QObject
{
    Q_OBJECT

public:
    EngineTst();
    ~EngineTst();

private slots:
    void TestGetTextDocuments();
    void TestCheckConfig ();
    void TestGetResponsesLimit();
    void TestPutAnswers();
    void TestGetRequests();

};

EngineTst::EngineTst()
{

}

EngineTst::~EngineTst()
{

}
// #################################### Тестирование класса ConverterJson ################################################
void EngineTst::TestGetTextDocuments()
{
    ConverterJson converter ("config_test1.json");
    QVERIFY2(converter.GetTextDocuments().size() == 3, "unable to get list of documents" );
    QVERIFY2(converter.GetTextDocuments().front() == "../resources/file001.txt","incorrect reading of file names");
}
void EngineTst::TestCheckConfig() {
    ConverterJson converter;
 QVERIFY2(converter.checkConfig("c.json")== "FAILURE","config file is missing -");
 QVERIFY2(converter.checkConfig("config_test1.json")== "FAILURE", "config is empty -");
 QVERIFY2(converter.checkConfig("config_test2.json")=="FAILURE", "config \"name\" is empty -");
 QVERIFY2(converter.checkConfig("config_test3.json")=="FAILURE", "version incorrect -");
 QVERIFY2(converter.checkConfig("config.json")!="FAILURE", "config fail");
}
void EngineTst::TestGetResponsesLimit(){
    ConverterJson converter ("config_test2.json");
    QVERIFY2(converter.GetResponsesLimit() == 3, "wrong reading Responses Limit");

}

void EngineTst::TestPutAnswers(){
    nlohmann::json tstFile;
    std::vector<std::vector<std::pair<int, float>>> answers = {{{10,15.3},{13,12.2}}, {{5,3.2}},{}};
    ConverterJson converter;
    converter.putAnswers(answers);
    std::ifstream file ("answers.json");
    file >> tstFile;


    QVERIFY2(tstFile["answers"]["requests0"]["result"] == true,"requsts 0 is empty");
    QVERIFY2(tstFile["answers"]["requests0"]["relevance"].size() == 2, "uncorrect size in requsts 0 ");
    QVERIFY2(tstFile["answers"]["requests2"]["result"] == false, "request 2 does not empty");
}
void EngineTst::TestGetRequests(){
     ConverterJson converter;
    QVERIFY2(converter.GetRequests("requests.json").size() == 4, "requests file is empty");
}
// ############################### Окончание тестирование класса ConverterJson ###########################################



QTEST_APPLESS_MAIN(EngineTst)

#include "tst_enginetst.moc"
