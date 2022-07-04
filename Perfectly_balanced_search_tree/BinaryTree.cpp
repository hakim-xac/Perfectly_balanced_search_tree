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

    std::stringstream BinaryTree::printTree(const Node* const root)
    {
        if (!root) return std::stringstream{};
        std::stringstream ss;
        ss << printTree(root->left).str();
        ss << root->data << " ";
        ss << printTree(root->right).str();
        return ss;
    }

    int BinaryTree::sizeTree(const Node* const root)
    {
        if (!root) return 0;
        return 1 + sizeTree(root->left) + sizeTree(root->right);
    }

    int BinaryTree::heightTree(const Node* const root)
    {
        if (!root) return 0;
        int left_height{ heightTree(root->left) };
        int right_height{ heightTree(root->right) };

        return (left_height > right_height ? left_height : right_height) + 1;		
    }

    int BinaryTree::middleHeightTree(const Node* const root, int level)
    {
        if (!root) return 0;
        return level 
            + middleHeightTree(root->left, level + 1)
            + middleHeightTree(root->right, level + 1);
    }

    long long BinaryTree::hashTree(const Node* const root)
    {
        if (!root) return 0;
        using out_type = long long;

        return (
            static_cast<out_type>(root->data)
            + hashTree(root->left)
            + hashTree(root->right) );

    }

    bool BinaryTree::isSearchTree(const Node* const root)
    {
        if (!root) return false;
        if ((root->left && root->data <= root->left->data || isSearchTree(root->left))
            || root->right && (root->data >= root->right->data || !isSearchTree(root->right))) {
            return false;
        }
        return true;
    }

    BinaryTree::BinaryTree(int value)
        : root_(new (std::nothrow) Node(value)) {}

    BinaryTree::~BinaryTree()
    {
        if(root_) deleteTree(root_);
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
                it->left = new (std::nothrow) Node(key);
                return;
            }

            if (it->data < key && it->right == nullptr)
            {
                it->right = new (std::nothrow) Node(key);
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

            delete it;
            return;
        }

        if (it->right == nullptr) {

            if (parent && parent->left == it)	parent->left = it->left;
            if (parent && parent->right == it)	parent->right = it->left;

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
        return sizeTree(root_);
    }

    std::stringstream BinaryTree::print() const
    {        
        return printTree(root_);
    }

    int BinaryTree::height() const
    {
        return heightTree(root_);
    }

    int BinaryTree::middleHeight() const
    {
        return middleHeightTree(root_, 1) / sizeTree(root_);
    }

    long long BinaryTree::hash() const
    {
        return hashTree(root_);
    }
    bool BinaryTree::isSearch() const
    {
        return isSearchTree(root_);
    }
}