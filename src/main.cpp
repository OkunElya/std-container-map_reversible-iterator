// 
#include <iostream>
#include "redBlackTree.h"
#include "map.h"

int main()
{
	// std_selfmade::map<int,int> test;
	class Wt: public data_structures::RedBlackTree<int>{
		data_structures::stack<node*> iterStack;
		int stat=0;
	public:
		bool leftIsWalked=false;
		bool rightIsWalked=false;
		bool outputDone=false;
		bool isFirstMove=true;
		node& operator*(){
			node* temp;
			temp=*iterStack.peek();
			return *temp; 
		}
		node* operator->(){
			node* temp;
			temp=*iterStack.peek();
			return temp; 
		}
		void initIter(){
			node* temp=getRoot();
			iterStack.push(temp);
			
		}
		node* findNode(int value){
			return getNode(value);
		}
		void initIter(node* nodePtr){

			data_structures::stack<node*> tempStack;
			tempStack.push(nodePtr);
			while(nodePtr->parent){
				nodePtr=nodePtr->parent;
				tempStack.push(nodePtr);
			}

			while(!tempStack.empty()){//reverse the stack
				node* temp;
				tempStack.pop(&temp);
				iterStack.push(temp);
			}
		}

		int operator++(){
			if (isFirstMove){
				leftIsWalked=true;
				if(!(*iterStack.peek())->right){
					outputDone=false;
					rightIsWalked=true;
				}
				else{
					rightIsWalked=false;
					outputDone=true;
				}
				isFirstMove=false;
			}
			node* temp;
			while(!iterStack.empty()){
				temp=*iterStack.peek();
				if(temp->left&&!leftIsWalked){
					iterStack.push(temp->left);
					leftIsWalked=false;
					rightIsWalked=false;
					continue;
				}
				leftIsWalked=true;

				if((!rightIsWalked)&&(!outputDone)){
					outputDone=true;
					break;
				}
				outputDone=false;
				
				if(temp->right&&!rightIsWalked){
					iterStack.push(temp->right);
					leftIsWalked=false;
					rightIsWalked=false;
					continue;
				}
				rightIsWalked=true;
				//no left child, no right chid.
				
				if (((*iterStack.peek())->parent)&&(((*iterStack.peek())->parent->left)==(*iterStack.peek()))){
					rightIsWalked=false;
				}
				iterStack.pop();
			}
			return temp->data;
		}
		int operator--(){
			if (isFirstMove){
				rightIsWalked=false;
				if(!(*iterStack.peek())->left){
					leftIsWalked=false;
					outputDone=false;
				}
				else{
					leftIsWalked=true;
					outputDone=true;
				}
				isFirstMove=false;
			}
			node* temp;
			while(!iterStack.empty()){
				temp=*iterStack.peek();

				if(temp->right&&rightIsWalked){
					iterStack.push(temp->right);
					leftIsWalked=true;
					rightIsWalked=true;
					continue;
				}
				rightIsWalked=false;
				
				if((leftIsWalked)&&(!outputDone)){
					outputDone=true;
					break;
				}
				outputDone=false;
				
				if(temp->left&&leftIsWalked){
					iterStack.push(temp->left);
					leftIsWalked=true;
					rightIsWalked=true;
					continue;
				}
				leftIsWalked=false;
				
				//no left child, no right chid.
				
				if (((*iterStack.peek())->parent)&&(((*iterStack.peek())->parent->right)==(*iterStack.peek()))){
					leftIsWalked=true;
				}
				iterStack.pop();
			}
			return temp->data;
		}

	};
	Wt tree;
	for(int i=0;i<10;i++){
		tree.insert(i);
	}
	tree.print();
	int toFind=9;
	Wt::node* toIterOn=tree.getNode(toFind);

	
	
	tree.initIter(toIterOn);
	// tree.initIter();


	std::cout<<tree->data<<"\n";
	for(int i =0;i<4;i++){
		std::cout<<(--tree)<<" ";
		std::cout<<(--tree)<<" ";
		std::cout<<(--tree)<<" ";
		std::cout<<(--tree)<<" ";
		std::cout<<(--tree)<<" B\n";

		std::cout<<(++tree)<<" ";
		std::cout<<(++tree)<<" ";
		std::cout<<(++tree)<<" ";
		std::cout<<(++tree)<<" ";
		std::cout<<(++tree)<<" F\n";
	}


	

	return 0;
}

