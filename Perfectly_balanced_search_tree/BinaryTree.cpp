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
        // если Node == nullptr
        if (!root) return 0;
        // иначе 1 + размер(лева€ Node) + размер(права€ Node)
        return 1 + sizeTree(root->left) + sizeTree(root->right);
    }

    int BinaryTree::heightTree(const Node* const root)
    {
        // если Node == nullptr то возвращаем 0
        if (!root) return 0;
        // определ€ем высоту левого дерева
        int left_height{ heightTree(root->left) };
        // определ€ем высоту правого дерева
        int right_height{ heightTree(root->right) };

        // возвращаем большую высоту из левого и правого дерева и добавл€ем текущую, т.е. +1
        return (left_height > right_height ? left_height : right_height) + 1;		
    }

    int BinaryTree::middleHeightTree(const Node* const root, int level)
    {
        // если Node == nullptr то возвращаем 0
        if (!root) return 0;
        // возвращаем среднюю высоту левого и правого дерева мен€ем уровень на +1
        return level 
            + middleHeightTree(root->left, level + 1)
            + middleHeightTree(root->right, level + 1);
    }

    long long BinaryTree::hashTree(const Node* const root)
    {
        // если Node == nullptr  то возвращаем 0.
        if (!root) return 0;

        using out_type = long long;

        // возвращаем хеш-сумму левого + хеш-сумму правого дерева + данные
        return (
            static_cast<out_type>(root->data)
            + hashTree(root->left)
            + hashTree(root->right) );

    }

    bool BinaryTree::isSearchTree(const Node* const root)
    {
        if(root && (
            (root->left && (root->data <= root->left->data || isSearchTree(root->left)))
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
        // принимаем границы в массиве

        // если лева€ граница больше, то это не правильно, возвращаем nullptr
        if (left > right) return nullptr;

        int size{ static_cast<int>(vec_buffer_.size()) };

        if (size == 0) return nullptr;

        // если права€ граница больше размера массива, или меньше 0, то возврат nullptr
        if (right >= size || left < 0) return nullptr;

        int middle{ left + ((right - left) / 2) };

        // —оздаем Node с данными из €чейки массива со смещением "middle".
        Node* nd{ new (std::nothrow) Node(vec_buffer_[middle]) };

        // если Node не создалс€, то возврат nullptr
        if (!nd) return nullptr;

        // теперь создаем левую и правую Node
        nd->left = toISDP(left, middle - 1);
        nd->right = toISDP(middle + 1, right);

        // возвращаем указатель на созданную Node
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
        Node* it{ root_ };  // —оздаем указатель на корень дерева

        // ≈сли указатель не пустой, значит содержит данные.
        // —равниваем данные с текущим ключом
        // , если он совпадает выходим из цикла
        // , так как данные в дереве должны быть уникальны.
        while (it && it->data != key)
        {
            // если ключ больше данных и указатель на левый Node пуст
            // , то создаем Node в левый Node
            if (it->data > key && it->left == nullptr)
            {
                it->left = new (std::nothrow) Node(key);
                break;
            }

            // если ключ vtymit данных и указатель на ghfdsq Node пуст
            // , то создаем Node в ghfdsq Node
            if (it->data < key && it->right == nullptr)
            {
                it->right = new (std::nothrow) Node(key);
                break;
            }

            // если ключ меньше данных
            //, то текущему указателю it, присваеваем левую Node
            if (it->data > key)  it = it->left;
            // если ключ больше данных
            //, то текущему указателю it, присваеваем правую Node
            else				 it = it->right;
        }
    }

    BinaryTree::BinaryTree(int size)
        : vec_buffer_()
        , root_(nullptr)
        , typeTree_(TypeTree::SDP) {

        vec_buffer_.reserve(size);

        if (!fillVector(size)) {
            std::cout << "ќЎ»Ѕ ј! Ќ≈¬ќ«ћќ∆Ќќ —ќ«ƒј“№ Ѕј«”! " << std::endl;
            system("pause");
            exit(1);
        }

        if (!toSDP()) {
            std::cout << "ќЎ»Ѕ ј! Ќ≈¬ќ«ћќ∆Ќќ —ќ«ƒј“№ ƒ≈–≈¬ќ! " << std::endl;
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
        // создаем указатель на корень
        Node* it{ root_ };

        // движемс€ по дереву пока не найдем ключ
        while (it) {

            // если ключ больше данных, то ищем в Node справа
            if (it->data < key)             it = it->right;
            // если ключ меньше данных, то ищем в Node слева
            else if (it->data > key)	    it = it->left;
            // иначе ключ найден
            else                            return true;            
        }

        // если дошли до конца дерева, а данных нет, то не нашли, если есть то нашли
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