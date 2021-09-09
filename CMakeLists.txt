# setting standards
cmake_minimum_required(VERSION 3.17)
project(MyNotes)
set(CMAKE_CXX_STANDARD 11)

# adding test cmake
add_subdirectory(test)

# setting project exec and lib
set(SRC src/Note.h src/Note.cpp
        src/Collection.h src/Collection.cpp
        src/CollectionManager.h src/CollectionManager.cpp
        src/Interface.h src/Interface.cpp
        src/FavouriteCollection.cpp src/FavouriteCollection.h)
add_library(core ${SRC})
add_executable(MyNote src/main.cpp)
target_link_libraries(MyNote core)