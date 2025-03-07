#include<iostream>
#include<string.h>
#include<cmath>
using namespace std;

//c : 테스트 케이스 수(<= 50), n : 정사각형이 수(<= 100)
int c;

int mod = 10000000;

int cache[102][102];
//폴리오노미오 중 세로 단조인 경우의 수 반환
int mPoly(int n, int before){
    //기저 사례: 
    if(n == before) return 1;
    
    //memorization
    int& ret = cache[n][before];
    if(ret != -1) return ret;

    ret = 0;
    return ret;
}

int main(){
    cin >> c;
    for(int i = 0; i < c; ++i){
        int n;
        cin >> n;
        memset(cache, -1, sizeof(cache));
        cout << mPoly(n, 0) << endl;
    }
}