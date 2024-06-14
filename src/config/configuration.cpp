#include "configuration.hpp"
#include<iostream>

string Configuration::getEnvVariable(std::string variableName){
    const char *env_p = std::getenv(variableName.c_str());
    return env_p == NULL  ? std::string("") : std::string(env_p);
}

string Configuration::getDataBaseHost(){
    return this->getEnvVariable("DB_HOST");
}
string Configuration::getDataBaseName(){
    return this->getEnvVariable("DB_NAME");
}
string Configuration::getDataBaseUser(){
    return this->getEnvVariable("DB_USER");
}
string Configuration::getDataBasePassword(){
    return this->getEnvVariable("DB_PASSWORD");
}
