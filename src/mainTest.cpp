// 
#include <iostream>
#include "redBlackTree.h"
#include "map.h"

int main()
{
	// std_selfmade::map<int,int> test;
	class Wt: public data_structures::RedBlackTree<int>{
		data_structures::stack<node*> iterStack;
		node* temp;
		public:
		void initIter(){
			temp=getRoot();
			iterStack.push(temp);
		}
		int walkFwd(){
			while(!iterStack.empty()){
				node* parent;
				iterStack.pop(&parent);
				if(parent->left){
					iterStack.push(parent->left);
				}

				

				if(parent->right){
					iterStack.push(parent->left);
				}
			}
			return temp->data;
		}
		int walkBkd(){
			return temp->data;
		}

	};
	Wt a;
	for(int i=0;i<10;i++){
		a.insert(i);
	}
	a.print();
	a.initIter();
	
	std::cout<<a.walkFwd()<<"\n";
	std::cout<<a.walkFwd()<<"\n";
	std::cout<<a.walkFwd()<<"\n";
	std::cout<<a.walkFwd()<<"\n";
	std::cout<<a.walkFwd()<<"\n";
	std::cout<<a.walkFwd()<<"\n";
	std::cout<<a.walkFwd()<<"\n";
	std::cout<<a.walkFwd()<<"\n";
	std::cout<<a.walkFwd()<<"\n";
	std::cout<<a.walkFwd()<<"\n";

	std::cout<<a.walkBkd()<<"\n";
	std::cout<<a.walkBkd()<<"\n";
	std::cout<<a.walkBkd()<<"\n";
	std::cout<<a.walkBkd()<<"\n";
	std::cout<<a.walkBkd()<<"\n";
	std::cout<<a.walkBkd()<<"\n";
	std::cout<<a.walkBkd()<<"\n";
	std::cout<<a.walkBkd()<<"\n";
	std::cout<<a.walkBkd()<<"\n";
	std::cout<<a.walkBkd()<<"\n";

	return 0;
}

