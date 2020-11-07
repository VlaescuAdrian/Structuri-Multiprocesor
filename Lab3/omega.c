#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h> 


int matrix[100][100];


void redirection(int *input, int number_of_entries,int j) {
    if (input[j] < (number_of_entries / 2)) {
        input[j] = input[j] * 2;
    }
    else 
    {
        input[j] = (input[j] * 2 + 1) % number_of_entries;
    }
}

int decide(int j,int i,int floors, int *copy_input, int *copy_output, char str[], int *input) {
    if (matrix[input[j]][i + 1] == 1) {
        printf("Pe comutatorul de la etajul %d nu se mai poate realiza o transmisie directa/inversa,\ndeci nu se mai poate realiza conexiunea intre %d si %d\n",
        floors - i - 1,copy_input[j],copy_output[j]);
        return 1;
    }
    else
    {
        matrix[input[j]][i + 1] = 1;
        printf("Comutator etajul %d - transmisie %s\n", floors - i - 1,str);
        return 0;
    }
}

bool IsPowerOfTwo(int x)
{
    return (x != 0) && ((x & (x - 1)) == 0);
}
int main(int argc, char* argv[])
{

    //am ales sa fie numarul de intrari si iesiri dat de la tastatura
    printf("Introduceti numarul de intrari si iesiri pentru Reteaua Omega:\n\n");
    int number_of_entries;
    scanf("%d", &number_of_entries);

    if (IsPowerOfTwo(number_of_entries) == false) {
        printf("Eroare: Numarul de intrari nu este putere a lui 2!\n");
        return 0;
    }
    
    printf("Introduceti numarul de conexiuni Reteaua Omega:\n");
    int connections;
    scanf("%d", &connections);
    if (connections > number_of_entries) {
        printf("Eroare: mai multe conexiuni decat intrari!\n");
        return 0;
    }

    printf("Retea cu %d intrari si %d iesiri\n",number_of_entries,number_of_entries);
    printf("Retea cu %d conexiuni\n\n",connections);

    //vectorii cu intrarile si iesirile din retea
    int input[connections], output[connections];
    int copy_input[connections], copy_output[connections];

    for (int i = 0 ; i < connections ; i++) {
        printf("Introduceti intrarea %d si iesirea %d\n",i,i);
        scanf("%d", &input[i]);
        copy_input[i] = input[i];
        scanf("%d", &output[i]);
        copy_output[i] = output[i];

        printf("Intrarea %d are iesirea %d\n\n",input[i],output[i]);
    }

    int floors = log(number_of_entries) / log(2);
    printf("Numarul de etaje este: %d\n", floors);


    

    for (int j = 0 ; j < connections ; j++) {
        printf("\nAvem conexiunea de la %d la %d\n", input[j], output[j]);
        int xor = input[j] ^ output[j];

        //redirectarea inseamna unde ar trebuie sa mearga fiecare numar de la 0 la nr intrari pe ficare 
        //comutator
        redirection(input,number_of_entries,j);

        for(int i = 0;  i < floors; i++)
		{
            //dorim sa vedem daca bitul corespunzator etajului este 0 sau 1
            //adica daca este 0 va fi o transmisie directa si invers in cazul lui 1
            int first_bit = xor & (1 << (floors-i-1));
            first_bit = first_bit >> (floors-i-1);

            //transmisie directa
            if (first_bit == 0) {
                redirection(input,number_of_entries,j);
                char str[] = "DIRECTA(C0 = C1 = 0)";
                int should_continue = decide(j,i,floors,copy_input,copy_output,str,input);
                if (should_continue) break;
                
            }
            else //transmisie inversa
            {
                //inseamna ca input[j] va urca sau cobora o pozitie in functie daca trece de pe 0 pe 1 sau invers
                //daca e pe 0 (pozitie para) coboara pe 1 (input[j] + 1)
                if (input[j] % 2) {
                    input[j]--;
                }
                else
                {
                    input[j]++;
                }

                //redirectionam ruta
                redirection(input,number_of_entries,j);

                char str[] = "INVERSA(C0 = C1 = 1)";
                int should_continue = decide(j,i,floors,copy_input,copy_output,str,input);
                if (should_continue) break;
                
                
            }
            
        }
    }

    return 0;

}
