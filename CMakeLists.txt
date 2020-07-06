cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(UHEMesh VERSION 0.4.2)
message(STATUS "[Project] ${PROJECT_NAME}")

include(cmake/InitUCMake.cmake)
Ubpa_InitUCMake()

Ubpa_InitProject()

Ubpa_AddDep(UContainer 0.0.6)

Ubpa_AddSubDirsRec(src)

Ubpa_Export(DIRECTORIES "include")
