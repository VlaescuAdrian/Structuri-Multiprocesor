#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>


struct list
{
	int type;
	int to[2];
};

int n, nr_levels;
list **levels;

std::string to_bit(int number) {
	std::string rez;
	char c;

	while(number) {
		rez += (number % 2 + '0');
		number /= 2;
	}

	std::reverse(rez.begin(), rez.end());

	//completam bitii si pentru restul de niveluri
	while(rez.size() < nr_levels){
        rez = "0" + rez;
	}
	return rez;
}


//se face shuffle la retea
void shuffle()
{
	int i, j, to;

	for(i = 0 ; i < n / 2 ; i ++) {
		levels[0][i].to[0] = i;
		levels[0][i].to[1] = n / 2 + i;
	}

	for(i = 0 ; i < n / 2; i ++) {
		levels[3][i / 2].to[i % 2] = 2 * i;
	}

	for(; i < n ; i++) {
		levels[3][i / 2].to[i % 2] = (2 * i + 1) - n;
	}
	for(i = 1 ; i < nr_levels - 2; i ++) {
		for(j = 0 ; j < n / 4 ; j++) {
			levels[i][j].to[0] = j % (n / 2);
			levels[i][j].to[1] = (j + 2) % (n / 2);
		}

		for(j = 0; j < n / 4 ; j++) {
			levels[i][j + n / 4].to[0] = n / 2 + j % (n / 2);
			levels[i][j + n / 4].to[1] = n / 2 + (j + 2) % (n / 2);
		}
	}
	for(i = 0 ; i < n / 2 ; i++) {
		levels[nr_levels - 1][i].to[0] = 2 * i;
		levels[nr_levels - 1][i].to[1] = 2 * i + 1;
	}
	for(i = 0 ; i < nr_levels ; i++)
		for(j = 0 ; j < n / 2 ; j++)
			levels[i][j].type = -1;
}

int getPath(int src, std::string con)
{
	int to = src % 2;
	for(int j = 0 ; j < nr_levels; j++) {
		to = (con[j] - '0') ^ (src % 2);
		src = levels[j][src / 2].to[to];
	}

	return src;
}

bool checkValidity(int src, std::string con)
{
	int to = src % 2;
	for(int j = 0 ; j < nr_levels; j++) {
		to = (con[j] - '0') ^ (src % 2);
		if(levels[j][src / 2].type == -1)
			levels[j][src / 2].type = con[j] - '0';
		else if(levels[j][src / 2].type != (con[j] - '0'))
			return false;
		else
			src = levels[j][src / 2].to[to];
	}

	return true;

}

int main(int argc, char* argv[])
{
	int i, in, out, pairs;

	std::cout<<"Numarul n este: " ;
	std::cin >> n;
	std::cout<<"Numarul de perechi este : " ;
    std::cin >> pairs;
	nr_levels = 2*floor(log2(n)) - 1;

	levels = (list **)calloc(nr_levels, sizeof(list*));

	for(i = 0 ; i < nr_levels ; i++)
		levels[i] = (list *)calloc(n / 2, sizeof(list));

	shuffle();

	for(i = 0 ; i < pairs ; i++) {
		std::cout<<"Intrarea "<< i <<" este: " ;
        std::cin >> in;
		std::cout<<"Iesirea "<< i <<" este: " ;
        std::cin >> out;
        int bkt = 0;

		for(int i = 0 ; i < pow(2,nr_levels) - 1; i++) {
			if(getPath(in, to_bit(bkt)) == out) {
				if(checkValidity(in, to_bit(bkt))) {
					int etaj = 0;

					for (int j = 0; j < to_bit(bkt).size(); j++){

						if (to_bit(bkt)[j] == '0') {
							std::cout << "Conexiunea la etajul " << etaj <<" pe comutator este directa" "\n";
						}
						else
						{
							std::cout << "Conexiunea la etajul " << etaj <<" pe comutator este inversa" "\n";
						}
						
						etaj++;
					}
					
					break;
				}
				else
					continue;
			}
			bkt++;
		}
    }

	return 0;
}