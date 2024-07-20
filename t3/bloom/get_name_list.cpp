#include <bits/stdc++.h>
#include "./bloom.h"

std::pair<std::vector<std::string>, std::vector<std::string>> get_name_list(double p, long int N){
    std::ifstream films("./lib/csv/Film-Names.csv");
    std::ifstream names("./lib/csv/Popular-Baby-Names-Final.csv");

    unsigned long int n = N * p, f = N * (1.0 - p);

    if(n + f < N){n++;}

    std::cout << f << ", " << n << std::endl;

    std::string buff;

    std::vector<std::string> Films, Names;
    while(f--){
        std::getline(films, buff);

        buff += '\%'; //to make sure films won't match
        
        Films.push_back(buff);

        if(films.eof()){
            films.clear();
            films.seekg(0, std::ios::beg);
        }
    }

    std::getline(names, buff);
    while(n--){
        std::getline(names, buff);
        
        Names.push_back(buff);
    }

    films.close();
    names.close();

    return {Names, Films};
}