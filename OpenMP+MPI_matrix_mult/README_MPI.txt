Vlaescu Adrian

Laborator Structuri Multiprocesor - MPI

Algoritgm: Inmultirea a doua matrici folosind mpi scatter, gather and bcast.

SIZE-ul matricilor este un define si trebuie sa fie multiplu de numarul de procesoare cu care
rulam. De ex: daca rulam mpirun -np 4 ./executabil, inseamna ca SIZE trebuie sa fie 4, 8, 12 etc.

Folosesc bcast pentru a trimite matricea B catre toate procesele, iar scatter pentru a trimite matricea
A sectionata in functie de numarul procesului curent, SIZE si numarul total de procese. Folosim gather pentru
a pune in matricea C rezultatele in concordanta cu parametrii de la Scatter pentru matricea A.
Inmultirea se face clasic doar ca fiecare proces va avea un anumit numar de elemente din matrice de calculat(from and to in cod).


Rulare:
mpicc matrix_multi_MPI.c -o multi_mpi
mpirun -np 4 ./multi_mpi

in cod SIZE-ul matricilor este 4 si fiecare element este calculat dupa formula i+j, i=linie, j=coloana.
