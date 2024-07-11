#include <bits/stdc++.h>
#include "./bloom.h"

std::vector<std::string> get_name_list(double p, long int N){

    std::vector<std::string> A(N);

    FILE *film = fopen("./bloom/Film-Names.csv", "r");
    FILE *names = fopen("./bloom/Popular-Baby-Names-Final.csv", "r");

    if(!film){std::cout << "no film" << std::endl;}
    if(!names){std::cout << "no names" << std::endl;}

    unsigned long int n = N * (1.0 - p), f = N * p;

    std::cout << f << ", " << n << std::endl;

    char buff[1024];

    while(f--){

        fgets(buff, 1024, film);

        std::string s(buff);

        s[s.size() - 1] = 0;

        A[--N] = s;

    }

    fgets(buff, 1024, names);
    n++;
    while(n--){

        fgets(buff, 1024, names);

        std::string s(buff);

        s[s.size() - 1] = 0;

        A[--N] = s;

    }

    return A;

}