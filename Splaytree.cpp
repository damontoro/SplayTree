#pragma once

#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class Splaytree
{
	using nodo = unique_ptr<Splaytree<T>>;
private:
	T valor;
	nodo padre;
	nodo derecha, izquierda;

	void rotRight(){

	}
	void rotLeft(){
		
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
