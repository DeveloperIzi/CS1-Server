#include <fstream>
#include "arduino_server_Stat.h"
using namespace arduino::server;
//add definition of your processing function here

int stat = 0;

void writeLog(std::string str)
{
    time_t timer = time(NULL);
    struct tm* t = localtime(&timer);
    FILE *logFile = fopen("LogFile","a");
    fprintf(logFile,"%04d-%02d-%02d %02d:%02d:%02d %s(mode : %d)\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec, str.c_str(), stat);
    fclose(logFile);
}

void Stat::show(const HttpRequestPtr &req,
                std::function<void (const HttpResponsePtr &)> &&callback)
{
    writeLog("Open");
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(drogon::k200OK);
    resp->setContentTypeCode(drogon::CT_TEXT_PLAIN);
    resp->setBody(std::to_string(stat));
    callback(resp);
}

void Stat::close(const HttpRequestPtr &req,
                std::function<void (const HttpResponsePtr &)> &&callback)
{
    writeLog("Close");
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(drogon::k200OK);
    resp->setContentTypeCode(drogon::CT_TEXT_PLAIN);
    resp->setBody(std::to_string(stat));
    callback(resp);
}

void Stat::set(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback,
               std::string statnum) const
{
    try
    {
        stat = std::stoi(statnum);
    } catch(int expn){
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k200OK);
        resp->setContentTypeCode(drogon::CT_TEXT_PLAIN);
        resp->setBody("error");
        callback(resp);
    }
    writeLog("Set");
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(drogon::k200OK);
    resp->setContentTypeCode(drogon::CT_TEXT_PLAIN);
    resp->setBody(statnum);
    resp->setBody(std::to_string(stat));
    callback(resp);
}

void Stat::showlog(const HttpRequestPtr &req,
                   std::function<void (const HttpResponsePtr &)> &&callback)
{
    std::ifstream logFile("LogFile");
    std::string logStr;
    if(logFile.is_open()) {
        logFile.seekg(0, std::ios::end);
        int size = logFile.tellg();
        logStr.resize(size);
        logFile.seekg(0, std::ios::beg);
        logFile.read(&logStr[0],size);
    }
    logFile.close();
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(drogon::k200OK);
    resp->setContentTypeCode(drogon::CT_TEXT_PLAIN);
    resp->setBody(logStr);
    callback(resp);
}

void Stat::clearlog(const HttpRequestPtr &req,
                    std::function<void (const HttpResponsePtr &)> &&callback)
{
    time_t timer = time(NULL);
    struct tm* t = localtime(&timer);
    FILE *logFile = fopen("LogFile","w");
    fprintf(logFile,"%04d-%02d-%02d %02d:%02d:%02d Log Cleared\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
    fclose(logFile);

    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(drogon::k200OK);
    resp->setContentTypeCode(drogon::CT_TEXT_PLAIN);
    resp->setBody("Log Cleared");
    callback(resp);
}