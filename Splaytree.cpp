#pragma once

#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class Splaytree
{
	struct node {
		T value;
		node* father;
		node* right, left;
	};

private:
	node *root;

	void rotRight(node* n){
		node* temp = n->left;
		n->left = temp->right;
		temp->right = n;
		temp->father = n->father;
		n->father = temp;
		if(n->left != nullptr)
			n->left->father = n;

		if(temp->father != nullptr){
			if(temp->father->left == n)
				temp->father->left = temp;
			else
				temp->father->right = temp;
		}
	}

	void rotLeft(node* n){
		node* temp = n->right;
		n->right = temp->left;
		temp->left = n;
		temp->father = n->father;
		n->father = temp;
		if(n->right != nullptr)
			n->right->father = n;
			
		if(temp->father != nullptr){
			if(temp->father->left == n)
				temp->father->left = temp;
			else
				temp->father->right = temp;
		}
	}

	void splay(node* n){
		while(n->father != nullptr){
			if(n->father->father == nullptr){
				if(n->father->left == n){
					rotRight(n->father);
				}else{
					rotLeft(n->father);
				}
			}else{
				if(n->father->left == n){
					if(n->father->father->left == n->father){
						rotRight(n->father->father);
						rotRight(n->father);
					}else{
						rotRight(n->father);
						rotLeft(n->father);
					}
				}else{
					if(n->father->father->left == n->father){
						rotLeft(n->father);
						rotRight(n->father);
					}else{
						rotLeft(n->father->father);
						rotLeft(n->father);
					}
				}
			}
		}
	}
	
	void join(node* n){ //This joins the tree N to this tree
		
	}

	node* split(node *n){ //This splits the tree at node N and returns the left tree (small one)
		
	}

public:

	bool find(T elem){
		
	}
	void insert(T ins){
		
	}
	void remove(T del){

	}


	Splaytree(/* args */){}
	~Splaytree(){}
};
