# CMakeList.txt: проект CMake для Perfectly_balanced_search_tree; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Perfectly_balanced_search_tree "Perfectly_balanced_search_tree.cpp" "Perfectly_balanced_search_tree.h" "Interface.h" "Interface.cpp" "TaskExecution.h" "TaskExecution.cpp" "Node.h" "BinaryTree.h" "BinaryTree.cpp" "Node.cpp" "Enums.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
