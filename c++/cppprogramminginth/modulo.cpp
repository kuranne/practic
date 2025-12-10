#include <iostream>
#include <vector>

int main(){
    int i, j, n, ques, count=0, isEqual;
    std::cin >> n;
    std::vector<int> temp(n, 0);
    for(i=0; i<n; i++){
        std::cin >> ques;
        temp[i] = ques%42;
        if(i!=0){ isEqual = 0; for(j=0; j<i; j++){ if(temp[j] == temp[i]){ isEqual = 1; break;}} if(isEqual==1){continue;}}
        count += 1;
    }
    std::cout << count << std::endl;
    return 0;
}