#pragma once

namespace KHAS {

	class Node {

	public:

		// указатель на левое дерево
		Node* left{ nullptr };

		// указатель на правое дерево
		Node* right{ nullptr };

		// данные
		int data{};


		Node(int value)
			: left(nullptr)
			, right(nullptr)
			, data(value) {}

		Node() = delete;
	};

}