#pragma once

#include "Node.h"
#include "Enums.h"
#include <sstream>
#include <vector>

namespace KHAS {

    class BinaryTree {

    private:
        std::vector<int> vec_buffer_;
        Node* root_;
        TypeTree typeTree_;
    private:

        static void deleteTree(Node* root)                             ;
        static std::stringstream readTree(const Node* const root)      ;
        static int sizeTree(const Node* const root)                    ;
        static int heightTree(const Node* const root)                  ;
        static int middleHeightTree(const Node* const root, int level) ;
        static long long hashTree(const Node* const root)              ;
        static bool isSearchTree(const Node* const root)               ;

        bool toSDP()                                                   ;
        static Node* toISDP(std::vector<int>& vec, int left, int right);
        bool fillVector(int size)                                      ;
        void insert(int& key)                                          ;

    public:
        BinaryTree() =                                  delete;
        BinaryTree(const BinaryTree& bt) =              delete;
        BinaryTree(BinaryTree&& bt) =                   delete;
        BinaryTree& operator =(const BinaryTree& bt) =  delete;
        BinaryTree& operator =(BinaryTree&& bt) =       delete;

        BinaryTree(int size);
        BinaryTree(BinaryTree* bt);
        ~BinaryTree();

        bool find(int key)	            const;
        size_t size()		            const;
        std::stringstream print()	    const;
        int height()		            const;
        int middleHeight()	            const;
        long long hash()	            const;
        bool isSearch()                 const;
        void deleteTree()                    ;


    };

}