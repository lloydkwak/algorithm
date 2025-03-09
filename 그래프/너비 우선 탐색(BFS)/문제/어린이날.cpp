#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<algorithm>

using namespace std;

//t : 테스트 케이스 수(<=50), n : 어린이 인원(<=10000), m : 욕심쟁이, d : 사용가능한 숫자 목록;
int t, n, m;
string d;

int append(int here, int edge, int mod){
    int there = here * 10 + edge;
    if(there >= mod) return mod + there % mod;
    return there % mod;
}

//c mod n == m 인 최소 c를 찾는 함수
string gifts(){
    sort(d.begin(), d.end());
    //parent : 스패닝 트리에서 정점의 부모, choice : 간선의 번호
    vector<int> parent(2*n, -1), choice(2*n, -1);
    queue<int> q;
    parent[0] = 0;
    q.push(0);
    while(!q.empty()){
        int here = q.front();
        q.pop();
        for(int i = 0; i < d.size(); ++i){
            int there = append(here, d[i] - '0', n);
            if(parent[there] == -1){
                parent[there] = here;
                choice[there] = d[i] - '0';
                q.push(there);
            }
        }
    }
    //c가 n+m 보다 크고 c mod n == m 인 정점에 도달하지 못한 경우
    if(parent[n + m] == -1) return "IMPOSSIBLE";
    string ret;
    //목표에서 부모를 따라 시작점으로 돌아가며 c를 역으로 계산
    int here = n + m;
    while(parent[here] != here){
        ret += char('0' + choice[here]);
        here = parent[here];
    }
    //역으로 계산한 c를 뒤집는다
    reverse(ret.begin(), ret.end());
    return ret;
}

int main(){
    cin >> t;
    while(t--){
        cin >> d >> n >> m;
        cout << gifts() << endl;
    }
}

/*
5
1 7 0
1 10 1 
0 7 3
345 9997 3333
35 9 8
*/