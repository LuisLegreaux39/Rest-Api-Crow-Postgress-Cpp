#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <libpq-fe.h>
#include <vector>

class DataBase{
public:
    DataBase(
        std::string _host,
        std::string _dbname,
        std::string _user,
        std::string _password)
    {
        std::string conninfo ;
        conninfo =  conninfo.append("host=").append(_host).append(" ").append("dbname=").append(_dbname).append(" ").append("user=").append(_user).append(" ").append("password=").append(_password);
        this->currentConn = PQconnectdb(conninfo.c_str());
    };

    PGresult* findAll(std::string tableName, std::vector<std::string> columns, std::string condition);
    PGresult* insert(std::string tableName, std::vector<std::string> columns, std::vector<std::string> values, std::string condition);
    PGresult* findAndDelete(std::string tableName, std::string condition);

private:
    PGconn *currentConn;
};

#endif // DATABASE_HPP