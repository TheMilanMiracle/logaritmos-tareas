#include <bits/stdc++.h>
#include "./bloom/bloom.h"


int main(){
    
    long int N = 5;
    double P = 0.0;

    std::vector<std::string> A = get_name_list(P, N);

    std::cout << "[";

    for(int i = 0; i < N; i++){
        std::cout << A[i] << ", ";
    }

    std::cout << "]" << std::endl;

    std::cout << sec_search(A) << std::endl;

    return 0;

}