#include "BaseController.hpp"
#include "crow.h"

BaseController::BaseController(std::string route,crow::SimpleApp& currentApp,DataBase& db):currentApp(currentApp),db(db){
    this->route = route;
};

void BaseController::initBaseRoute(){
    DataBase& currentConn = this->db;
    this->currentApp.route_dynamic(std::move(this->route))([currentConn](){
        return "Hello, World!";
    });
}

void BaseController::parametrizedRoute(){
     DataBase& currentConn = this->db;
    this->currentApp.route_dynamic(std::move(this->route))([currentConn](){
        return "Hello, World!";
    });
}
