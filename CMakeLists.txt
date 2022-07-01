# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)
project ("Perfectly_balanced_search_tree")

# Включите подпроекты.
add_subdirectory ("Perfectly_balanced_search_tree")
