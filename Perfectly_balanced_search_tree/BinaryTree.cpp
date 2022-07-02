#include "BinaryTree.h"
#include <iostream>


namespace KHAS {

	void BinaryTree::deleteTree(Node* root)
	{
		if (root) {
			deleteTree(root->left);
			deleteTree(root->right);
			delete root;
		}
	}

	void BinaryTree::printTree(Node* root) const
	{
		if (!root) return;
		printTree(root->left);
		std::cout << root->data << " ";
		printTree(root->right);
	}

	BinaryTree::BinaryTree(int value)
		: root_(new Node(value))
		, size_(1) {}

	BinaryTree::~BinaryTree()
	{
		deleteTree(root_);
	}

	bool BinaryTree::find(int key) const
	{
		Node* it{ root_ };

		while (it && it->data != key) {
			if (it->data > key)		it = it->left;
			else					it = it->right;
		}
		return it != nullptr;
	}

	void BinaryTree::insert(int key)
	{
		Node* it{ root_ };

		while (it && it->data != key)
		{
			if (it->data > key && it->left == nullptr)
			{
				it->left = new Node(key);
				++size_;
				return;
			}

			if (it->data < key && it->right == nullptr)
			{
				it->right = new Node(key);
				++size_;
				return;
			}

			if (it->data > key)		it = it->left;
			else					it = it->right;
		}
	}

	void BinaryTree::erase(int key)
	{
		Node* it{ root_ };
		Node* parent{ nullptr };

		while (it && it->data != key) {
			parent = it;
			if (it->data > key)	it = it->left;
			else				it = it->right;
		}

		if (!it) return;

		if (it->left == nullptr) {

			if(parent && parent->left == it)	parent->left = it->right;
			if(parent && parent->right == it)	parent->right = it->right;

			--size_;
			delete it;
			return;
		}

		if (it->right == nullptr) {

			if (parent && parent->left == it)	parent->left = it->left;
			if (parent && parent->right == it)	parent->right = it->left;

			--size_;
			delete it;
			return;
		}

		Node* replace{ it->right };

		while (replace->left) {
			replace = replace->left;
		}

		int replace_value{ replace->data };
		erase(replace_value);
		it->data = replace_value;
	}

	size_t BinaryTree::size() const
	{
		return size_;
	}

	void BinaryTree::print() const
	{
		printTree(root_);
		std::cout << std::endl;
	}
}