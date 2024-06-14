#ifndef BASECONTROLLER_HPP
#define BASECONTROLLER_HPP

#include<iostream>
#include "../../database/database.hpp"
#include "crow.h"

class BaseController{
    public:
        BaseController(std::string route, crow::SimpleApp& currentApp, DataBase& db);
        virtual void initBaseRoute();
        virtual void parametrizedRoute();

    protected:
        DataBase& db;
        crow::SimpleApp& currentApp ;
        std::string route;
};
#endif // BASECONTROLLER_HPP