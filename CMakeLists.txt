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
)

qt_add_resources(LoreGenerator "resource"
    PREFIX "/"
    FILES
        resource/names/MaleGermanic.txt
        resource/names/FemaleGermanic.txt
        resource/names/MaleArabic.txt
        resource/names/FemaleArabic.txt
        resource/names/MaleBreton.txt
        resource/names/FemaleBreton.txt
        resource/names/MaleDwarven.txt
        resource/names/FemaleDwarven.txt
        resource/names/MaleElven.txt
        resource/names/FemaleElven.txt
        resource/settlement/roots/Arabic.txt
        resource/settlement/roots/Latin.txt
        resource/settlement/roots/Dwarven.txt
        resource/settlement/topoformants/Arabic.txt
        resource/settlement/topoformants/Breton.txt
        resource/settlement/topoformants/Germanic.txt
        resource/settlement/topoformants/Dwarven.txt
        resource/settlement/jobs/castle.txt
        resource/settlement/jobs/hugecity.txt
        resource/settlement/jobs/largecity.txt
        resource/settlement/jobs/mediumcity.txt
        resource/settlement/jobs/outpost.txt
        resource/settlement/jobs/smalltown.txt
        resource/settlement/jobs/village.txt
        resource/surnames/Arabic.txt
        resource/surnames/Breton.txt
        resource/surnames/Germanic.txt
        resource/surnames/Dwarven.txt
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
