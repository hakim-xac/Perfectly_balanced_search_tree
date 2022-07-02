#include "Interface.h"
#include <string>

namespace KHAS {

	void Interface::initMenu()
	{
		using namespace std::literals;
		push(delimiter('='));
		push(bufferItem("������������ ������:"s, "����� 1"s));
		push(bufferItem("����:"s, "�������� ���������������� ������ ������"s));
		push(delimiter('-'));
		push(bufferItem("�������� �������:"s, "������� �.�."s));
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
