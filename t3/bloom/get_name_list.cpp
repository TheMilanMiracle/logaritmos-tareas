#include <bits/stdc++.h>
#include "./bloom.h"

std::vector<std::string> get_name_list(double p, long int N){

    std::vector<std::string> A(N);

    std::ifstream films("./bloom/Film-Names.csv");
    std::ifstream names("./bloom/Popular-Baby-Names-Final.csv");

    unsigned long int n = N * p, f = N * (1.0 - p);

    if(n + f < n){n++;}

    std::cout << f << ", " << n << std::endl;

    std::string buff;

    while(f--){
        std::getline(films, buff);

        buff += '\%';
        
        A[--N] = buff;
    }

    std::getline(names, buff);
    while(n--){
        std::getline(names, buff);
        
        A[--N] = buff;
    }

    films.close();
    names.close();

    return A;

}