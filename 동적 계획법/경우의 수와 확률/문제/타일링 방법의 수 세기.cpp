#include<iostream>
#include<string.h>
using namespace std;

//c : 테스트 케이스 수(<= 50), n : 사각형 길이
int c, n;
const int mod = 1000000007;

int cache[101];
//타일을 채우는 방법의 수
int fill(int width){
    //기저 사례1: 남은 길이가 1 이하 일때
    if(width <= 1) return 1;

    //memorization
    int& ret = cache[width];
    if(ret != -1) return ret;
    
    return ret = (fill(width - 1) + fill(width - 2)) % mod;
}

int main(){
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n;
        memset(cache, -1, sizeof(cache));
        cout << fill(n) << endl;
    }
}