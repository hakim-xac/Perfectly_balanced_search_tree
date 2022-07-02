#include "TaskExecution.h"
#include <random>

namespace KHAS {

	BinaryTree* TaskExecution::create(int count_tree)
	{

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<std::mt19937::result_type> dist(1);

		BinaryTree * temp_tree{ new BinaryTree(dist(gen)) };

		for (int i{ 1 }; i < count_tree; ++i) {
			temp_tree->insert(dist(gen));
		}
		
		return temp_tree;
	}

	void TaskExecution::print(BinaryTree* tree)
	{
		if (!tree) return;
		tree->print();
	}

	TaskExecution
		::TaskExecution()
	: Interface()
	, tree100_(create(100))
	, tree200_(create(200))
	, tree300_(create(300))
	, tree400_(create(400))
	, tree500_(create(500))	{}

	TaskExecution::~TaskExecution()
	{
		delete tree100_;
		delete tree200_;
		delete tree300_;
		delete tree400_;
		delete tree500_;
	}

	void TaskExecution::print100() const
	{
		print(tree100_);
	}

}