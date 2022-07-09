#include "TaskExecution.h"

namespace KHAS {
    std::pair<BinaryTree*, BinaryTree*> TaskExecution::create(int count_tree)
    {
                
        BinaryTree* sdpTree{ new (std::nothrow) BinaryTree(count_tree) };

        if (!sdpTree) return { nullptr, nullptr };

        BinaryTree* isdpTree{ new (std::nothrow) BinaryTree(sdpTree) };

        if (!isdpTree) {
            sdpTree->deleteTree();
            return { nullptr, nullptr };
        }

        return { sdpTree, isdpTree };
    }

    bool TaskExecution::checkIsTree()
    {
        return (sdpTree100_ != nullptr && sdpTree200_ != nullptr
            && sdpTree300_ != nullptr && sdpTree400_ != nullptr
            && sdpTree500_ != nullptr && isdpTree100_ != nullptr
            && isdpTree200_ != nullptr && isdpTree300_ != nullptr
            && isdpTree400_ != nullptr && isdpTree500_ != nullptr
            );
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
        case 6:     bt = isdpTree100_;  break;
        case 7:     bt = isdpTree200_;  break;
        case 8:     bt = isdpTree300_;  break;
        case 9:     bt = isdpTree400_;  break;
        case 0:     bt = isdpTree500_;  break;
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
            push(bufferItem("������� ����� �� 0 �� 9, � ����� ������ ����� ������:"s));
            push(delimiter('-'));
            push(bufferItem("1 -"s, "��� ������ �������� � 100 ���������"s));
            push(bufferItem("2 -"s, "��� ������ �������� � 200 ���������"s));
            push(bufferItem("3 -"s, "��� ������ �������� � 300 ���������"s));
            push(bufferItem("4 -"s, "��� ������ �������� � 400 ���������"s));
            push(bufferItem("5 -"s, "��� ������ �������� � 500 ���������"s));
            push(delimiter('-'));
            push(bufferItem("6 -"s, "���� ������ �������� � 100 ���������"s));
            push(bufferItem("7 -"s, "���� ������ �������� � 200 ���������"s));
            push(bufferItem("8 -"s, "���� ������ �������� � 300 ���������"s));
            push(bufferItem("9 -"s, "���� ������ �������� � 400 ���������"s));
            push(bufferItem("0 -"s, "���� ������ �������� � 500 ���������"s));
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
    , sdpTree100_(nullptr), sdpTree200_(nullptr)
    , sdpTree300_(nullptr), sdpTree400_(nullptr)
    , sdpTree500_(nullptr), isdpTree100_(nullptr)
    , isdpTree200_(nullptr), isdpTree300_(nullptr)
    , isdpTree400_(nullptr), isdpTree500_(nullptr) {

        std::tie(sdpTree100_, isdpTree100_) = create(100);
        std::tie(sdpTree200_, isdpTree200_) = create(200);
        std::tie(sdpTree300_, isdpTree300_) = create(300);
        std::tie(sdpTree400_, isdpTree400_) = create(400);
        std::tie(sdpTree500_, isdpTree500_) = create(500);

    }

    TaskExecution::~TaskExecution()
    {
        sdpTree100_->deleteTree();
        sdpTree200_->deleteTree();
        sdpTree300_->deleteTree();
        sdpTree400_->deleteTree();
        sdpTree500_->deleteTree();
        isdpTree100_->deleteTree();
        isdpTree200_->deleteTree();
        isdpTree300_->deleteTree();
        isdpTree400_->deleteTree();
        isdpTree500_->deleteTree();

        delete sdpTree100_;     delete sdpTree200_;
        delete sdpTree300_;     delete sdpTree400_;
        delete sdpTree500_;     delete isdpTree100_;
        delete isdpTree200_;    delete isdpTree300_;
        delete isdpTree400_;    delete isdpTree500_;

        sdpTree100_ = nullptr;
        sdpTree200_ = nullptr;
        sdpTree300_ = nullptr;
        sdpTree400_ = nullptr;
        sdpTree500_ = nullptr;
        isdpTree100_ = nullptr;
        isdpTree200_ = nullptr;
        isdpTree300_ = nullptr;
        isdpTree400_ = nullptr;
        isdpTree500_ = nullptr;
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