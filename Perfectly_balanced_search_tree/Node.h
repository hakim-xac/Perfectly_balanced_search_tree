#pragma once

namespace KHAS {

	class Node {

	public:
		Node* left{ nullptr };
		Node* right{ nullptr };
		int* data{ nullptr };


		Node(int* value)
			: left(nullptr)
			, right(nullptr)
			, data(value) {}

		Node() = delete;
	};

}