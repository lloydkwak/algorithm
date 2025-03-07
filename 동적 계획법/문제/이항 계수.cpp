#include<iostream>
using namespace std;

//이항계수: n 개의 수 중 r 개의 수를 순서 없이 골라내는 방법의 수
//점화식: (n r) = (n-1 r-1) + (n-1 r)

int cache[30][30]; //(n, r) <= 30
//cache 를 -1로 초기화 함.

int bino(int n, int r){
    //기저 사례: 모든 원소를 고른경우 또는 고를 원소가 없는 경우
    if(n == r || r == 0) return 1;
    
    int& ret = cache[n][r];
    //cache의 값이 -1이 아닌 경우
    if(ret != -1){
        return ret; //중복 부분 문제의 결과 재사용
    }
    ret = bino(n-1, r-1) + bino(n-1, r);
    return ret;
}