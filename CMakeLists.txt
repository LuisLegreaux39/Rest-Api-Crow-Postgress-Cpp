cmake_minimum_required(
    VERSION 
    3.9
)

project(CPP_PROJECT)

# Project variables
set(PROJECT_NAME cpp_essentials)
set(EXECUTABLE_NAME cpp_essentials_executable)


add_executable(
    ${EXECUTABLE_NAME} # extracting executable name from context
    ./src/index.cpp

    ./src/config/configuration.hpp
    ./src/config/configuration.cpp

    ./src/controller/BaseController/BaseController.hpp
    ./src/controller/BaseController/BaseController.cpp

    ./src/controller/BooksController/BooksController.hpp
    ./src/controller/BooksController/BooksController.cpp

    ./src/controller/HealthController/HealthController.hpp

    ./src/database/database.hpp
    ./src/database/database.cpp

)

find_package(Crow REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(nlohmann_json REQUIRED)


# Linked libraries
target_link_libraries(${EXECUTABLE_NAME}  Crow::Crow)
target_link_libraries(${EXECUTABLE_NAME} PostgreSQL::PostgreSQL)
target_link_libraries(${EXECUTABLE_NAME} nlohmann_json::nlohmann_json)
