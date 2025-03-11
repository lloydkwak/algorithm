#include<iostream>
#include<queue>
#include<algorithm>

#define INF 987654321
using namespace std;

//c : 테스트 케이스 수(<=50), m : 종목 수(<=500)
//a : a국 완주 시간, b : b국 완주시간간
int c, m;
vector<int> a, b;

//그래프의 인접 리스트 표현: (가중치, 정점점)
vector<pair<int, int>> adj[405];
vector<int> shortest;
const int START = 401;

void dijkstra(int start){
    shortest = vector<int>(402, INF);
    shortest[start] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push(make_pair(0, start));
    while(!pq.empty()){
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        if(shortest[here] < cost) continue;
        for(int i = 0; i < adj[here].size(); ++i){
            int nextCost = cost + adj[here][i].first;
            int there = adj[here][i].second;
            if(shortest[there] > nextCost){
                shortest[there] = nextCost;
                pq.push(make_pair(-nextCost, there));
            }
        }
    }
}

//a - b의 정점 반환
int vertex(int sub){
    return sub + 200;
}

void makeGraph(){
    for(int i = 0; i < 402; ++i){
        adj[i].clear();
    }
    for(int i = 0; i < a.size(); ++i){
        int sub  = a[i] - b[i];
        adj[START].push_back(make_pair(a[i], vertex(sub)));
    }
    for(int sub = -200; sub <= 200; ++sub){
        for(int i = 0; i < a.size(); ++i){
            int next = sub + a[i] - b[i];
            //시간 차이가 200 이상 나는 종목은 무시한다.
            if(abs(next) > 200) continue;
            adj[vertex(sub)].push_back(make_pair(a[i], vertex(next)));
        }
    }   
}

int main(){
    cin >> c;
    while(c--){
        cin >> m;
        a = vector<int>(m);
        b = vector<int>(m);
        for(int i = 0; i < m; ++i){
            cin >> a[i] >> b[i];
        }
        makeGraph();
        dijkstra(START);
        if(shortest[vertex(0)] == INF) cout << "IMPOSSIBLE" << endl;
        else cout << shortest[vertex(0)] << endl;
    }
}

/*
3
5
1 2
3 4
5 6
7 8
7 3
3
1 100
21 20
10 1 
3
10 81
63 71
16 51
*/

/*
11
111
IMPOSSIBLE
*/