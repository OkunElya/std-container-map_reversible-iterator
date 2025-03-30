#pragma once

#include <iostream>
#include <cstdio>
#include <iterator>
#include <numeric>
#include <optional>

#include "redBlackTree.h"
#include "stack.h"

namespace std_selfmade
{
    template <class Key, class T>
    class map
    {
        struct node;
        struct treeNode;
        template <bool is_const>
        class iteratorBase;
        using const_iterator = iteratorBase<true>;
        template <bool is_const>
        class iteratorBase
        { // has to be bidirectional
        private:
            enum statuses {notOnEdge,preLeft,postRight};
            statuses status=notOnEdge;
            bool leftIsWalked = false;
            bool rightIsWalked = false;
            bool outputDone = false;
            bool isFirstMove = true;
            data_structures::stack<typename data_structures::RedBlackTree<treeNode>::node *> iterStack;
            typename data_structures::RedBlackTree<treeNode>::node* leftMostNode = nullptr;
            typename data_structures::RedBlackTree<treeNode>::node* rightMostNode = nullptr;
        public:
            using value_type = typename std::conditional<is_const, const node, node>::type;    // LegacyIterator req
            using difference_type = std::ptrdiff_t;                                            // LegacyIterator req
            using reference = typename std::conditional<is_const, const node &, node &>::type; // LegacyIterator req
            using pointer = typename std::conditional<is_const, const node *, node *>::type;   // LegacyIterator req
            using iterator_category = typename std::bidirectional_iterator_tag;                // LegacyIterator req

            iteratorBase()
            {
            } // DefaultConstructible
            iteratorBase(pointer p)
            {
                if(!p){
                   throw "Bad node for iterator init!";
                }
                typename data_structures::RedBlackTree<treeNode>::node* nodePtr = p->treeNodePtr;
                data_structures::stack<typename data_structures::RedBlackTree<treeNode>::node *> tempStack;

                tempStack.push(nodePtr);
                while (nodePtr->parent)
                {
                    nodePtr = nodePtr->parent;
                    tempStack.push(nodePtr);
                }

                while (!tempStack.empty())
                { // reverse the stack
                    typename data_structures::RedBlackTree<treeNode>::node *temp;
                    tempStack.pop(&temp);
                    iterStack.push(temp);
                }

                //sadly for edge cases to work i'll have to store leftmost and rightmost nodes for the iterator
                //it means that complexity of iterator construction will be increased at least increased by 3 times(sad)
                leftMostNode = nodePtr;//holds root
                while(leftMostNode->left){
                    leftMostNode=leftMostNode->left;
                }
                rightMostNode = nodePtr;
                while(rightMostNode->right){
                    rightMostNode=rightMostNode->right;
                }
            }
            iteratorBase(const iteratorBase &other)
            {
                this->operator=(other);
            } // CopyConstructable (LegacyIterator)
            iteratorBase(iteratorBase &&other)
            {
                this->operator=(other);
            } // MoveConstructable (LegacyIterator)
            iteratorBase &operator=(const iteratorBase &other)
            {
                status=other.status;
                leftIsWalked = other.leftIsWalked;
                rightIsWalked = other.rightIsWalked;
                outputDone = other.outputDone;
                isFirstMove = other.isFirstMove;
                leftMostNode = other.leftMostNode;
                rightMostNode = other.rightMostNode;
                this->iterStack = other.iterStack;
                return *this;
            } // CopyConstructable
            iteratorBase &operator=(iteratorBase &&other)
            {
                status=other.status;
                leftIsWalked = other.leftIsWalked;
                rightIsWalked = other.rightIsWalked;
                outputDone = other.outputDone;
                isFirstMove = other.isFirstMove;
                leftMostNode = other.leftMostNode;
                rightMostNode = other.rightMostNode;
                this->iterStack = other.iterStack;

                other.status = status;//null out 
                other.leftIsWalked = leftIsWalked;
                other.rightIsWalked = rightIsWalked;
                other.outputDone = outputDone;
                other.isFirstMove = isFirstMove;
                other.leftMostNode = leftMostNode;
                other.rightMostNode = rightMostNode;
                return *this;
            } // MoveConstructible

            ~iteratorBase() {} // Destructible (LegacyIterator)

            void swap(iteratorBase &other) // Swapable (LegacyIterator)
            {
                std::swap(*this, other);
            }

            friend void swap(iteratorBase &lhs, iteratorBase &rhs) // Swapable req
            {
                lhs.swap(rhs);
            }
            reference operator*() // LegacyInputIterator req
            {
                node *temp;
                if(iterStack.peek()){
                    temp = &((*iterStack.peek())->data);
                    temp->treeNodePtr = (*iterStack.peek());
                }
                return *temp;
            }
            pointer operator->() // LegacyInputIterator req
            {
                treeNode *temp;
                if(iterStack.peek()){
                    temp = *iterStack.peek();
                }
                return ((node *)temp);
            }

            iteratorBase &operator++() // prefix
            {
                if(rightMostNode==(*iterStack.peek())){//developer is not a child... in some update i'll allow only one chance for mistake and after second bad move iterator will throw error
                    status=postRight;//prevent iterator from going further
                    return (*this);
                }
                if((leftMostNode==(*iterStack.peek()))&&(status==preLeft)){
                    status=notOnEdge;//prevent iterator from going further
                    return (*this);
                }
                
                if (isFirstMove)
                {
                    leftIsWalked = true;
                    if (!(*iterStack.peek())->right)
                    {
                        outputDone = false;
                        rightIsWalked = true;
                    }
                    else
                    {
                        rightIsWalked = false;
                        outputDone = true;
                    }
                    isFirstMove = false;
                }
                typename data_structures::RedBlackTree<treeNode>::node *temp;
                while (!iterStack.empty())
                {
                    temp = *iterStack.peek();
                    if (temp->left && !leftIsWalked)
                    {
                        iterStack.push(temp->left);
                        leftIsWalked = false;
                        rightIsWalked = false;
                        continue;
                    }
                    leftIsWalked = true;

                    if ((!rightIsWalked) && (!outputDone))
                    {
                        outputDone = true;
                        break;
                    }
                    outputDone = false;

                    if (temp->right && !rightIsWalked)
                    {
                        iterStack.push(temp->right);
                        leftIsWalked = false;
                        rightIsWalked = false;
                        continue;
                    }
                    rightIsWalked = true;
                    // no left child, no right chid.

                    if (((*iterStack.peek())->parent) && (((*iterStack.peek())->parent->left) == (*iterStack.peek())))
                    {
                        rightIsWalked = false;
                    }
                    iterStack.pop();
                }
                return (*this);
            }
            iteratorBase &operator++(int) // postfix
            {
                iteratorBase temp(*this);
                ++(*this);
                return temp;
            }

            bool operator==(const iteratorBase &other) // EqualityComparable (LegacyInputIterator)
            {
                if(!((status==notOnEdge)&&(other.status==notOnEdge))){
                    return other.status==this->status;
                }
                if (((iterStack.peek()) == nullptr) || (((other.iterStack.peek())) == nullptr))
                {
                    return (iterStack.peek() == other.iterStack.peek());
                }
                return ((*iterStack.peek()) == (*other.iterStack.peek()));
            }
            bool operator!=(const iteratorBase &other) // LegacyInputIterator req
            {
                return !this->operator==(other);
            }

            iteratorBase &operator--() // prefix
            {
                if(leftMostNode==(*iterStack.peek())){//developer is not a child... in some update i'll allow only one chance for mistake and after second bad move iterator will throw error
                    status=preLeft;//prevent iterator from going further
                    return (*this);
                }
                if((rightMostNode==(*iterStack.peek()))&&(status==postRight)){
                    status=notOnEdge;//prevent iterator from going further
                    return (*this);
                }

                if (isFirstMove)
                {
                    rightIsWalked = false;
                    if (!(*iterStack.peek())->left)
                    {
                        leftIsWalked = false;
                        outputDone = false;
                    }
                    else
                    {
                        leftIsWalked = true;
                        outputDone = true;
                    }
                    isFirstMove = false;
                }
                typename data_structures::RedBlackTree<treeNode>::node *temp;
                while (!iterStack.empty())
                {
                    temp = *iterStack.peek();

                    if (temp->right && rightIsWalked)
                    {
                        iterStack.push(temp->right);
                        leftIsWalked = true;
                        rightIsWalked = true;
                        continue;
                    }
                    rightIsWalked = false;

                    if ((leftIsWalked) && (!outputDone))
                    {
                        outputDone = true;
                        break;
                    }
                    outputDone = false;

                    if (temp->left && leftIsWalked)
                    {
                        iterStack.push(temp->left);
                        leftIsWalked = true;
                        rightIsWalked = true;
                        continue;
                    }
                    leftIsWalked = false;

                    // no left child, no right chid.

                    if (((*iterStack.peek())->parent) && (((*iterStack.peek())->parent->right) == (*iterStack.peek())))
                    {
                        leftIsWalked = true;
                    }
                    iterStack.pop();
                }
                return (*this);
            }
            iteratorBase &operator--(int) // postfix
            {
                iteratorBase temp(*this);
                --(*this);
                return temp;
            }
            operator const_iterator() // LegacyForwardIterator req
            {
            }
        };
        using iterator = iteratorBase<false>;

        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        using value_type = node;
        using reference = node &; // LegacyIterator req
        using const_reference = const node &;
        using difference_type = std::ptrdiff_t;
        using size_type = size_t;
        using pointer = node *;

    public:
        map()
            requires isComparable<Key> // the only point where user can select the type
        {
        }
        map(const map &other)
        {
            tree(other.tree);
        } // copy constructor
        map(map &&other)
        {
            tree(other.tree);
        } // move consructor
        map &operator=(const map &other)
        {
            tree(other.tree);
            return this;
        }
        map &operator=(map &&other)
        {
            tree(other.tree);
            return this;
        }

        iterator begin()
        {

            typename data_structures::RedBlackTree<treeNode>::node *treeTemp = tree.getRoot();
            while (treeTemp->left)
            {
                treeTemp = treeTemp->left;
            }
            node tempOut;
            tempOut.treeNodePtr = treeTemp;
            return iterator(&tempOut);
        }
        const_iterator begin() const {  typename data_structures::RedBlackTree<treeNode>::node *treeTemp = tree.getRoot();
            while (treeTemp->left)
            {
                treeTemp = treeTemp->left;
            }
            node tempOut;
            tempOut.treeNodePtr = treeTemp;
            return const_iterator(&tempOut); }
        const_iterator cbegin()
        {
           return begin();
        }

        iterator end()
        {
            typename data_structures::RedBlackTree<treeNode>::node *treeTemp = tree.getRoot();
            while (treeTemp->right)
            {
                treeTemp = treeTemp->right;
            }
            node temp;
            temp.treeNodePtr = treeTemp;
            return ++iterator(&temp);
        }
        const_iterator end() const { return cend(); }
        const_iterator cend()
        {
            typename data_structures::RedBlackTree<treeNode>::node *treeTemp = tree.getRoot();
            while (treeTemp->right)
            {
                treeTemp = treeTemp->right;
            }
            node temp;
            temp.treeNodePtr = treeTemp;
            return ++const_iterator(&temp);
        }

        reverse_iterator rbegin() { return reverse_iterator(end()); } // reversible container req
        const_reverse_iterator rbegin() const { return crbegin(); }
        const_reverse_iterator crbegin() { return const_reverse_iterator(end()); }

        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const { return crend(); }
        const_reverse_iterator crend() { return const_reverse_iterator(cbegin()); }


        bool operator==(const map &other)
        {
            if (size() != other.size())
                return false;
            return tree == other.tree;
        }
        bool operator!=(const map &other)
        {
            return !this->operator==(other);
        }

        void swap(map &other)
        {
            std::swap(this->elementCount, other.elementCount);
            std::swap(this->tree, other.tree);
        }
        friend void swap(map &lhs, map &rhs)
        {
            lhs.swap(rhs);
        }
        size_type size()
        {
            return elementCount;
        }
        size_type max_size()
        {
            // idk, container is not allocator aware so can't actually say how much can it take , but i can take into accout sizeof(key)+sizeof(val) (Stackowerflo0w states that i should'nt take memeory constraints into account)
            return std::numeric_limits<size_t>::max();
        }
        bool empty()
        {
            return size() == 0;
        }
        std::optional<node> get(Key temp)
        {
            treeNode toFind;
            toFind.first = temp;
            typename data_structures::RedBlackTree<treeNode>::node *out_ = tree.getNode(toFind);
            if (!out_)
            {
                return {}; // node doesen't exist
            }
            node found;
            found.treeNodePtr = out_;
            found = *((node *)(&(out_->data)));
            return found;
        }

        void put(std::pair<Key, T> temp)
        {
            elementCount++;
            tree.insert(*((treeNode *)&temp));
        }

        bool pop(Key key)
        {
            auto temp=get(key);
            if(temp){
                elementCount--;
                tree.remove(temp);
                return true;
            }
            return false;
        }

        ~map() {} // tree is destructed automaticly, all freeing is handled there

    private:
        size_t elementCount = 0; // cout them all
        struct node : public std::pair<Key, T>
        {
        public:
            data_structures::RedBlackTree<treeNode>::node *treeNodePtr = nullptr;
            // let's assume that it always points to the node in the tree
        };

        struct treeNode : public node
        {
        public:
            bool operator==(treeNode &other)
            {
                return this->first == other.first;
            }
            bool operator<(treeNode &other)
            {
                return this->first < other.first;
            }
            bool operator>(treeNode &other)
            {
                return this->first > other.first;
            }
        };

        data_structures::RedBlackTree<treeNode> tree;
    };
}
