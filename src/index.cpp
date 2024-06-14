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

    // // const char *conninfo = "host=host.docker.internal dbname=catalog_book_db user=postgres password=postgres";
    // Initialize array
    // std::vector<std::string>  colour{ "columna 1", "columna 2","columna3"};
    // std::vector<std::string>  values{ "1", "'hola'","'hola'"};
    // db.select("books",colour);
    // db.insert("books",colour,values);
    // PGconn *conn = PQconnectdb(conninfo);

    // if (PQstatus(conn) != CONNECTION_OK)
    // {
    //     std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
    //     PQfinish(conn);
    //     return 1;
    // }
    // crow::SimpleApp app;

    // BooksController controller("/books", app, conn);
    // controller.initBaseRoute();
    // controller.parametrizedRoute();
    // controller.get();
    // controller.getId();
    // controller.create();

    // crow::logger::setLogLevel(crow::LogLevel::Debug);
    // app.port(3000).multithreaded().run();

    return 0;
}

// Function to convert PGresult to JSON
// crow::json::wvalue PGresultToJson(PGresult *res)
// {
//     crow::json::wvalue::list resultJson = crow::json::wvalue::list(); // Initialize as a list (array)

//     int nFields = PQnfields(res);
//     int nRows = PQntuples(res);

//     crow::json::wvalue::list listRows; // Create a list to hold the rows
//     for (int i = 0; i < nRows; ++i)
//     {
//         crow::json::wvalue rowJson;
//         for (int j = 0; j < nFields; ++j)
//         {
//             const char *fieldName = PQfname(res, j);
//             const char *fieldValue = PQgetvalue(res, i, j);
//             rowJson[fieldName] = fieldValue;
//         }
//         listRows.push_back(std::move(rowJson)); // Add the row to the list
//     }

//     resultJson = std::move(listRows); // Set the resultJson to the list of rows
//     return resultJson;
// }

// int main(){
//     const char *conninfo = "host=host.docker.internal dbname=catalog_book_db user=postgres password=postgres";
//     PGconn *conn = PQconnectdb(conninfo);

//     if (PQstatus(conn) != CONNECTION_OK)
//     {
//         std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
//         PQfinish(conn);
//         return 1;
//     }
//     PGresult *res = PQexec(conn, "SELECT * FROM book;");

//     if (PQresultStatus(res) != PGRES_TUPLES_OK)
//     {
//         std::cerr << "SELECT failed: " << PQerrorMessage(conn) << std::endl;
//         PQclear(res);
//     }

//     int nCols = PQnfields(res);
//    printf("There are %d columns:", nCols);
//     for(int i = 0; i < nCols; i++)
//     {
//         string name = PQfname(res, i);
//         printf(" %s", name.c_str());
//     }
//     printf("\n");
//     int nrows = PQntuples(res);
//     for (int i = 0; i < nrows; i++)
//     {
//        char *id = PQgetvalue(res, i, 0);
//        char *cover_image = PQgetvalue(res, i, 1);
//        char *name = PQgetvalue(res, i, 2);
//     //    char *description = PQgetvalue(res, i, 0);

//        printf("Id: %s, Name: %s, Image: %s \n",id, name, cover_image);
//     }
//     PQclear(res);

//   crow::SimpleApp app;

//   CROW_ROUTE(app, "/books")
//   ([conn](){
//        PGresult *res = PQexec(conn, "SELECT * FROM book;");

//         if (PQresultStatus(res) != PGRES_TUPLES_OK) {
//             std::cerr << "SELECT failed: " << PQerrorMessage(conn) << std::endl;
//             PQclear(res);
//             return crow::response(500, "Database query failed");
//         }

//         crow::json::wvalue resultJson = PGresultToJson(res);
//         PQclear(res);
//         return crow::response(resultJson);
//    });

//   app.port(3000).multithreaded().run();

//     const char conninfo[] = "host=host.docker.internal dbname=catalog_book_db user=postgres password=postgres";
//   PGconn *conn = PQconnectdb(conninfo);
//   if (PQstatus(conn) != CONNECTION_OK)
//   {
//     fprintf(stderr, "%s[%d]: Connection to database failed: %s\n",
//             __FILE__, __LINE__, PQerrorMessage(conn));
//     PQfinish(conn);
//     return 1;
//   }
//   else
//   {
//     printf("Connection to database succeed.\n");
//   }

//  PGresult *res = NULL;
//  res = PQexec(conn, "select * from book;");

//  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
//     std::cout << "Select failed: " << PQresultErrorMessage(res) << std::endl;
//  } else {
//     std::cout << "Get " << PQntuples(res) << "tuples, each tuple has " << PQnfields(res) << "fields" << std::endl;
//     // print column name
//     for (int i = 0; i < PQnfields(res); i++) {
//       std::cout << PQfname(res, i) << "              ";
//     }
//     std::cout << std::endl;
//       // print column values
//         for (int i = 0; i < PQntuples(res); i++) {
//           for (int j = 0; j < PQnfields(res); j++) {
//             std::cout << PQgetvalue(res, i, j) << "   ";
//           }
//           std::cout << std::endl;
//         }
//       }
//       PQclear(res);

// Configuration config;
// string dataBaseUrL = config.getDataSourceUrl();

// connection string
// postgresql://postgres@127.0.0.1:5432/catalog_book_db
//  const char conninfo[] =
// 		"host=host.docker.internal dbname=catalog_book_db user=postgres password=postgres";
//  PGconn *conn = PQconnectdb(conninfo);
//  if(PQstatus(conn) != CONNECTION_OK){
//        fprintf(stderr, "%s[%d]: Connection to database failed: %s\n",
// 		__FILE__, __LINE__, PQerrorMessage(conn));
// 	PQfinish(conn);
//   return 1;
//  }else {
// 	printf("Connection to database succeed.\n");
// }

// PQfinish(conn);
//     return 0;
// }