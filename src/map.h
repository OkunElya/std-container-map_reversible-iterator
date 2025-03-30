#include <iostream>
#include <cstdio>
#include <iterator>
#include <numeric>

#include "redBlackTree.h"

#ifndef SELFMADE_MAP_CLASS_H
#define SELFMADE_MAP_CLASS_H
namespace std_selfmade
{
    template <class Key, class T> 
    class map 
    {
        struct node;

        template<bool is_const>
        class iteratorBase;
        using const_iterator = iteratorBase<true>;
        template<bool is_const>
        class iteratorBase{//has to be bidirectional
        public:
            using value_type = std::conditional<is_const,const node,node>;//LegacyIterator req 
            using difference_type = std::ptrdiff_t;//LegacyIterator req 
            using reference =  std::conditional<is_const,const node&,node&>;//LegacyIterator req 
            using pointer =  std::conditional<is_const,const node*,node*>;//LegacyIterator req 
            using iterator_category = std::bidirectional_iterator_tag;//LegacyIterator req 

            iteratorBase(){
                
            }//DefaultConstructible
            iteratorBase(pointer p){
                data_structures::RedBlackTree<node> treeptr=p->treeNodePtr;
            }
            iteratorBase(const iteratorBase& other){}//CopyConstructable (LegacyIterator)
            iteratorBase(iteratorBase&& other){}//MoveConstructable (LegacyIterator)
            iteratorBase& operator=(const iteratorBase& other) {}//CopyConstructable
            iteratorBase& operator=(iteratorBase&& other) {}//MoveConstructible

            ~iteratorBase(){}//Destructible (LegacyIterator)
            
            void swap(iteratorBase& other)//Swapable (LegacyIterator)
            {

            }

            friend void swap(iteratorBase& lhs, iteratorBase& rhs)//Swapable req
            {
                lhs.swap(rhs);
            }
            reference operator*()//LegacyInputIterator req
            {

            }
            pointer operator->()//LegacyInputIterator req
            {
                
            }

            iteratorBase& operator++()//prefix
            {

            }
            iteratorBase& operator++(int)//postfix
            {

            }
            
            bool operator==(const iteratorBase& other)//EqualityComparable (LegacyInputIterator)
            {
                curr_ptr->treeNodePtr==other->treeNodePtr;
            }
            bool operator!=(const iteratorBase& other)//LegacyInputIterator req
            {
                return ! this->operator==();
            }

            iteratorBase& operator--()//prefix
            {}
            iteratorBase& operator--(int)//postfix
            {}
            operator const_iterator()//LegacyForwardIterator req
            {
                
            }
            private:
            pointer curr_ptr;
        };
        using iterator =iteratorBase<false>;
        
        using reverse_iterator= std::reverse_iterator<iterator>;
        using const_reverse_iterator= std::reverse_iterator<const_iterator>;

        using value_type =node;
        using reference = node&;//LegacyIterator req 
        using const_reference = const node&;
        using difference_type = std::ptrdiff_t;
        using size_type = size_t;
        using pointer = node*;
    

    public:
        map()requires isComparable<Key> //the only point where user can select the type
        {
            
        }
        map(const map& other)
        {
            tree(other.tree);
        }//copy constructor
        map(map&& other)
        {
            tree(other.tree);
        }//move consructor
        map& operator=(const map& other) 
        {
            tree(other.tree);
            return this;
        }
        map& operator=(map&& other) 
        {
            tree(other.tree);
            return this;

        }

        iterator begin() {return iterator(tree->root);}
        const_iterator begin() const {return cbegin();}
        const_iterator cbegin() {}

        iterator end() {}
        const_iterator end() const {return cend();}
        const_iterator cend(){}

        reverse_iterator rbegin()   {return reverse_iterator().rbegin(); }//reversible container req
        const_reverse_iterator rbegin() const {return crbegin(); }
        const_reverse_iterator crbegin()  {return reverse_iterator().crbegin(); }

        reverse_iterator rend() {return reverse_iterator().rend(); }
        const_reverse_iterator rend() const {return crend();}
        const_reverse_iterator crend()   {return reverse_iterator().crend(); }



        bool operator==(const map& other){
            if(size()!=other.size())
                return false;
            return tree==other.tree;
        }
        bool operator!=(const map& other){
            return !this->operator==(other);
        }

        void swap(map& other){
            std::swap(this->elementCount,other.elementCount);
            std::swap(this->tree,other.tree);
        }
        friend void swap(map& lhs, map& rhs){
            lhs.swap(rhs);
        }
        size_type size(){
            return elementCount;
        }
        size_type max_size(){
            //idk, container is not allocator aware so can't actually say how much can it take , but i can take into accout sizeof(key)+sizeof(val) (Stackowerflo0w states that i should'nt take memeory constraints into account)
            return std::numeric_limits<size_t>::max();
        }
        bool empty(){
            return size()==0;
        }
        
        ~map(){
            //tree is destructed automaticly, all freeing is handled there
        }
        private:
            size_t elementCount=0;//cout them all
            struct node:protected std::pair<Key,T> {
            protected:
                data_structures::RedBlackTree<node>::node* treeNodePtr=nullptr;
                //let's assume that it always points to the node in the tree
            };
            
            struct treeNode:node {
            public:
                bool operator== (treeNode &other){
                    return this->first==other.first;
                }
                bool  operator< (treeNode &other){
                    return this->first<other.first;
                }
                bool  operator> (treeNode &other){
                    return this->first>other.first;
                }
            };

            data_structures::RedBlackTree<treeNode> tree;
    };
}

#endif
