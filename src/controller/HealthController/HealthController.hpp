#include<iostream>
#include "../BaseController/BaseController.hpp"

class HealthController: public BaseController{
    public:
        HealthController(std::string route,crow::SimpleApp& currentApp, DataBase& db):BaseController(route, currentApp,db){};
         void initBaseRoute() override;
};

void HealthController::initBaseRoute(){
    this->currentApp.route_dynamic(std::move(this->route))([](){
        return "ok!";
    });
}