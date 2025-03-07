#include<iostream>
#include<string.h>
using namespace std;

//c: 테스트 케이스 수(<= 50), n: 수열의 크기(<= 500)
//seq: 수열
int c, n;
int seq[501];

//idx를 시작으로 가질 수 있는 최대 증가 부분 수열 저장
int cache[501];


int lis(int idx){
    //memorization
    int& ret = cache[idx + 1];
    if(ret != -1){
        return ret;
    }

    //최초 계산
    ret = 1;
    for(int i = idx + 1; i < n; ++i){
        if(idx == -1 || seq[idx] < seq[i]){
            ret = max(ret, lis(i) + 1);
        }
    }
    return ret;
}

int main() {
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n;
        memset(seq, 0, sizeof(seq));
        memset(cache, -1, sizeof(cache));
        for(int j = 0; j < n; ++j){
            cin >> seq[j];
        }
        //-1인 경우를 추가 했기 때문에 결과에서 빼줘야함
        cout << lis(-1) - 1 << endl;
    }
}