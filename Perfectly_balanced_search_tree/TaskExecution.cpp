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
                push(bufferItem("������ �����!"s));
                push(bufferItem("��������� ����!"s));
                std::cin.get();
            }
            push(delimiter('-'));
            push(bufferItem("������� ����� �� 1 �� 5, � ����� ������ ����� ������:"s));
            push(delimiter('-'));
            push(bufferItem("1 -"s, "������ �������� � 100 ���������"s));
            push(bufferItem("2 -"s, "������ �������� � 200 ���������"s));
            push(bufferItem("3 -"s, "������ �������� � 300 ���������"s));
            push(bufferItem("4 -"s, "������ �������� � 400 ���������"s));
            push(bufferItem("5 -"s, "������ �������� � 500 ���������"s));
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
            std::cout << "��������! �� ������� �������� ������ �� ���� ��� ������!";
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
                push(bufferItem("������ �����!"s));
                push(bufferItem("��������� ����!"s));
                std::cin.get();
            }
            push(delimiter('-'));
            push(bufferItem("������� ����� ������� ���������� �����:"s));
            push(delimiter('-'));
            showStatusBar();
            std::cin >> find_item;
            start = true;

            if (std::cin.fail()) continue;
            
            bt = selectTreeView();
            if (bt) isSelectBase = true;
        }
        
        push(delimiter('-'));
        push(bufferItem("���� �����:"s
            , std::to_string(find_item)
            , (bt->find(find_item) ? "�������!"s : "�� �������!"s)));
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
        pushToBuffer(bufferItem("����"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("�������"s, "�������"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("1"s, "��������� ������ � ������"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("2"s, "���������� ����� � ������"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("9"s, "������� ����������"s));
        pushToBuffer(delimiter('='));
        show();
    }

}