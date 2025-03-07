#include<iostream>
#include<string.h>
using namespace std;

//c : 테스트 케이스 수(<= 50), n : 삼각형의 크기(<= 100)
//num: 삼각형에 숫자를 기록
int c, n;
int num[101][101];

int cache[101][101], countCache[101][101];

int path(int y, int x){
    //기저 사례: 바닥에 도달한 경우
    if(y == n-1) return num[y][x];
    //memorization
    int& ret = cache[y][x];
    if(ret != -1) return ret;

    return ret = num[y][x] + max(path(y + 1, x), path(y + 1, x + 1));
}

int count(int y, int x){
    //기저 사례: 바닥에 도달한 경우
    if(y == n-1) return 1;
    //memorization
    int& ret = countCache[y][x];
    if(ret != -1) return ret;

    ret = 0;
    if(path(y + 1, x) <= path(y + 1, x + 1)) ret += count(y + 1, x + 1);
    if(path(y + 1, x) >= path(y + 1, x + 1)) ret += count(y + 1, x);
    return ret;
}

int main(){
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n;
        memset(cache, -1, sizeof(cache));
        memset(countCache, -1, sizeof(countCache));
        for(int j = 0; j < n; ++j){
            for(int k =0; k <= j; ++k){
                cin >> num[j][k];
            }
        }
        cout << count(0, 0) << endl;
    }
}