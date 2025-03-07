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
        /*
        대치응로 타일을 채운 경우 절반까지 타일을 채우면 나머지 
        절반은 한가지 경우로 고정되기때문에 절반까지 채우는 수를 빼면 된다.
        */
        int ans = n % 2 ? (fill(n) - fill(n/2)) % mod : (fill(n) - fill(n/2+1) + mod) % mod;
        cout << ans << endl;
    }
}