Cosas a tener en cuenta para la implementación:

Los algoritmos para buscar, insertar y borrar una clave en un ABBA son exactamente los mismos
que los de un árbol binario de búsqueda convencional, salvo que incorporan como última acción
una flotación.

La flotación se inicia en un nodo, que llamaremos origen de la flotación, que es:
	* En buscar, el nodo buscado, o el último nodo visitado, si el nodo buscado no se encuentra en
	el árbol.

	* En insertar, el nodo insertado, o el nodo que ya contenía dicha clave, si no se ha realizado la
	inserción.

	* En borrar, el padre del nodo borrado, o el último nodo visitado, si el nodo a borrar no se
	encuentra en el árbol


Casos de la flotación:

	1. Si q es el nodo raíz, la flotación termina.

	2. Si q es hijo directo de la raíz, se desencadena una rotación RR o LL idéntica a la de los AVL,
	que hace que q pase a ser la raíz. En la Fig. 1 (tomada de [1]) se muestra el caso RR. La
	flotación termina.

	3. Si q tiene padre p y abuelo gp, se desencadena una rotación LL, LR, RL o RR, según que q sea
	respectivamente el hijo izquierdo del hijo izquierdo de gp, el hijo derecho del hijo izquierdo
	de gp, el hijo izquierdo del hijo derecho de gp, o el hijo derecho del hijo derecho de gp. Las
	rotaciones LR y RL son exactamente las mismas que las de los AVL, mientras que las LL y
	RR son ligeramente distintas. En la Fig. 2 (tomada de [1]) se muestran las rotaciones RR y
	RL. La flotación continua en la nueva posición de q.


Rotaciones:

	Zig(rotacion derecha en AVL): se hace cuando el nodo no tiene abuelo y es un hijo izquierdo
	Zag(rotacion izquierda en AVL): se hace cuando el nodo no tiene abuelo y es un hijo derecho
	Zig-Zig(LL): Se hace cuando el nodo es un hijo izquierdo y su padre es un hijo izquierdo
	Zag-Zag(RR): Se hace cuando el nodo es un hijo derecho y su padre es un hijo derecho
	Zig-Zag(LR): Se hace cuando el nodo es un hijo izquierdo y su padre es un hijo derecho
	Zag-Zig(RL): Se hace cuando el nodo es un hijo derecho y su padre es un hijo izquierdo


Funcion flotar(Splay):

	Lleva un nodo a la raiz haciendo una serie de rotaciones.
