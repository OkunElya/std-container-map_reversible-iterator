//just a little stack implementnion , will use it in RBT
#pragma once

namespace data_structures {
    template<typename T>
    class stack{
        size_t size=0;
        public:
            struct node
            {
                T data;
                node* prev;
            };
            node* start=nullptr;
        public:
        stack(){
            start=nullptr;
            size=0;
        }
        stack(stack &&other) noexcept {
            this->size = other.size;
            other.size = 0;
            this->start = other.start;
            other.start = nullptr;
        }   
        
        stack& operator=(const stack& other) {
            while (size > 0) pop(nullptr);
            if (!other.start) {
                return *this;
            }
            stack<T*> tempStack;
            node* tempNode = other.start;
            
            while (tempNode->prev) {
                tempStack.push(&tempNode->data);
                tempNode = tempNode->prev;
            }

            while (!tempStack.empty()) {
                T* temp;
                tempStack.pop(&temp);
                this->push(*temp);
            }
            
            return *this;
        }
        
        stack& operator=(stack&& other) noexcept {
          (*this)=other;
        }// MoveConstructable 

        stack(const stack &other) noexcept
        { 
            (*this)=other;
        } // CopyConstructable (LegacyIterator)
        ~stack(){
            while(size>0){
                pop(nullptr);
            }
        }
        size_t push(T data){
            node* temp=new node;
            temp->prev=start;
            temp->data=data;
            start=temp;
            return ++size;
        }
        bool pop(T* buf=nullptr){
            if(!start)
                return false;
            if (buf)
                *buf=start->data;
            node* toRem =start;
            start=start->prev;
            delete toRem;
            --size;
            return true;

        }
        size_t getSize(){
            return size;
        }
        T* peek()const {
            if(!start)
                return nullptr;
            return &start->data;
        }
        bool empty(){
            return start==nullptr;
        }
    };

}
