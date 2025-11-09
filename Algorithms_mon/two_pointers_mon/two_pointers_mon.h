#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;


//? returns pointers{?,?}
pair<long double, long double> two_pointers_mon(vector<long double>& vec, long double target){

    sort(vec.begin(), vec.end());
    long double sum;
    auto it1 = vec.begin(),
    it2 = vec.end()-1;

    while(*it1<=*it2){
        sum = *it1+*it2;
        if(sum==target){
            return {*it1, *it2};
        }else if(sum<target){
            it1++;
        }else if(sum>target){
            it2--;
        }
    }

    return {-1,-1};
}