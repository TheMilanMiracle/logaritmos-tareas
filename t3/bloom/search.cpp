#include <bits/stdc++.h>
#include "./bloom.h"

long int sec_search(std::vector<std::string> A){
    long int counter = 0;

    FILE *names = fopen("./bloom/Popular-Baby-Names-Final.csv", "r");

    for(long unsigned int i = 0; i < A.size(); i++){
        char buff[512];

        while(fgets(buff, 512, names)){
            std::string s(buff);

            s[s.size() - 1] = 0;

            if(s.size() < A[i].size()){continue;}

            for(int j = 0; j < s.size() - A[i].size(); j++){
                if(s.find(A[i], j) != std::string::npos){counter++;}
            }
        }

        fseek(names, 0, SEEK_SET);
    }

    return counter;
}