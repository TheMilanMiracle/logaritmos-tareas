#include <bits/stdc++.h>
#include "./bloom.h"

long int sec_search(std::string str){
    long int count = 0;

    std::ifstream names("./lib/csv/Popular-Baby-Names-Final.csv");
    std::string buff;

    while(std::getline(names, buff)){
        if(buff.find(str) != std::string::npos){
            count++;
        }
    }

    return count;
}