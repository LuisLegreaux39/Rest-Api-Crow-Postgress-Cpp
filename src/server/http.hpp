#include "crow.h"

#pragma once

class App
{
private:
    int port;
    crow::SimpleApp app;

public:
    App(int _port);
    void initServer();
};