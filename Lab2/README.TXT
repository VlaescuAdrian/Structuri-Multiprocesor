Vlaescu Adrian-Cristian
342C2

Lab 2 Structuri Multiprocesor

Am facut graficele si pentru exercitiul 8 din laborator, dar si pentru algoritmul de 
sortare bubble sort.

Atat O(1), cat si T(1) au valoarea egala cu n^2; valoarea lui O(n) este nlog2(n);
Problema a fost pentru valoarea T(n) unde am gasit informatii de genul:
pentru un numar de procesoare mai mic decat n/2, T(n) va avea valoarea n^2/2p;
pentru un numar de procesoare mai maredecat n/2, T(n) va avea valoarea n;

Asa ca am decis ca pentru p = n, T(n) = n; 

Am calculat accelerarea, eficienta, redundanta, utilizarea si
factorul de calitate dupa formulele din laborator si am scris atat pentru
exercitiul 8 cat si pentru bubble sort fisiere octave/matlab pentru a
desena plot-urile.

Despre bubble sort am gasit informatii aici: https://issuu.com/williamss98675d/docs/11319ijcsit05