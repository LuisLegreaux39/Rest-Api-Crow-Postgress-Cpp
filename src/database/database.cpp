
#include "database.hpp"

PGresult *DataBase::insert(
    std::string tableName, std::vector<std::string> columns, std::vector<std::string> values, std::string condition = "")
{
    std::string firstQueryElement = "INSERT INTO ";

    firstQueryElement = firstQueryElement.append(tableName).append("(");

    for (std::string colum : columns)
    {
        firstQueryElement = firstQueryElement.append(colum);
        if (colum != columns.back())
            firstQueryElement = firstQueryElement.append(",");
    }

    firstQueryElement = firstQueryElement.append(") VALUES (");

    for (std::string value : values)
    {
        firstQueryElement = firstQueryElement.append(value);
        if (value != values.back())
            firstQueryElement = firstQueryElement.append(",");
    }

    if (!condition.empty())
        firstQueryElement = firstQueryElement.append(condition);
    std::string resultQuery = firstQueryElement.append(");");
    std::cout << resultQuery;

    PGresult *res = PQexec(this->currentConn, resultQuery.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cerr << "INSERT failed: " << PQerrorMessage(currentConn) << std::endl;
        PQclear(res);
    }

    return res;
}

PGresult *DataBase::findAll(
    std::string tableName, std::vector<std::string> columns, std::string condition = "")
{
    std::string firstQueryElement = "SELECT ";
    if (columns.size() == 0)
        firstQueryElement.append("*");

    for (std::string colum : columns)
    {
        firstQueryElement = firstQueryElement.append(colum);
        if (colum != columns.back())
            firstQueryElement = firstQueryElement.append(",");
    }
    std::string resultQuery = firstQueryElement.append(" FROM ").append(tableName);

    if (!condition.empty())
        resultQuery = resultQuery.append(" ").append(condition);
    resultQuery = resultQuery.append(";");
    std::cout << resultQuery;

    PGresult *res = PQexec(this->currentConn, resultQuery.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cerr << "SELECT failed: " << PQerrorMessage(currentConn) << std::endl;
        PQclear(res);
    }

    return res;
}



PGresult *DataBase::findAndDelete(
    std::string tableName, std::string condition)
{
    
    std::string firstQueryElement = "DELETE FROM ";

    firstQueryElement = firstQueryElement.append(tableName).append(" ");

    firstQueryElement = firstQueryElement.append(condition);
        
    std::string resultQuery = firstQueryElement.append(";");
    std::cout << resultQuery;

    PGresult *res = PQexec(this->currentConn, resultQuery.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cerr << "Delete failed: " << PQerrorMessage(currentConn) << std::endl;
        PQclear(res);
    }

    return res;
}