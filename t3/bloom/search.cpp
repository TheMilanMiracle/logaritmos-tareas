#include <bits/stdc++.h>
#include "./bloom.h"

long int sec_search(std::vector<std::string> A){
    long int count = 0;

    std::ifstream names("./bloom/Popular-Baby-Names-Final.csv");
     std::string buff;
    for(long unsigned int i = 0; i < A.size(); i++){

        while(std::getline(names, buff)){
            if(buff.find(A[i]) != std::string::npos){
                std::cout << "found " << A[i] << " in " << buff << std::endl;
                count++;
            }
        }

        names.clear();
        names.seekg(0, std::ios::beg);
    }

    return count;
}