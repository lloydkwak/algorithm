#include<iostream>
#include<queue>
#include<string.h>
#include<algorithm>

using namespace std;

//c : 테스트 케이스 수(<=50), n : 원반의 총 수(<=12)
int c, n;
const int MAX_N = 12;

//비트마스크
//idx의 위치 반환
int get(int state, int idx){
    return (state >> (idx * 2)) & 3;
}
//idx, value 기둥에 넣기
int set(int state, int idx, int value){
    return (state & ~(3 << (idx * 2))) | (value << (idx * 2));
}
int path[1 << (MAX_N * 2)];

//양방향 탐색
int sgn(int x) {
    if(!x) return 0;
    return x > 0 ? 1 : -1;
}
int incr(int x){
    if(x < 0) return x - 1;
    return x + 1;
}

int bfs(int discs, int begin, int end){
    if(begin == end) return 0;
    queue<int> q;
    memset(path, 0, sizeof(path));
    q.push(begin);
    path[begin] = 1;
    q.push(end);
    path[end] = -1;
    while(!q.empty()){
        int here = q.front();
        q.pop();
        //하노이 탑 기둥 가장 위에 있는 디스크
        int top[4] {-1, -1, -1,-1};
        for(int i = discs - 1; i >= 0; --i){
            top[get(here, i)] = i;
        }
        for(int i = 0; i < 4; ++i){
            if(top[i] != -1){
                for(int j = 0;  j < 4; ++j){
                    if(i != j && (top[j] == -1 || top[j] > top[i])){
                        int there = set(here, top[i], j);
                        if(path[there] == 0){
                            path[there] = incr(path[here]);
                            q.push(there);
                        }
                        else if(sgn(path[there]) != sgn(path[here]))
                            return abs(path[there]) + abs(path[here]) - 1;
                    }
                }
            }
        }
    }
    return -1;
}

int main(){
    cin >> c;
    while(c--){
        cin >> n;
        int num, disc, begin = 0, end = 0;
        for(int i = 0; i < 4; ++i){
            cin >> num;
            for(int j = 0; j < num; ++j){
                cin >> disc;
                begin = set(begin, disc - 1, i);
            }
        }
        for(int i = 0; i < n; ++i){
            end = set(end, i, 3);
        }
        cout << bfs(n, begin, end) << endl;
    }
}


/*
3
5
1 1
1 3
2 5 4
1 2
3
1 2
0
2 3 1
0
10
2 8 7
2 5 4
3 6 3 2
3 10 9 1
*/