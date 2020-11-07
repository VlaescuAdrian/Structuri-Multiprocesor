Laborator 1 - SM

Rulare: gcc crcw.c
	gcc crew.c -lm

Dimensiunea matricelor este data de #define N value; poti modifica aceasta 
valoare. Am ales sa nu preiau date din fisier deoarece nu era relevant 
acest lucru; important este sa functioneze algoritmul.

	Algoritm CRCW-PRAM - implementare seriala

Am alocat dinamic cele trei matrici(A,B,C) si tabloul 3D P. Am ales ca matricile
A si B sa aiba valorile pe fiecare pozitie egala cu numarul coloanei plus 
numarul liniei.
Fiecare procesor calculeaza produsul A(i,k) * B(k,j), dupa care se face scrierea
concurenta a procesoarelor. Afisez matricea C si dezaloc memoria alocata

	Algoritm CREW-PRAM - implementare seriala

Am alocat dinamic cele trei matrici(A,B,C) si tabloul 3D P.
Fiecare procesor executa un pas de calcul si log2n pasi pentru 
reducerea paralela, dupa care se face insumarea din fiecare tablou 2D din P
in C[i][j] pentru a contura matricea finala.
In principiu, algoritmul este dupa pseudocodul din laborator, exact ca si 
la CRCW-PRAM.

Implementarile sunt seriale, nu in paralel (PS: asa am inteles ca ai spus la 
primul lab; ca se accepta implementarile seriale; important era sa intelegem 
algoritmul)