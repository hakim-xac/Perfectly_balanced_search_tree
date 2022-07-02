#pragma once
#include "Interface.h"
#include "BinaryTree.h"

namespace KHAS {

	class TaskExecution : Interface {

		BinaryTree* tree100_;
		BinaryTree* tree200_;
		BinaryTree* tree300_;
		BinaryTree* tree400_;
		BinaryTree* tree500_;

	private:
		static BinaryTree* create(int count_tree);
		static void print(BinaryTree* tree);
	public:
		TaskExecution();
		~TaskExecution();
		void print100() const;
	};
}