#pragma once

namespace KHAS {

	// тип дерева
	enum class TypeTree {
		SDP, ISDP
	};

	// используемые команды в программе
	enum class InputCommand {
		NoCommand
		, Exit
		, ErrorCommands
		, Print
		, FindItem		
	};

}