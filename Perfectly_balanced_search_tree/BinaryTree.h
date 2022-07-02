#pragma once

#include "Node.h"

namespace KHAS {

	class BinaryTree {

	private:
		Node* root_;
		size_t size_;

	private:

		void deleteTree(Node* root);
		void printTree(Node* root) const;

	public:
		BinaryTree() = delete;
		BinaryTree(int value);
		~BinaryTree();

		bool find(int key) const;
		void insert(int key);
		void erase(int key);
		size_t size() const;
		void print() const;

	};
}