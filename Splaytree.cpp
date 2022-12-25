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
		node* right;
		node *left;
	};

private:
	node *root = nullptr;

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
		root = n;
	}

/*
	void join(node *n){ //This joins the tree N to this tree
		if(n == nullptr) return;
		if(this.root == nullptr){
			this.root = n; return;
		}
		node *aux = this.root;
		while(aux->right != nullptr) aux = aux->right;
		splay(aux);
		aux->right = n;
		n->father = aux;
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
	*/

public:

	node *find(T elem){
		node *aux = root;
		while(aux->left != nullptr || aux->right != nullptr){
			if(elem > aux->value && aux->right != nullptr)
				aux = aux->right;
			else if(elem < aux->value && aux->left != nullptr)
				aux = aux->left;
			else
				break;
		}
		splay(aux);
		return aux->value == elem ? aux : nullptr;
	}

	void insert(T ins){
		node *aux = root;
		node *ne;
		if(!aux) {
			root = new node{ins, nullptr, nullptr, nullptr};
			return;
		}
		while(aux->left != nullptr || aux->right != nullptr){
			if(aux->value <= ins && aux->right != nullptr)
				aux = aux->right;
			else if(aux->left != nullptr)
				aux = aux->left;
			else
				break;
		}
		if(aux->value <= ins)
			aux->right = ne = new node{ins, aux, nullptr, nullptr};
		else
			aux->left = ne = new node{ins, aux, nullptr, nullptr};
		splay(ne);
	}
	
	void remove(T del){
		
	}

	Splaytree(){
		root = nullptr;
	}
	~Splaytree(){}
};
