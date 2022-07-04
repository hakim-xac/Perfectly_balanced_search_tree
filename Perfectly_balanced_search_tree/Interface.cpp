#include "Interface.h"
#include <string>

namespace KHAS {

    void Interface::showHeader()
    {
        using namespace std::literals;
        pushToBuffer(delimiter('='));
        pushToBuffer(bufferItem("Лабораторная работа:"s, "номер 1"s));
        pushToBuffer(bufferItem("Тема:"s, "ИСДП и СДП"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("Выполнил студент:"s, "Хакимов А.С."s));
        pushToBuffer(delimiter('='));
        show();
    }

    void Interface::readCommand()
    {
        std::cout << std::string(fieldWidth_, '_')
            << std::string(fieldWidth_, '\b')
            << "Введите команду:";

        int cmd{ std::cin.get() };
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (cmd)
        {
        case 49: activeCommand_ = InputCommand::Print;      break; // 1
        case 50: activeCommand_ = InputCommand::FindItem;   break; // 2
        case 57: activeCommand_ = InputCommand::Exit;       break; // 9

        default: activeCommand_ = InputCommand::ErrorCommands;            
        }
        
    }

    Interface::~Interface()
    {
        show();
    }

    void Interface::show()
    {
        while (!buffer_.empty()) {

            std::cout << buffer_.front() << "\n";
            buffer_.pop();
        }
        std::flush(std::cout);
    }



    void Interface::showStatusBar()
    {
        if (!bufferStatusBar_.empty()) {
            push(delimiter('-'));
            while (!bufferStatusBar_.empty()) {
                std::cout << bufferStatusBar_.front() << "\n";
                bufferStatusBar_.pop();
            }
            std::flush(std::cout);
        }
    }

    InputCommand Interface::getActiveCommand() const
    {
        return activeCommand_;
    }

    void Interface::clearActiveCommand()
    {
        activeCommand_ = InputCommand::NoCommand;
    }



    void Interface::view()
    {
        while (true) {
            system("cls");
            showHeader();
            functionLaunch();
            showStatusBar();
            showMenu();
            readCommand();
        }
    }

}
