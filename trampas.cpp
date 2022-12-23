	void join(node* n1, node* n2){
		if(n1 == nullptr){
			root = n2;
			return;
		}
		if(n2 == nullptr){
			root = n1;
			return;
		}
		node* temp = n1;
		while(temp->right != nullptr)
			temp = temp->right;
		splay(temp);
		temp->right = n2;
		n2->father = temp;
	}

	pair<node*, node*> split(node *n){
		if(n == nullptr)
			return make_pair(nullptr, nullptr);
		splay(n);
		node* temp = n->left;
		n->left = nullptr;
		if(temp != nullptr)
			temp->father = nullptr;
		return make_pair(temp, n);
	}