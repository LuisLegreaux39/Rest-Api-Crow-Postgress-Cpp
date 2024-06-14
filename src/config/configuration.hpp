#include<string>

using namespace std;

class Configuration{
    public:
        string getDataBaseHost();
        string getDataBaseName();
        string getDataBaseUser();
        string getDataBasePassword();
        
    private:
        string getEnvVariable(string variableName);
};

