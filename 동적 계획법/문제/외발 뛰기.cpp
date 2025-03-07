#include<iostream>
#include<vector>
#include<string.h>
using namespace std;

//c : 테스트 케이스의 수(<=50), n : 격자의 크기(2<=n<=100)
int c, n, num[100][100];

//cache: 현재 위치에서 끝에 도달 할 수있지 여부 저장장(음수가 불가능 하므로 -1로 초기화)
int cache[101][101];

//현재 위치를 계산하여 끝에 도달 할 수있는지 판단하는 함수
int move(int y, int x){
    //기저 사례1: 범위를 벗어난 경우
    if(y >= n || x >= n){
        return 0;
    }
    //기저 사례2: 끝에 도달한 경우
    if(y == n-1 && x == n-1){
        return 1;
    }

    int next = num[y][x];

    //memorization: 이미 계산한 칸인 경우 바로 반환
    int& ret = cache[y][x];    
    if(ret != -1){
        return ret;
    }

    //다음 칸으로 이동
    return ret = (move(y + next, x) || move(y, x + next));
}

int main(){
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n;
        memset(cache, -1, sizeof(cache));
        for(int j = 0; j < n; ++j){
            for(int k = 0; k < n; ++k){
                cin >> num[j][k];
            }
        }
        if(move(0, 0) != 0) {
            cout << "YES" << endl;
        } else cout << "NO" << endl;
    }
}