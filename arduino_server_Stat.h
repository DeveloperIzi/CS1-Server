#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
namespace arduino
{
    namespace server
    {
        class Stat:public drogon::HttpController<Stat>
        {
          public:
            METHOD_LIST_BEGIN
                //use METHOD_ADD to add your custom processing function here;
                METHOD_ADD(Stat::show,"/open",  Get);
                METHOD_ADD(Stat::close,"/close",Get);
                METHOD_ADD(Stat::set,"/set?statnum={1}",Post);
                METHOD_ADD(Stat::showlog,"/log", Get);
                METHOD_ADD(Stat::clearlog,"/clear",Post);
            METHOD_LIST_END
            //your declaration of processing function maybe like this:
            void show(const HttpRequestPtr &req,
                      std::function<void (const HttpResponsePtr &)> &&callback);
            void close(const HttpRequestPtr &req,
                       std::function<void (const HttpResponsePtr &)> &&callback);
            void set(const HttpRequestPtr &req,
                     std::function<void (const HttpResponsePtr &)> &&callback,
                     std::string statnum) const;
            void showlog(const HttpRequestPtr &req,
                         std::function<void (const HttpResponsePtr &)> &&callback);
            void clearlog(const HttpRequestPtr &req,
                          std::function<void (const HttpResponsePtr &)> &&callback);
        };
    }
}
