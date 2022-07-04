#include "TaskExecution.h"
#include <random>

namespace KHAS {

    BinaryTree* TaskExecution::create(int count_tree)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dist(-1000000, 1000000);

        BinaryTree * temp_tree{ new (std::nothrow) BinaryTree(dist(gen)) };
        if (!temp_tree) return nullptr;
        for (int i{ 1 }; i < count_tree; ++i) {
            temp_tree->insert(dist(gen));
        }
        
        return temp_tree;
    }

    bool TaskExecution::checkIsTree()
    {
        return (sdpTree100_ != nullptr
            && sdpTree200_ != nullptr
            && sdpTree300_ != nullptr
            && sdpTree400_ != nullptr
            && sdpTree500_ != nullptr);
    }

    BinaryTree* TaskExecution::selectTree(int index) const
    {
        BinaryTree* bt{ nullptr };
        switch (index) {
        case 1:     bt = sdpTree100_;  break;
        case 2:     bt = sdpTree200_;  break;
        case 3:     bt = sdpTree300_;  break;
        case 4:     bt = sdpTree400_;  break;
        case 5:     bt = sdpTree500_;  break;
        default:    bt = nullptr;
        }
        return bt;
    }

    BinaryTree* TaskExecution::selectTreeView()
    {
        using namespace std::literals;
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

        std::cin.get();
        return bt;
    }

    void TaskExecution::functionLaunch()
    {
        if (!checkIsTree()) {
            system("cls");
            std::cout << "Внимание! не удалось выделить память из кучи под данные!";
            exit(1);
        }

        switch (getActiveCommand()) {
        case InputCommand::Print:       printView();    break;
        case InputCommand::FindItem:    findInTree();   break;
        case InputCommand::Exit:        quit();         break;
        default: break;
        }
        clearActiveCommand();
    }

    TaskExecution
        ::TaskExecution()
    : Interface()
    , sdpTree100_(create(100))
    , sdpTree200_(create(200))
    , sdpTree300_(create(300))
    , sdpTree400_(create(400))
    , sdpTree500_(create(500))	{}

    TaskExecution::~TaskExecution()
    {
        delete sdpTree100_;
        delete sdpTree200_;
        delete sdpTree300_;
        delete sdpTree400_;
        delete sdpTree500_;
    }

    void TaskExecution::space() const
    {
        pushToBuffer(delimiter(' '));
    }

    void TaskExecution::findInTree()
    {
        using namespace std::literals;
        int find_item{};
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
            start = true;

            if (std::cin.fail()) continue;
            
            bt = selectTreeView();
            if (bt) isSelectBase = true;
        }
        
        push(delimiter('-'));
        push(bufferItem("Выше число:"s
            , std::to_string(find_item)
            , (bt->find(find_item) ? "НАЙДЕНО!"s : "НЕ НАЙДЕНО!"s)));
        push(delimiter('-'));
    }

    void TaskExecution::quit() const
    {
        system("cls");
        exit(0);
    }

    void TaskExecution::printView()
    {
        BinaryTree* bt{ selectTreeView() };
        print(bt);
    }

    void TaskExecution::showMenu() const
    {
        using namespace std::literals;

        pushToBuffer(delimiter('='));
        pushToBuffer(bufferItem("Меню"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("Клавиша"s, "Команда"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("1"s, "Распечать данные о дереве"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("2"s, "Произвести поиск в дереве"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("9"s, "Закрыть приложение"s));
        pushToBuffer(delimiter('='));
        show();
    }

}