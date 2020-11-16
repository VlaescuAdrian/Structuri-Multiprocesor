Vlaescu Adrian

Laborator Structuri Multiprocesor - OpenMP

Algoritgm: Inmultirea a doua matrici folosind OpenMP.

Size-ul matricilor este setat la rulare, dandu-se o valoare de la tastatura.

Valoarea elementelor este:
-pentru a: i + j
-pentru b: modul(i-j)

Numarul de threaduri este setat la numarul de procesoare ale PC-ului.

Se foloseste pragma omp parallel cu variabilele share-uite a,b,c si 
private fiind i,j,k. Se foloseste schedule static pentru a mapa blocurile
de iteratie intr-un mod de genul round-robin. Apoi, se calculeaza clasic
produsul matricilor si in final afisez matricea c, matricea rezultat 
impreuna cu timpul de executie si numarul de threaduri.

Rulare:
gcc matrix_multi_openMP.c -fopenmp -o multi_openmp
./multi_openmp

Apoi, se introduce n de la tastatura.