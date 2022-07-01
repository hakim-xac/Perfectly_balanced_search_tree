#include "Interface.h"
#include <string>

namespace KHAS {

	void Interface::init()
	{
		initMenu();

	}

	void Interface::initMenu()
	{
		using namespace std::literals;

		push(bufferItem("gngfngfn"s));
		push(bufferItem("gngfhjjngfn"s));
		push(bufferItem("gnhrhrrgfngfn"s));
		push(bufferItem("gngergergefngfn"s));
	}

	Interface::Interface()
	{
		init();
	}

	void Interface::show()
	{
		while (!buffer_.empty()) {

			std::cout << buffer_.top();
			buffer_.pop();
		}
	}

}
