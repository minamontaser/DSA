//! binary search
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int binary_search_mon(vector<long long>& vec , int target){
    long long low = 0
    , high = vec.size()-1 , mid, value;
    while(low<=high){
        mid = low+(high-low)/2;
        value = vec[mid];
        if(value<target){
            low = mid + 1;
        }else if(value>target){
            high = mid - 1;
        }else{
            return mid;
        }
    }

    return -1;
}