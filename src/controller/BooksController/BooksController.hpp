#include<iostream>
#include "../BaseController/BaseController.hpp"

class BooksController: public BaseController{
    public:
        BooksController(std::string route,crow::SimpleApp& currentApp, DataBase& db):BaseController(route, currentApp,db){};
        void initBaseRoute() override;
        void parametrizedRoute() override;
};