#include "BinaryTree.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>


namespace KHAS {

    void BinaryTree::deleteTree(Node* root)
    {
        if (root) {
            deleteTree(root->left);
            deleteTree(root->right);
            delete root;
        }
    }

    std::stringstream BinaryTree::readTree(const Node* const root)
    {
        if (!root) return std::stringstream{};
        std::stringstream ss;
        ss << readTree(root->left).str();
        ss << root->data << " ";
        ss << readTree(root->right).str();
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
        if(root && ((root->left && (root->data <= root->left->data || isSearchTree(root->left)))
            || (root->right && (root->data >= root->right->data || !isSearchTree(root->right)))
            )){
            return false;
        }
        return true;
    }

    bool BinaryTree::toSDP()
    {
        if (vec_buffer_.size() == 0) return false;

        root_ = new (std::nothrow) Node(vec_buffer_[0]);

        for (size_t i{}, ie{ vec_buffer_.size() }; i != ie; ++i) {
            insert(vec_buffer_[i]);            
        }
        return true;
    }

    Node* BinaryTree::toISDP(int left, int right)
    {
        if (left > right) return nullptr;

        int size{ static_cast<int>(vec_buffer_.size()) };

        if (size == 0) return nullptr;
        if (right >= size || left < 0) return nullptr;

        int middle{ left + ((right - left) / 2) };

        Node* nd{ new (std::nothrow) Node(vec_buffer_[middle]) };
        if (!nd) return nullptr;

        nd->left = toISDP(left, middle - 1);
        nd->right = toISDP(middle + 1, right);
        return nd;

    }

    bool BinaryTree::fillVector(int size)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dist(-10000, 10000);
        


        for (int i{}, ie{ size }; i != ie; ++i) {

            auto tmp{ dist(gen) };
            while (std::find(vec_buffer_.begin(), vec_buffer_.end(), tmp) != vec_buffer_.end()) {
                tmp = dist(gen);
            }
            vec_buffer_.emplace_back(tmp);
        }     


        if (vec_buffer_.size() != size) {
            return false;
        }
        return true;
    }

    void BinaryTree::insert(int key)
    {
        Node* it{ root_ };
        while (it && it->data != key)
        {
            if (it->data > key && it->left == nullptr)
            {
                it->left = new (std::nothrow) Node(key);
                break;
            }

            if (it->data < key && it->right == nullptr)
            {
                it->right = new (std::nothrow) Node(key);
                break;
            }

            if (it->data > key)  it = it->left;
            else				 it = it->right;
        }
    }

    BinaryTree::BinaryTree(int size)
        : vec_buffer_()
        , root_(nullptr)
        , typeTree_(TypeTree::SDP) {

        vec_buffer_.reserve(size);

        if (!fillVector(size)) {
            std::cout << "ньхайю! мебнглнфмн янгдюрэ аюгс! " << std::endl;
            system("pause");
            exit(1);
        }

        if (!toSDP()) {
            std::cout << "ньхайю! мебнглнфмн янгдюрэ депебн! " << std::endl;
            system("pause");
            exit(1);
        }

    }

    BinaryTree::BinaryTree(BinaryTree* bt)
        : vec_buffer_()
        , root_(nullptr)
        , typeTree_(TypeTree::ISDP) {

        if (bt == this) return;

        vec_buffer_ = bt->vec_buffer_;

        root_ = toISDP(0, static_cast<int>(vec_buffer_.size() - 1));
    }

    BinaryTree::~BinaryTree()
    {
        if(root_) deleteTree(root_);
    }

    bool BinaryTree::find(int key) const
    {
        Node* it{ root_ };

        while (it) {
            if (it->data < key)          it = it->right;
            else if (it->data > key)	    it = it->left;
            else                            return true;            
        }
        return it != nullptr;
    }

    size_t BinaryTree::size() const
    {
        return sizeTree(root_);
    }

    std::stringstream BinaryTree::print() const
    {        
        return readTree(root_);
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
    void BinaryTree::deleteTree()
    {
        deleteTree(root_);
    }
}