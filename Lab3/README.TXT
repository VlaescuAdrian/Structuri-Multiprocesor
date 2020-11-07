Laborator SM - Retea Omega - Implementare Software
Vlaescu Adrian-Cristian 342C2

Dupa cum spunea si in enunt, am folosit o retea 8 * 8 (de preferat, dar
numarul de intrari si iesiri poate fi dat de la tastatura) cu numarul de conexiuni 
dat de la tastatura, un numar <= 8.
Am tratat cateva cazuri in care, de exemplu, o intrare nu poate aparea de mai 
multe ori(000->000 si 000->001 - o sa afiseze un mesaj de eroare pentru a doua 
conexiune). Acelasi lucru se intampla si daca avem mai multe iesiri identice 
pe diferite conexiuni. Stiu ca ai spus la laborator ca o sa testezi doar pe cazuri valide,
dar am implementat si pentru cazurile cand nu s-ar putea realiza conexiuni intre
diferite inputuri si outputuri.
Matricea matrix arata daca la etajul respectiv s-a mai trecut printr-o intrare la un moment
dat sau nu pentru stabili daca conexiunea curenta poate trece prin punctul respectiv sau nu,
caz in care este anulata.

Rulare:
	gcc omega.c -lm
1.Trebuie introdus numarul de intrari si numarul de conexiuni
2.Pentru fiecare conexiune in parte se introduce un input si un output
3.Pentru toate conexiunile in parte va afisa transmisia directa/inversa
de pe fiecare comutator(doar daca conexiunea se poate realiza la acel moment)