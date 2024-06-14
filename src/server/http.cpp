// Implementation file
#include "http.hpp"

App::App(int _port)
{
    port = _port;
};


void App::initServer()
{
    app.port(port).run();

};
