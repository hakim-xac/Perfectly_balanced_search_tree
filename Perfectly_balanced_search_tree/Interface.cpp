#include "Interface.h"
#include <string>

namespace KHAS {

	void Interface::init()
	{
		using namespace std::literals;

		bufferItem("m"s, "s"s, "hg"s);
	}

	Interface::Interface()
	{
		init();
	}

}
