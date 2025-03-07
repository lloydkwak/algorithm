#include<iostream>
#include<string.h>
using namespace std;

//c : 테스트 케이스 수(<= 50), n : 삼각형의 크기(<= 100)
//num: 삼각형에 숫자를 기록
int c, n;
int num[101][101];

int cache[101][101];

/* 재귀를 활용한 dp: cache를 -1로 초기화 해서 사용해야함
int path(int y, int x){
    //기저 사례: 바닥에 도달한 경우
    if(y == n-1){
        return num[y][x];
    }
    //memorization
    int& ret = cache[y][x];
    if(ret != -1){
        return ret;
    }
    return ret = num[y][x] + max(path(y + 1, x), path(y + 1, x + 1));
}
*/

//반복적 동적 계획법
void path(){
    for(int i = n-1; i >= 0; --i){
        for(int j = 0; j < n; ++j){
            cache[i][j] = num[i][j] + max(cache[i + 1][j], cache[i + 1][j + 1]);
        }
    }
}

int main(){
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n;
        memset(num, 0, sizeof(num));
        memset(cache, 0, sizeof(cache));
        for(int j = 0; j < n; ++j){
            for(int k =0; k <= j; ++k){
                cin >> num[j][k];
            }
        }
        path();
        cout << cache[0][0] << endl;
        //cout << path(0, 0) << endl;
    }
}