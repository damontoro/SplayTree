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

	void join(SplayTree<T> *n){ //This joins the tree N to this tree
		if(n.root == nullptr) return;
		if(this.root == nullptr){
			this.root = n.root; return;
		}
		node *aux = this.root;
		while(aux->right != nullptr) aux = aux->right;
		splay(aux);
		aux->right = n.root;
		n.root->father = aux;
	}

	node *split(node *n){ //This splits the tree given a node
		splay(n);
		node *small = n;
		this.root = n->right;
		if(this.root)
			this.root->father = nullptr;

		small->right = nullptr;
		small->father = nullptr;
		n = nullptr;
		return small;
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
