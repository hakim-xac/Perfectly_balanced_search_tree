#pragma once
#include "Interface.h"
#include "BinaryTree.h"

namespace KHAS {

    class TaskExecution : public Interface {

        template <typename BTree>
        using isBinaryTree_t = std::enable_if_t<std::is_same_v<BTree, BinaryTree>>;

        BinaryTree* tree100_;
        BinaryTree* tree200_;
        BinaryTree* tree300_;
        BinaryTree* tree400_;
        BinaryTree* tree500_;

    private:
        /// <summary>
        /// 
        /// </summary>
        static BinaryTree* create(int count_tree);

        /// <summary>
        /// 
        /// </summary>
        template <typename Str>
        static void print(Str&& str, const BinaryTree* const tree);

        /// <summary>
        /// 
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void printTree(const BTree* const tree);

        /// <summary>
        /// 
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void hashTree(const BTree* const tree);

        /// <summary>
        /// 
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void heightTree(const BTree* const tree);

        /// <summary>
        /// 
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void sizeTree(const BTree* const tree);

        /// <summary>
        /// 
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void middleHeightTree(const BTree* const tree);
        /// <summary>
        /// 
        /// </summary>
        BinaryTree* selectTree(int index) const;

        /// <summary>
        /// 
        /// </summary>
        void functionLaunch() override;

        /// <summary>
        /// 
        /// </summary>
        void space()        const;

        /// <summary>
        /// 
        /// </summary>
        void print100()     const;

        /// <summary>
        /// 
        /// </summary>
        void print200()     const;

        /// <summary>
        /// 
        /// </summary>
        void print300()     const;

        /// <summary>
        /// 
        /// </summary>
        void print400()     const;

        /// <summary>
        /// 
        /// </summary>
        void print500()     const;

        /// <summary>
        /// 
        /// </summary>
        void findInTree();

        /// <summary>
        /// 
        /// </summary>
        void quit()         const;



    public:
        TaskExecution()          ;
        ~TaskExecution()         ;
        void showMenu() const override;
        
    };



    template<typename Str>
    inline void TaskExecution::print(Str&& str, const BinaryTree* const tree)
    {
        using namespace std::literals;

        push(delimiter('-'));
        push(bufferItem(std::forward<Str>(str)));
        push(delimiter('-'));

        printTree(tree);
        sizeTree(tree);
        hashTree(tree);
        heightTree(tree);
        middleHeightTree(tree);
        showStatusBar();
        
    }

    template<typename BTree, typename T2>
    inline void TaskExecution::printTree(const BTree* const tree)
    {
        using namespace std::literals;

        auto&& ss{ tree->print() };

        push(delimiter('='));
        push(bufferItem("Вывод дерева"s));
        push(delimiter('='));

        std::string first{}, second{}, third{}, fourth{}, fiveth{};
        do {

            ss >> first >> second >> third >> fourth >> fiveth;
            if (ss.good()) {
                push(bufferItem(
                    first
                    , second
                    , third
                    , fourth
                    , fiveth));
            }
        } while (ss.good());
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::hashTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("Хеш сумма дерева:"s
            , std::to_string(tree->hash())));
        push(delimiter('='));
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::heightTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("Высота дерева:"s
            , std::to_string(tree->height())));
        push(delimiter('='));
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::sizeTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("Размер дерева:"s
            , std::to_string(tree->size())));
        push(delimiter('='));
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::middleHeightTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("Средняя высота дерева:"s
            , std::to_string(tree->middleHeight())));
        push(delimiter('='));
    }





}