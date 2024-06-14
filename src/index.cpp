#include <iostream>
#include "controller/BooksController/BooksController.hpp"
#include "controller/HealthController/HealthController.hpp"
#include "database/database.hpp"
#include <libpq-fe.h>

#include "config/configuration.hpp"
#include "crow.h"

using namespace std;
int main()
{
    Configuration config;
    string host = config.getDataBaseHost();
    string dbName = config.getDataBaseName();
    string user = config.getDataBaseUser();
    string password = config.getDataBasePassword();


    DataBase db(host, dbName,user,password);
    crow::SimpleApp app;

    HealthController healtController("/", app, db);
    healtController.initBaseRoute();

    BooksController controller("/books", app, db);
    controller.initBaseRoute();
    controller.parametrizedRoute();

    crow::logger::setLogLevel(crow::LogLevel::Debug);
    app.port(3000).multithreaded().run();

    return 0;
}

