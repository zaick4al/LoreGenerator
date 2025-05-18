cmake_minimum_required(VERSION 3.16)

project(LoreGenerator LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(LoreGenerator
  src/main.cpp
  src/generation/generator.h src/generation/generator.cpp

  src/loregenerator.h src/loregenerator.cpp
  src/objects/person.h src/objects/person.cpp
  src/objects/utils.h src/objects/utils.cpp
  src/generation/personsgenerator.h src/generation/personsgenerator.cpp
  src/objects/job.h src/objects/job.cpp
  src/writer/latexwriter.h src/writer/latexwriter.cpp
  src/writer/writerworker.h src/writer/writerworker.cpp
  src/generation/settlementgenerator.h src/generation/settlementgenerator.cpp
  src/objects/settlement.h src/objects/settlement.cpp
  src/objects/contry.h src/objects/contry.cpp
  src/objects/family.h src/objects/family.cpp
  src/enumssingleton.h src/enumssingleton.cpp
)

qt_add_resources(LoreGenerator "resource"
    PREFIX "/"
    FILES
        resource/names/male/Beinian.txt
        resource/names/male/Dwarven.txt
        resource/names/male/Elven.txt
        resource/names/male/Fishman.txt
        resource/names/male/Halfling.txt
        resource/names/male/Halforc.txt
        resource/names/male/Nortkin.txt
        resource/names/male/Qualtian.txt
        resource/names/male/Quarite.txt
        resource/names/male/Tiefling.txt
        resource/names/male/Vitean.txt
        resource/names/male/Irvisian.txt
        resource/names/male/Taikonian.txt

        resource/names/female/Beinian.txt
        resource/names/female/Dwarven.txt
        resource/names/female/Elven.txt
        resource/names/female/Fishman.txt
        resource/names/female/Halforc.txt
        resource/names/female/Halfling.txt
        resource/names/female/Nortkin.txt
        resource/names/female/Qualtian.txt
        resource/names/female/Quarite.txt
        resource/names/female/Tiefling.txt
        resource/names/female/Vitean.txt
        resource/names/female/Irvisian.txt
        resource/names/female/Taikonian.txt

        resource/surnames/Beinian.txt
        resource/surnames/Dwarven.txt
        resource/surnames/Elven.txt
        resource/surnames/Fishman.txt
        resource/surnames/Halforc.txt
        resource/surnames/Halfling.txt
        resource/surnames/Nortkin.txt
        resource/surnames/Qualtian.txt
        resource/surnames/Quarite.txt
        resource/surnames/Tiefling.txt
        resource/surnames/Vitean.txt
        resource/surnames/Irvisian.txt
        resource/surnames/Taikonian.txt

        resource/settlement/roots/Arabic.txt
        resource/settlement/roots/Latin.txt
        resource/settlement/roots/Dwarven.txt
        resource/settlement/topoformants/Arabic.txt
        resource/settlement/topoformants/Breton.txt
        resource/settlement/topoformants/Germanic.txt
        resource/settlement/topoformants/Dwarven.txt
        resource/npc/jobs.txt
        resource/titles/Any.txt
)

target_include_directories(LoreGenerator PRIVATE
    src/
    src/generation/
    src/objects/
)

target_link_libraries(LoreGenerator Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS LoreGenerator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
