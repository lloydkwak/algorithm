#include<iostream>
#include<string.h>
#include<string>
using namespace std;

#define INF 987654321

//c: 테스트 케이스 수(<= 50), num : 외워야 하는 수(10,000자리 이하)
int c;
string num;

//현재부터 마직까지 수를 왜우는 최소 난이도
int cache[10002];

//num[left..right] 구간의 난이도 반환
int classify(int left, int right){
    //substr(시작 idx, 크기)
    string tmp = num.substr(left, right - left + 1);

    //모든 자리가 같을 경우
    if(tmp == string(tmp.size(), tmp[0])) return 1;

    //등차수열 여부 검사
    bool flag = true;
    for(int i = 1; i < tmp.size() - 1; ++i){
        if(tmp[i + 1] - tmp[i] != tmp[1] - tmp[0]){
            flag = false;
            break;
        }
    }

    //단조 증감인 경우
    if(flag && abs(tmp[1] - tmp[0]) == 1) return 2;

    //단소 증감이 아닌 등차 수열인 경우
    if(flag) return 5;

    //수가 번갈아 나오는 경우
    flag = true;
    for(int i = 2; i < tmp.size(); ++i){
        if(tmp[i] != tmp[i-2]){
            flag = false;
            break;
        }
    }
    if(flag) return 4;

    //다른 모든 경우
    return 10;
}

//난이도 최소 합 출력
int difficulty(int idx){
    //기저 사례1: 다 외운 경우
    if(idx == num.size()) return 0;

    //memorization
    int& ret = cache[idx];
    if(ret != -1) return ret;

    ret = INF;
    for(int i = 3; i <=5; ++i){
        if(idx + i <= num.size()){
            ret = min(ret, classify(idx, idx + i - 1) + difficulty(idx + i));
        }
    }
    return ret;
}

int main() {
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> num;
        memset(cache, -1, sizeof(cache));
        cout << difficulty(0) << endl;
    }
    return 0;
}