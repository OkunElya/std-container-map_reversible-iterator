#include <iostream>
#include <cstdio>
#include <iterator>
#include <map>
namespace myAlgs
{
    template <class Key, class T> 
    class map
    {
        template<typename ITER_VAR>
        class iteratorBase;
        using const_iterator = iteratorBase<const T>;
        template<typename ITER_VAR>
        class iteratorBase{//has to be bidirectional
        public:
            using value_type = ITER_VAR;//LegacyIterator req 
            using difference_type = std::ptrdiff_t;//LegacyIterator req 
            using reference = ITER_VAR&;//LegacyIterator req 
            using pointer = ITER_VAR*;//LegacyIterator req 
            using iterator_category = std::bidirectional_iterator_tag;//LegacyIterator req 

            iterator(
                
            ){}// DefaultConstructible
            iterator(pointer p){
                curr_ptr=nullptr;
            }
            iterator(const iteratorBase& other){}//CopyConstructable (LegacyIterator)
            iterator(iteratorBase&& other){}//MoveConstructable (LegacyIterator)
            iteratorBase& operator=(const iteratorBase& other) {}//CopyConstructable
            iteratorBase& operator=(iteratorBase&& other) {}//MoveConstructible

            ~iteratorBase(){}//Destructible (LegacyIterator)
            
            void swap(iteratorBase& other)//Swapable (LegacyIterator)
            {}

            friend void swap(iteratorBase& lhs, iteratorBase& rhs)//Swapable req
            {}
            reference operator*()//LegacyInputIterator req
            {}
            pointer operator->()//LegacyInputIterator req
            {}

            iteratorBase& operator++()//prefix
            {}
            iteratorBase& operator++(int)//postfix
            {}
            
            bool operator==(const iteratorBase& other)//EqualityComparable (LegacyInputIterator)
            {}
            bool operator!=(const iteratorBase& other)//LegacyInputIterator req
            {
                return ! this->operator==();
            }

            iteratorBase& operator--()//prefix
            {}
            iteratorBase operator--(int)//postfix
            {}
            operator const_iterator()//LegacyForwardIterator req
            {

            }
            private:
            pointer curr_ptr;
        };
        using iterator =iteratorBase<T>;
        
        using reverse_iterator= std::reverse_iterator<iterator>;
        using const_reverse_iterator= std::reverse_iterator<const_iterator>;

        using value_type = T;
        using reference = T&;//LegacyIterator req 
        using const_reference = const T&;
        using difference_type = std::ptrdiff_t;
        using size_type = size_t;
        using pointer = T*;

         
        map()
        {}
        map(const map& other)
        {}//copy constructor
        map(map&& other)
        {}//move consructor
        map& operator=(const map& other) 
        {}
        map& operator=(map&& other) 
        {}


        iterator begin() {}
        const_iterator begin() const {}
        const_iterator cbegin() {}

        iterator end() {}
        const_iterator end() const {}
        const_iterator cend(){}

        reverse_iterator rbegin(){}//reversible container req
        const_reverse_iterator rbegin() const {}
        const_reverse_iterator crbegin()  {}

        reverse_iterator rend(){}
        const_reverse_iterator rend() const {}
        const_reverse_iterator crend()  {}


        bool operator==(const map& other){}
        bool operator!=(const map& other){}

        void swap(map& other){}
        friend void swap(map& lhs, map& rhs){}
        size_type size(){}
        size_type max_size(){}
        bool empty(){}
        
        ~map(){}
    };
}
