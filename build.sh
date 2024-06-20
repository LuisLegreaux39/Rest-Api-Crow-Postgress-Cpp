#/bin/bash
export DB_HOST=db DB_NAME=cpp_library DB_USER=postgres DB_PASSWORD=postgres
conan profile detect
conan install . --output-folder=build --build=missing
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
./cpp_essentials_executable 