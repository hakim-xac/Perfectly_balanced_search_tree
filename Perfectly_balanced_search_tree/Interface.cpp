#include "Interface.h"
#include <string>

namespace KHAS {

	void Interface::initMenu()
	{
		using namespace std::literals;
		push(delimiter('='));
		push(bufferItem("Лабораторная работа:"s, "номер 1"s));
		push(bufferItem("Тема:"s, "Идеально сбалансированное дерево поиска"s));
		push(delimiter('-'));
		push(bufferItem("Выполнил студент:"s, "Хакимов А.С."s));
		push(delimiter('='));
	}

	Interface::Interface()
	{
		initMenu();
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

}
