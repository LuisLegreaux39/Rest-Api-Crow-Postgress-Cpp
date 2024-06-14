#include "BooksController.hpp"
#include <libpq-fe.h>
#include<iostream>
#include "crow.h"

void BooksController::initBaseRoute()
{
    DataBase* currentConn = &this->db;
    this->currentApp.route_dynamic(std::move(this->route)).methods(
        crow::HTTPMethod::Get,
        crow::HTTPMethod::Post 
    )([currentConn](
         const crow::request& req
    ){
        std::vector<std::string> columns{};

        if(req.method == crow::HTTPMethod::Get){

            crow::json::wvalue::list resultJsonList = crow::json::wvalue::list();

            PGresult *res = currentConn->findAll("book",columns,"ORDER BY id ASC LIMIT 200");
            
            int nRows = PQntuples(res);
            
            for (int i = 0; i < nRows; i++){
                crow::json::wvalue rowJson(crow::json::type::Object);

                rowJson["id"] = PQgetvalue(res, i, 0);
                rowJson["cover_image"] = PQgetvalue(res, i, 1);
                rowJson["name"] = PQgetvalue(res, i, 2);
                rowJson["description"] = PQgetvalue(res, i, 3);


                resultJsonList.push_back(rowJson);
            }
            PQclear(res);
            crow::json::wvalue resultJson = resultJsonList;
            return crow::response(resultJson); 
        }
        
        if(req.method == crow::HTTPMethod::Post){
            
            crow::json::rvalue requestBody = crow::json::load(req.body);
            
            if (!requestBody) return crow::response(500);
            
            int id = requestBody["id"].i();
            std::string coverImage = requestBody["cover_image"].s();
            std::string name = requestBody["name"].s();
            std::string description = requestBody["description"].s();

            std::vector<std::string> insertColumns{ "id", "cover_image","name", "description" };

            std::vector<std::string> values{ std::to_string(id), "'" +coverImage + "'","'" +name + "'","'" +description + "'"  };
            
            currentConn->insert("book",insertColumns,values, "");
        
            return crow::response(200); 
        }

        return crow::response(404);

    });
}

void BooksController::parametrizedRoute(){

    DataBase* currentConn = &this->db;
    
    std::string currentRoute = this->route.append("/<int>");

    this->currentApp.route_dynamic(std::move(currentRoute)).methods(
        crow::HTTPMethod::Get,
        crow::HTTPMethod::Delete
    )([currentConn](
        const crow::request& req, int currentId
        ){

        if(req.method == crow::HTTPMethod::Get){
            std::vector<std::string> columns{};

            crow::json::wvalue::list resultJsonList = crow::json::wvalue::list();

            std::string condition = "WHERE id=" + std::to_string(currentId); 

            PGresult *res = currentConn->findAll("book",columns,condition);

            int nRows = PQntuples(res);
                
            for (int i = 0; i < nRows; i++){
                crow::json::wvalue rowJson(crow::json::type::Object);

                rowJson["id"] = PQgetvalue(res, i, 0);
                rowJson["cover_image"] = PQgetvalue(res, i, 1);
                rowJson["name"] = PQgetvalue(res, i, 2);
                rowJson["description"] = PQgetvalue(res, i, 3);


                resultJsonList.push_back(rowJson);
            }
            PQclear(res);
            crow::json::wvalue resultJson = resultJsonList;
            return crow::response(resultJson); 
        }
        if(req.method == crow::HTTPMethod::Delete){

            std::string condition = "WHERE id=" + std::to_string(currentId); 

            currentConn->findAndDelete("book",condition);

            return crow::response(200); 
        }
        
        return crow::response(404); 
    });
}