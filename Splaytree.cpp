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
	
	//Hacer find del elemento a borrar, buscar el mas grande de la izquierda, hacerle splay y pegarle el arbol derecho
	void remove(T del){
		node *aux = find(del);
		if(!aux) return;
		node *left = aux->left, *right = aux->right;
		delete(aux);
		root = nullptr;
		if(!left){
			this->root = right;
			right->father = nullptr;
			return;
		}
		if(!right){
			this->root = left;
			left->father = nullptr;
			return;
		}
		left->father = nullptr;
		right->father = nullptr;
		node *aux2 = left;
		while(aux2->right != nullptr)
			aux2 = aux2->right;
		splay(aux2);
		aux2->right = right;
		right->father = aux2;
		this->root = aux2;
	}

	Splaytree(){
		root = nullptr;
	}
	~Splaytree(){
	}
};
