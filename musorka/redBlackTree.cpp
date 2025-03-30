// red black tree class with insert, find ,delete functions

#include<iostream>
#include "redBlackTree.h"
#include "stack.hpp"

#ifndef RED_BLACK_TREE_CLASS_CPP
#define RED_BLACK_TREE_CLASS_CPP

namespace data_structures {
	
		template <typename dataPoint>
		RedBlackTree<dataPoint>::RedBlackTree() requires isComparable<dataPoint>
		
		template <typename dataPoint>
		RedBlackTree<dataPoint>::~RedBlackTree() 
		
		template <typename dataPoint>
		RedBlackTree<dataPoint>::RedBlackTree(RedBlackTree&& other)

		template <typename dataPoint>
		RedBlackTree<dataPoint>::RedBlackTree(const RedBlackTree& other)
		
		template <typename dataPoint>
		bool RedBlackTree<dataPoint>::operator==(const RedBlackTree& other)

		template <typename dataPoint>
		void RedBlackTree<dataPoint>::copyNode( node* thisNode,const node* otherNode)

		template <typename dataPoint>
		RedBlackTree<dataPoint>::node* RedBlackTree<dataPoint>::node::gran()
	
		template <typename dataPoint>
		RedBlackTree<dataPoint>::node* RedBlackTree<dataPoint>::node::brother() 
		
		template <typename dataPoint>
		RedBlackTree<dataPoint>::node* RedBlackTree<dataPoint>::node::uncle() 
		
		template <typename dataPoint>
		Color RedBlackTree<dataPoint>::color(node* node_) 
		
		template <typename dataPoint>
		void RedBlackTree<dataPoint>::rotateLeft(node* toRot) 
		
		template <typename dataPoint>
		void RedBlackTree<dataPoint>::rotateRight(node* toRot) 
		
		template <typename dataPoint>
		void RedBlackTree<dataPoint>::print(node* current, std::ostream& outStream, bool useColors, std::string prefix , bool isLeft , int level)

		template <typename dataPoint>
		void RedBlackTree<dataPoint>::deletionBalance(node * temp) 
		//some funstions tat return node instead of value
		template <typename dataPoint>
		constexpr RedBlackTree<dataPoint>::node* RedBlackTree<dataPoint>::getRoot() 

		template <typename dataPoint>
		RedBlackTree<dataPoint>::node* RedBlackTree<dataPoint>::getNode(dataPoint& value) 

		template <typename dataPoint>
		bool RedBlackTree<dataPoint>::deleteNode(node* toDelete)

		template <typename dataPoint>
		void RedBlackTree<dataPoint>::insertionBalance(node * temp)

		template <typename dataPoint>
		RedBlackTree<dataPoint>::node* RedBlackTree<dataPoint>::insertNode(node* toInsert) 
	
		template <typename dataPoint>
		dataPoint* RedBlackTree<dataPoint>::insert(dataPoint &item) 
	 
		template <typename dataPoint>
		dataPoint* RedBlackTree<dataPoint>::get(dataPoint& value)

        template <typename dataPoint>
        bool RedBlackTree<dataPoint>::remove(dataPoint& value) 

		template <typename dataPoint>
		void RedBlackTree<dataPoint>::clear(node* temp) 
		
		template <typename dataPoint>
		void RedBlackTree<dataPoint>::clear() 

		template <typename dataPoint>
		void RedBlackTree<dataPoint>::print(std::ostream& outStream, bool useColors) 

		template <typename dataPoint>
		bool RedBlackTree<dataPoint>::isEmpty() 
}
#endif