#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>

using namespace std;

//c : 테스트 케이스 수(<=1000), n : 수열의 길이(<=8);
int c, n;

/*
가장 기본적인 bfs를 이용한 풀이: 시간안에 문제 해경 불가
--->해결 방안
1. 수열의 상대적 크기가 같으면 정답이 같다
따라서 1-8까지 정렬된 수열에 대해 모든 다른 수열의 뒤집기 연산을 미리 연사
2. 주어진 수열을 상대적 크기에 맞춰 1-8까지 숫자로 변환

int bfs(const vector<int>& perm){
    vector<int> sorted = perm;
    sort(sorted.begin(), sorted.end());
    queue<vector<int>> q;
    map<vector<int>, int> distance;
    distance[perm] = 0;
    q.push(perm);
    while(!q.empty()){
        vector<int> here = q.front();
        q.pop();
        //도착하면 즉시 끝냄
        if(here == sorted) return distance[here];
        int cost = distance[here];
        //가능한 모든 뒤집기를 해보고 인접 수열 찾기
        for(int i = 0; i < n; ++i){
            for(int j = i + 2; j <= n; ++j){
                //i-j 구간 뒤집기
                reverse(here.begin() + i, here.begin() + j);
                //처음 발견된 수열인 경우 거리 추가, 큐에 추가
                if(distance.count(here) == 0){
                    distance[here] = cost + 1;
                    q.push(here);
                }
                //되돌리기
                reverse(here.begin() + i, here.begin() + j);
            }
        }
    }
}

*/

map<vector<int>, int> toSort;
void precalc(int n){
    vector<int> perm(n);
    for(int i = 0; i < n; ++i){
        perm[i] = i;
    }
    queue<vector<int>> q;
    q.push(perm);
    toSort[perm] = 0;
    while(!q.empty()){
        vector<int> here = q.front();
        q.pop();
        int cost = toSort[here];
        for(int i = 0; i < n; ++i){
            for(int j = i + 2; j <= n; ++j){
                reverse(here.begin() + i, here.begin() + j);
                if(toSort.count(here) == 0){
                    toSort[here] = cost + 1;
                    q.push(here);
                }
                reverse(here.begin() + i, here.begin() + j);
            }
        }
    }
}

int solve(const vector<int>& perm){
    vector<int> fixed(n);
    for(int i = 0; i < n; ++i){
        int smaller = 0;
        for(int j = 0; j < n; ++j){
            if(perm[j] < perm[i]){
                ++smaller;
            }
            fixed[i] = smaller;
        }
    }
    return toSort[fixed];
}

int main(){
    cin >> c;
    while(c--){
        cin >> n;
        precalc(n);
        vector<int> perm(n);
        for(int i = 0; i < n; ++i){
            cin >> perm[i];
        }
        cout << solve(perm) << endl;
    }
}

/*
3
8
1 2 3 4 8 7 6 5
4
3 4 1 2
3
1 2 3
*/