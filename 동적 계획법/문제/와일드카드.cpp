#include<iostream>
#include<algorithm>
#include<string>
#include<string.h>
using namespace std;

//c : 테스트 케이스의 수(<=50), n : 파일명의 수(<=50), cnt : 대응되는 문자열 수
//ans[]: 대응하는 파일명을 기록한 배열
int c, n, cnt;
string ans[50];

//W: 와일드 카드 문자열, S: 입력 받은 파일명
string W, S;

//cache는 위치에 따른 문자열 대응 여부 저장(-1로 초기화)
int cache[101][101];

//문자열 w, s 대응 여부 확인
bool match(int w, int s) {
    //memorization
    int& ret = cache[w][s];
    if(ret != -1) {
        return ret;
    }

    //대응되는지 여부 확인
    if(w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s])){
        return ret = match(w + 1, s + 1);
    }

    if(w == W.size()){
        return ret = (s == S.size());
    }
    //* 인 경우 *의 대응을 재귀를 통해 구한다
    if(W[w] == '*'){
        if(match(w + 1, s) || (s < S.size() && match(w, s + 1))){
            return ret = 1;
        }
    }
    return ret = 0;
}

int main(){
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> W;
        cin >> n;
        cnt = 0;
        for(int j = 0; j < n; ++j){
            memset(cache, -1, sizeof(cache));
            cin >> S;
            if(match(0, 0)){
                ans[cnt] = S;
                ++cnt;
            }
        }
        sort(ans, ans + cnt);
        for(int j = 0; j < cnt; ++j){
            cout << ans[j] << endl;
        }
    }
    return 0;
}