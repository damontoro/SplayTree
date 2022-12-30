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
		node *y = n->left;
		n->left = y->right;
		if (y->right != nullptr) {
			y->right->father = n;
		}
		y->father = n->father;
		if (n->father == nullptr) {
			this->root = y;
		} else if (n == n->father->right) {
			n->father->right = y;
		} else {
			n->father->left = y;
		}
		y->right = n;
		n->father = y;
	}

	void rotLeft(node* n){
		node *y = n->right;
		n->right = y->left;
		if (y->left != nullptr) {
			y->left->father = n;
		}
		y->father = n->father;
		if (n->father == nullptr) {
			this->root = y;
		} else if (n == n->father->left) {
			n->father->left = y;
		} else {
			n->father->right = y;
		}
		y->left = n;
		n->father = y;
	}

	void splay(node* n){
		while(n && n->father != nullptr){
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
		if(n) root = n;
	}
	
public:

	node *find(T elem){
		node *aux = root;
		if(!aux) return nullptr;
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
			else if(aux->value > ins && aux->left != nullptr)
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
		node *aux = root;
		if(!aux) return;
		while((aux->left != nullptr || aux->right != nullptr) && aux->value != del){
			if(del > aux->value){
				if(aux->right != nullptr)
					aux = aux->right;
				else
					break;
			}
			else if(del < aux->value){
				if(aux->left != nullptr)
					aux = aux->left;
				else
					break;
			}
		}
		if(aux->value != del) splay(aux);
		else{
			if(!aux->left && !aux->right){
				if(aux->father->left == aux) aux->father->left = nullptr;
				else aux->father->right = nullptr;
			}
			else if(aux->left && !aux->right){
				aux->left->father = aux->father;
				if(aux->father && aux->father->left == aux) aux->father->left = aux->left;
				else if(aux->father) aux->father->right = aux->left;
			}
			else {
				//Find the smallest element in the right subtree
				node *search = aux->right;
				while(search->left != nullptr) search = search->left;

				if(search->father->left == search) 
					search->father->left = search->right;
				else 
					search->father->right = search->right;

				search->father = aux->father;
				search->left = aux->left;
				search->right = aux->right;
				if(aux->father && aux->father->left == aux) 
					aux->father->left = search;
				else if(aux->father)
					aux->father->right = search;
				if(aux->left) aux->left->father = search;
				if(aux->right) aux->right->father = search;

				if(aux == root) root = search;
			}
			splay(aux->father);
			delete aux;
		}

	}

	Splaytree(){
		root = nullptr;
	}
	~Splaytree(){
	}
};
