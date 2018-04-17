15 PUZZLE
-------------------------------------------

Program description:
        In this program “jogo15.cpp” we have some search algorithms, being them: DFS, BFS,IDFS, greedy and A*. For the last 2 we use two different heuristics: misplaced tiles and Manhattan distance. The nodes, which represent the configurations on the tree are repesented on a class, which has an array with the position of each tile, the position with no tile (0),depth and a string with the path to the final node. 

-------------------------------------------

Requeriments:
	C++ complier version 11.
	OS linux. (to use the function which prints the memory used)

-------------------------------------------

Compiling and execution tips:
	Compiling: g++ -std=c++11 all.cpp                                                                                             Executing: ./a.out

-------------------------------------------

Executing:
	Is't going to be asked the start and finish configuration, which should be given the following way: “1 2 3 4 5 6 8 12 13 9 0 7 14 11 10 15”.

-------------------------------------------

Notice:
how to change each method:
     In the function main there are different methods commented, like this: “bool ok = nome do método;”. To test each one of them you need to uncomment the method you want to use.

| Author            |   UP Number       |
|-------------------|:-----------------:|
|Diogo Pereira      |   201605323       |
|Afonso Fernandes   |   201696852       |

