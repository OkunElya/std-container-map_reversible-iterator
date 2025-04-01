#pragma once
// red black tree class with insert, find ,delete functions

#include <iostream>
#include <type_traits> //for concepts usage
#include <string>
// #include "map.h"
#include "stack.h"

template <typename T>
concept isComparable = requires(T a, T b) { // a concept to check if type is comparable
	{ a > b } -> std::same_as<bool>;
	{ a < b } -> std::same_as<bool>;
	{ a == b } -> std::same_as<bool>;
};

namespace data_structures
{
	enum Color
	{
		red,
		black
	};

	template <typename dataPoint>
	class RedBlackTree
	{
		// template<typename A,typename B>
		// friend class std_selfmade::map;
		//  public:
	public:
		struct node
		{
		public:
			struct node *left = nullptr;
			struct node *right = nullptr;
			struct node *parent = nullptr;
			dataPoint data;
			enum Color color = red;
			// some 'safe' to use functions
			node *gran()
			{
				if (this->parent)
				{
					return this->parent->parent;
				}
				return nullptr;
			} // Returns the grandparent of the node
			node *brother()
			{
				if (this->parent)
				{
					if (this == this->parent->left)
						return this->parent->right;
					else
						return this->parent->left;
				}
				return nullptr;
			} // Returns the sibling of the node
			node *uncle()
			{
				if (this->parent)
				{
					return this->parent->brother();
				}
				return nullptr;
			} // Returns the uncle of the node
		};
		struct stackStatus
		{
			node *addr = nullptr;
			unsigned char stat = 0;
		};

		constexpr node *getRoot()
		{
			node *temp = root;
			return temp;
		};

		node *getNode(dataPoint &value)
		{ // Gets a node with the given data

			struct node *temp = root;

			while (temp)
			{
				if (value < temp->data)
				{
					if (!temp->left) // nullptrCheck
						return nullptr;
					temp = temp->left;
				}
				else if (value > temp->data)
				{
					if (!temp->right) // nullptrCheck
						return nullptr;
					temp = temp->right;
				}
				else
				{
					return temp; // found
				}
			}
			return nullptr;
		}

		node *insertNode(node *toInsert)
		{
			// first do simple binary tree insertion
			struct node *temp = root;
			if (!root)
			{
				root = toInsert;
				temp = toInsert;
			}
			else
			{
				while (temp)
				{
					if (toInsert->data > temp->data)
					{
						if (!temp->right) //
						{
							toInsert->parent = temp;
							temp->right = toInsert;
							temp = toInsert; // go to the new node
							break;
						}
						else
							temp = temp->right;
					}
					else
					{
						if (!temp->left) // nullptrCheck
						{
							toInsert->parent = temp;
							temp->left = toInsert;
							temp = toInsert; // go to the new node
							break;
						}
						else
							temp = temp->left;
					}
				}
			}

			insertionBalance(temp);
			return toInsert;
		}

		bool deleteNode(node *toDelete)
		{ // Gets a node with the given data

			node *temp = toDelete;
			node *deleted = toDelete;

			if ((temp->left == nullptr) && (temp->right == nullptr))
			{
				// no children, node can be simply removed
				// remove parent linkage
				if (temp->parent)
				{
					if (temp == temp->parent->left)
					{
						temp->parent->left = nullptr;
					}
					else
					{
						temp->parent->right = nullptr;
					}
					deleted = temp;
				}
				else // root moment
				{
					root = nullptr;
				}
			}
			else if ((temp->left != nullptr) && (temp->right != nullptr))
			{
				// node has both left and right children, so the algorithm has to find lowest on the right or biggest on the left
				node *toReplace = temp->left;
				while (toReplace->right != nullptr)
				{
					toReplace = toReplace->right;
				} // finding biggest node on the right
				dataPoint *delBuf = new dataPoint;
				*delBuf = temp->data;
				temp->data = toReplace->data;
				toReplace->data = *delBuf;

				// here because we take the node after traveling far left, it should only have one child or less, if any then on the left.
				if (toReplace->parent->left == toReplace)
				{ // not sure about this if, but in case of 1 child on the right there might be no way to go to the right
					toReplace->parent->left = toReplace->left;
				}
				else
				{
					toReplace->parent->right = toReplace->left;
				}
				if (toReplace->left)
				{ // if child on the left is present
					toReplace->left->parent = toReplace->parent;
					toReplace->left->color = toReplace->color;
				}
				// at this point toReplace node is unlinked
				deleted = toReplace;
			}
			else if (temp->left != nullptr)
			{ // only left child is present
				if (temp->parent)
				{ // not the root node
					if (temp->parent->left == temp)
					{
						temp->parent->left = temp->left; // temp is on the left of the parent
					}
					else
					{
						temp->parent->right = temp->left; // ... right ...
					}
				}
				else
				{
					root = temp->left; // root had only one child and we removed root
				}
				temp->left->parent = temp->parent; //
				deleted = temp;
			}
			else
			{ // only right child is present
				if (temp->parent)
				{ // not the root node
					if (temp->parent->left == temp)
					{
						temp->parent->left = temp->right; // temp is on the left of the parent
					}
					else
					{
						temp->parent->right = temp->right; // ... right ...
					}
				}
				else
				{
					root = temp->right; // root had only one child and we removed root
				}
				temp->right->parent = temp->parent; //
				deleted = temp;
			}

			// at this point we have the deleted node
			RedBlackTree::deletionBalance(deleted); // the deleted node will always have the parent or else the balancing won't be done.
													// std::cout << "deleting node " << deleted->data << std::endl;//debug
			delete deleted;
			return true;
		}

		// private:
		struct node *root = nullptr;

		Color color(node *node_)
		{
			if (node_ == nullptr)
				return black;
			return node_->color;
		} // Returns the color of the node

		void rotateLeft(node *toRot)
		{
			if (!toRot || !toRot->right)
			{ // sanity check
				std::cerr << "Rotating node that shouldn't be rotated\n";
				return; // Cannot rotate if node is null or has no right child
			}
			// parent handling
			node *newParent = toRot->right; // better readability
			if (toRot->parent)
			{
				if (toRot->parent->left == toRot)
				{
					toRot->parent->left = newParent; // because after the left turn the right node will be tha parent of the left
				}
				else
				{
					toRot->parent->right = newParent; // same as before
				}
				newParent->parent = toRot->parent;
			}
			else
			{
				// rotated node is the root
				root = newParent;
				newParent->parent = nullptr;
			}

			// the rotation part itself
			node *buf = newParent->left; // the one that'll be unassigned, so we need to remember it
			newParent->left = toRot;	 // make rot a left child of it's right node
			toRot->parent = newParent;	 // make node of the right of the rot it's parent
			toRot->right = buf;
			if (buf)
			{
				buf->parent = toRot;
			}
		} // Performs a left rotation on the given node

		void rotateRight(node *toRot)
		{
			if (!toRot || !toRot->left)
			{ // sanity check
				std::cerr << "Rotating node that shouldn't be rotated\n";
				return; // Cannot rotate if node is null or has no right child
			}
			// parent handling
			node *newParent = toRot->left; // better readability
			if (toRot->parent)
			{
				if (toRot->parent->left == toRot)
				{
					toRot->parent->left = newParent; // because after the right turn the left node will be tha parent of the left
				}
				else
				{
					toRot->parent->right = newParent; // same as before
				}
				newParent->parent = toRot->parent;
			}
			else
			{
				// rotated node is the root
				root = newParent;
				newParent->parent = nullptr;
			}

			// the rotation part itself
			node *buf = newParent->right; // the one that'll be unassigned, so we need to remember it
			newParent->right = toRot;	  // make rot a right child of it's left node
			toRot->parent = newParent;	  // make node of the left of the rot it's parent
			toRot->left = buf;
			if (buf)
			{
				buf->parent = toRot;
			}
		} // Performs a right rotation on the given node

		void print(node *current, std::ostream &outStream = std::cout, bool useColors = true, std::string prefix = "", bool isLeft = false, int level = 0)
		{ // Prints the tree in a readable format

			if (!current)
			{
				return; // recursion end
			}

			print(current->right, outStream, useColors, prefix + (isLeft ? "       " : "       "), false, level + 1);

			outStream << prefix;
			outStream << (isLeft ? "       " : "       ");
			if (useColors)
			{
				outStream << "[" << ((current->color == red) ? "\x1b[31m" : "") << current->data << ((current->color == red) ? "\x1b[0m" : "");
			}
			else
			{
				outStream << "[" << ((current->color == red) ? "RED" : "") << current->data;
			}

			/*if (current->parent) { was polluting the output
				std::cout << ":" << current->parent->data;
			}
			else {
				std::cout << ":NPR";
			}*/
			outStream << "]" << std::endl;

			print(current->left, outStream, useColors, prefix + (isLeft ? "       " : "       "), true, level + 1);
		}

		void deletionBalance(node *temp)
		{
			while (temp != root && color(temp) == black)
			{
				if (!temp->parent)
					break; // safety check

				bool isLeftChild = (temp == temp->parent->left);
				node *brother = isLeftChild ? temp->parent->right : temp->parent->left;

				// brother is red (case 1)
				if (color(brother) == red)
				{
					brother->color = black;
					temp->parent->color = red;
					if (isLeftChild)
					{
						rotateLeft(temp->parent);
						brother = temp->parent->right;
					}
					else
					{
						rotateRight(temp->parent);
						brother = temp->parent->left;
					}
				}

				// exit if brother is null after rotation
				if (!brother)
					break;

				bool brotherLeftBlack = color(brother->left) == black;
				bool brotherRightBlack = color(brother->right) == black;

				// black brother with two black children (case 2)
				if (brotherLeftBlack && brotherRightBlack)
				{
					brother->color = red;
					temp = temp->parent;
					continue;
				}

				// black brother with one red child (case 3)
				if (isLeftChild)
				{
					if (brotherRightBlack)
					{
						if (brother->left)
							brother->left->color = black;
						brother->color = red;
						rotateRight(brother);
						brother = temp->parent->right;
					}
					// black brother with right red child (case 4)
					brother->color = temp->parent->color;
					temp->parent->color = black;
					if (brother->right)
						brother->right->color = black;
					rotateLeft(temp->parent);
				}
				else
				{
					if (brotherLeftBlack)
					{
						if (brother->right)
							brother->right->color = black;
						brother->color = red;
						rotateLeft(brother);
						brother = temp->parent->left;
					}
					// black brother with left red child (case 4)
					brother->color = temp->parent->color;
					temp->parent->color = black;
					if (brother->left)
						brother->left->color = black;
					rotateRight(temp->parent);
				}

				temp = root;
			}
			// Ensure root is black
			temp->color = black;
		} // Balances the tree after a node deletion

		void copyNode(node *thisNode, const node *otherNode)
		{
			if(!otherNode){//if tree is empty
				return;
			}
			if (thisNode == nullptr)
			{ // if it's a root node
				thisNode = new node;
				root = thisNode;
			}
			thisNode->data = otherNode->data;

			// create children nodes
			if (otherNode->left)
			{
				node *leftNode = new node;
				thisNode->left = leftNode;
				leftNode->parent = thisNode;
				copyNode(leftNode, otherNode->left);
			}

			if (otherNode->right)
			{
				node *rightNode = new node;
				thisNode->right = rightNode;
				rightNode->parent = thisNode;
				copyNode(rightNode, otherNode->right);
			}
			return;
		}

		void clear(node *temp)
		{
			if (temp == nullptr)
			{
				return;
			}

			if (temp->left)
			{
				clear(temp->left);
			}

			if (temp->right)
			{
				clear(temp->right);
			}
			delete temp;
			return;
		}

		void insertionBalance(node *temp)
		{
			// we-re standing on a new child node and it's color is red
			while ((temp != root) && (color(temp->parent) == red))
			{
				if (!temp->gran())
				{
					break; // if there's no grandparent than we can't determine on which side of it is our node is based
				}
				if (temp->parent == temp->gran()->left)
				{
					node *uncle = temp->gran()->right;
					if (color(uncle) == red)
					{ // case 2
						temp->parent->color = black;
						uncle->color = black;
						temp->gran()->color = red;
						temp = temp->gran();
					}
					else
					{
						if (temp == temp->parent->right)
						{ // fixing change of direction before insertion (case 4)
							temp = temp->parent;
							this->rotateLeft(temp);
						}
						temp->parent->color = black; // case 3
						temp->gran()->color = red;
						this->rotateRight(temp->gran());
					}
				}
				else
				{
					node *uncle = temp->gran()->left;
					if (color(uncle) == red)
					{ // case 2
						temp->parent->color = black;
						uncle->color = black;
						temp->gran()->color = red;
						temp = temp->gran();
					}
					else
					{
						if (temp == temp->parent->left)
						{ // case 4
							temp = temp->parent;
							this->rotateRight(temp);
						}
						temp->parent->color = black; // case 3
						temp->gran()->color = red;
						this->rotateLeft(temp->gran());
					}
				}
			}
			root->color = black; // case 1
		}

	public:
		RedBlackTree() noexcept
			requires isComparable<dataPoint>
		{
			this->root = nullptr;
		} // constructor

		RedBlackTree(RedBlackTree &&other)
		{
			this->root = other.root; // just transfer root node
			other.root = nullptr;
		} // move constructor

		RedBlackTree(const RedBlackTree &other) noexcept
		{
			copyNode(root, other.root);
		} // copy constructor
		RedBlackTree& operator=(const RedBlackTree& other) {
			clear();
		    copyNode(root,other.root);
		    return *this;
		}//Copyassignable

		RedBlackTree& operator=(RedBlackTree&& other) noexcept {
			clear();
		  this->root=other.root;
		  other.root=nullptr;
		  return *this;
		}// MoveAssignable

		~RedBlackTree()
		{
			clear();
		}

		dataPoint *insert(dataPoint &item)
		{ // Inserts a new node with the given data
			node *toInsert = new node;
			toInsert->data = item;
			insertNode(toInsert);
			return &toInsert->data;
		}

		dataPoint *get(dataPoint &value) // Gets a node with the given data,returns true if value is overwritten
		{
			node *temp = getNode(value);
			if (temp)
			{
				return temp->data;
			}
			return nullptr;
		}

		bool remove(dataPoint &value)
		{ // Deletes a node with the given data
			node *temp = getNode(value);
			if (!temp)
			{
				return false;
			}
			deleteNode(temp);
			return true;
		}

		void clear()
		{
			clear(root);
		} // removes every node in the tree

		void print(std::ostream &outStream = std::cout, bool useColors = true)
		{											 // Prints the tree in a readable format
			this->print(root, outStream, useColors); // just a wrapper to make it public
		}

		bool isEmpty()
		{
			return (root == nullptr);
		}

		bool operator==(const RedBlackTree &other)
		{
			if (isEmpty() || other.isEmpty())
			{
				return other.isEmpty() == isEmpty();
			}
			stack<stackStatus> thisStack;
			stack<stackStatus> otherStack;

			node *tempThis = root;
			node *tempOther = other.root;
			thisStack.push(stackStatus{root, 0});
			otherStack.push(stackStatus{other.root, 0});
			while ((!otherStack.empty()) || (!thisStack.empty()))
			{
				while (!thisStack.empty())
				{
					stackStatus *parent;
					parent = thisStack.peek();
					tempThis = parent->addr;

					if ((tempThis->left) && (parent->stat < 1))
					{
						parent->stat = 1;

						tempThis = tempThis->left;
						thisStack.push(stackStatus{tempThis, 0});
						continue;
					}
					if (parent->stat < 2)
					{
						// std::cout<<tempThis->data<<"-A";
						parent->stat = 2;

						break;
					}

					if ((tempThis->right) && (parent->stat < 3))
					{
						parent->stat = 3;

						tempThis = tempThis->right;
						thisStack.push(stackStatus{tempThis, 0});
						continue;
					}

					thisStack.pop();
				}

				while (!otherStack.empty())
				{
					stackStatus *parent;
					parent = otherStack.peek();
					tempOther = parent->addr;

					if ((tempOther->left) && (parent->stat < 1))
					{
						parent->stat = 1;

						tempOther = tempOther->left;
						otherStack.push(stackStatus{tempOther, 0});
						continue;
					}
					if (parent->stat < 2)
					{
						// std::cout<<tempOther->data<<"-B\n";
						parent->stat = 2;

						break;
					}

					if ((tempOther->right) && (parent->stat < 3))
					{
						parent->stat = 3;

						tempOther = tempOther->right;
						otherStack.push(stackStatus{tempOther, 0});
						continue;
					}

					otherStack.pop();
				}
				if ((thisStack.empty() != otherStack.empty()) || (!thisStack.empty() && !otherStack.empty() && (tempThis->data != tempOther->data)))
				{
					return false;
				}
			}

			return true;
		}
	};
}