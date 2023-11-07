cmake_minimum_required(VERSION 3.26)
project(SplendorDuel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.6.0\\msvc2019_64\\lib\\cmake")

include_directories(.)
include_directories(x64/Debug/uic)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(SplendorDuel
        x64/Debug/moc/moc_SplendorDuel.cpp
        x64/Debug/rcc/qrc_SplendorDuel.cpp
        x64/Debug/uic/ui_SplendorDuel.h
        Bag.cpp
        Bag.h
        Board.cpp
        Board.h
        Card.cpp
        Card.h
        DrawPile.cpp
        DrawPile.h
        GameFactory.cpp
        GameFactory.h
        Gemmes.cpp
        Gemmes.h
        main.cpp
        MyException.h
        SplendorDuel.cpp
        SplendorDuel.h
        SplendorDuel.qrc)

target_link_libraries(SplendorDuel Qt5::Widgets)