JOGO DOS 15
-------------------------------------------

Descrição do programa:
        Neste programa “jogo15.cpp” temos todas as estratégias de procura, sendo elas, DFS, BFS,IDFS, gulosa e A*, sendo que as últimas duas usam duas heurísticas: peças fora do lugar e Manhattan distance. Os nós, que representam as várias configurações são representadas numa classe, que contém o array das posições de cada peça na configuração, a posição zero, a profundidade e uma string com o caminho até chegar á configuração final. 

-------------------------------------------

Requerimentos:
	Compilador c++ versão 11.
	OS linux. (necessário para imprimir informação sobre a memória utilizada)

-------------------------------------------

Instruções para compilar e executar:
	Compilar: g++ -std=c++11 all.cpp
	executar: ./a.out

-------------------------------------------

Execução:
	Irá ser pedido as configurações iniciais e finais que devem ter o aspeto do seguinte exemplo: “1 2 3 4 5 6 8 12 13 9 0 7 14 11 10 15”.

-------------------------------------------

NOTA:
Como alterar entre cada um dos métodos:
     Na função main do programa estão comentados os diferentes métodos, da forma: “bool ok = nome do método;” e para testar cada um deles basta retirar o comentário na linha do método que quer testar.

Diogo Pereira           201605323
Afonso Fernandes        291696852
Lucas Paula             201608440


