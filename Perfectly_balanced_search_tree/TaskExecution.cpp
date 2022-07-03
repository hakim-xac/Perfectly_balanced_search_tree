#include "TaskExecution.h"
#include <random>

namespace KHAS {

    BinaryTree* TaskExecution::create(int count_tree)
    {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dist(-1000000, 1000000);

        BinaryTree * temp_tree{ new BinaryTree(dist(gen)) };

        for (int i{ 1 }; i < count_tree; ++i) {
            temp_tree->insert(dist(gen));
        }
        
        return temp_tree;
    }

    BinaryTree* TaskExecution::selectTree(int index) const
    {
        BinaryTree* bt{ nullptr };
        switch (index) {
        case 1:     bt = tree100_;  break;
        case 2:     bt = tree200_;  break;
        case 3:     bt = tree300_;  break;
        case 4:     bt = tree400_;  break;
        case 5:     bt = tree500_;  break;
        default:    bt = nullptr;
        }
        return bt;
    }

    void TaskExecution::functionLaunch()
    {
        switch (getActiveCommand()) {
        case InputCommand::Print100:    print100();     break;
        case InputCommand::Print200:    print200();     break;
        case InputCommand::Print300:    print300();     break;
        case InputCommand::Print400:    print400();     break;
        case InputCommand::Print500:    print500();     break;
        case InputCommand::FindItem:    findInTree();   break;
        case InputCommand::Exit:        quit();         break;
        default: break;
        }
        clearActiveCommand();
    }

    TaskExecution
        ::TaskExecution()
    : Interface()
    , tree100_(create(100))
    , tree200_(create(200))
    , tree300_(create(300))
    , tree400_(create(400))
    , tree500_(create(500))	{}

    TaskExecution::~TaskExecution()
    {
        delete tree100_;
        delete tree200_;
        delete tree300_;
        delete tree400_;
        delete tree500_;
    }

    void TaskExecution::space() const
    {
        pushToBuffer(delimiter(' '));
    }

    void TaskExecution::print100() const
    {
        using namespace std::literals;
        print("Данные о дереве с количеством элементов 100"s, tree100_);
    }

    void TaskExecution::print200() const
    {
        using namespace std::literals;
        print("Данные о дереве с количеством элементов 200"s, tree200_);
    }

    void TaskExecution::print300() const
    {
        using namespace std::literals;
        print("Данные о дереве с количеством элементов 300"s, tree300_);
    }

    void TaskExecution::print400() const
    {
        using namespace std::literals;
        print("Данные о дереве с количеством элементов 400"s, tree400_);
    }

    void TaskExecution::print500() const
    {
        using namespace std::literals;
        print("Данные о дереве с количеством элементов 500"s, tree500_);
    }

    void TaskExecution::findInTree()
    {
        using namespace std::literals;
        int find_item{};
        int index{};
        bool start{};
        bool isSelectBase{};
        BinaryTree* bt{ nullptr };
        while (!isSelectBase || !start || std::cin.fail()) {
            std::cin.clear();
            if (start) {
                push(bufferItem("Ошибка ввода!"s));
                push(bufferItem("Повторите ввод!"s));
                std::cin.get();
            }
            push(delimiter('-'));
            push(bufferItem("Введите число которое необходимо найти:"s));
            push(delimiter('-'));
            showStatusBar();
            std::cin >> find_item;
            push(delimiter('-'));
            push(bufferItem("Введите число от 1 до 5, в каком дереве хотим искать:"s));
            push(delimiter('-'));
            push(bufferItem("1 -"s, "дерево размером в 100 элементов"s));
            push(bufferItem("2 -"s, "дерево размером в 200 элементов"s));
            push(bufferItem("3 -"s, "дерево размером в 300 элементов"s));
            push(bufferItem("4 -"s, "дерево размером в 400 элементов"s));
            push(bufferItem("5 -"s, "дерево размером в 500 элементов"s));
            push(delimiter('-'));
            showStatusBar();
            std::cin >> index;
            start = true;
            if (bt = selectTree(index)) isSelectBase = true;
            
        }
        
        push(delimiter('-'));
        push(bufferItem("Выше число:"s
            , std::to_string(find_item)
            , (bt->find(find_item) ? "НАЙДЕНО!"s : "НЕ НАЙДЕНО!"s)));
        push(delimiter('-'));
        std::cin.get();
    }

    void TaskExecution::quit() const
    {
        system("cls");
        exit(0);
    }

    void TaskExecution::showMenu() const
    {
        using namespace std::literals;

        pushToBuffer(delimiter('='));
        pushToBuffer(bufferItem("Меню"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("Клавиша"s, "Команда"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("1"s, "Распечать данные о дереве из 100 элементов"s));
        pushToBuffer(bufferItem("2"s, "Распечать данные о дереве из 200 элементов"s));
        pushToBuffer(bufferItem("3"s, "Распечать данные о дереве из 300 элементов"s));
        pushToBuffer(bufferItem("4"s, "Распечать данные о дереве из 400 элементов"s));
        pushToBuffer(bufferItem("5"s, "Распечать данные о дереве из 500 элементов"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("6"s, "Произвести поиск в дереве"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("9"s, "Закрыть приложение"s));
        pushToBuffer(delimiter('='));
        show();
    }

}