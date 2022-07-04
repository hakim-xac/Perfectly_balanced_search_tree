#pragma once

#include "Node.h"
#include <sstream>

namespace KHAS {

    class BinaryTree {

    private:
        Node* root_;

    private:

        static void deleteTree(Node* root)                             ;
        static std::stringstream printTree(const Node* const root)     ;
        static int sizeTree(const Node* const root)                    ;
        static int heightTree(const Node* const root)                  ;
        static int middleHeightTree(const Node* const root, int level) ;
        static long long hashTree(const Node* const root)              ;
        static bool isSearchTree(const Node* const root)               ;


    public:
        BinaryTree() = delete;
        BinaryTree(int value);
        ~BinaryTree();

        void insert(int key);
        void erase(int key);
        bool find(int key)	        const;
        size_t size()		        const;
        std::stringstream print()	const;
        int height()		        const;
        int middleHeight()	        const;
        long long hash()	        const;
        bool isSearch()             const;

    };
}