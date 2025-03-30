//just a little stack implementnion , will use it in RBT

#ifndef STACK_CLASS_H
#define STACK_CLASS_H
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
        T* peek(){
            if(!start)
                return nullptr;
            return &start->data;
        }
        bool empty(){
            return start==nullptr;
        }
    };

}

#endif