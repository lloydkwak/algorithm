#include<iostream>
#include<queue>
#include<algorithm>

#define INF 987654321
using namespace std;

//c : 테스트 케이스 수(<=50), v : 장소(<= 1000), e : 도로
//n : 화재 장소 수, m : 소방서 수
int c, v, e, n, m;

//그래프의 인접 리스트
vector<pair<int, int>> adj[1001];
//rode[i] : i 지점까지 가는 최소 시간
vector<int> rode;

void makeGraph(){
    //그래프 초기화
    for(int i = 0; i <= v; ++i){
        adj[i].clear();
    }
    int a, b, t;
    for(int i = 0; i < e; ++i){
        cin >> a >> b >> t;
        adj[a].push_back(make_pair(t, b));
        adj[b].push_back(make_pair(t, a));
    }
}

void dijkstra(int src){
    rode = vector<int>(v + 1, INF);
    rode[src] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push(make_pair(0, src));
    while(!pq.empty()){
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        if(rode[here] < cost) continue;
        for(int i = 0; i < adj[here].size(); ++i){
            int there = adj[here][i].second;
            int nextTime = cost + adj[here][i].first;
            if(rode[there] > nextTime){
                rode[there] = nextTime;
                pq.push(make_pair(-nextTime, there));
            }
        }
    }
    return;
}

int solve(const vector<int>& fire){
    dijkstra(0);
    int sum = 0;
    for(int i = 0; i < n; ++i){
        sum += rode[fire[i]];
    }
    return sum;
}

int main(){
    cin >> c;
    while(c--){
        cin >> v >> e >> n >> m;
        makeGraph();
        int station;
        vector<int> fire(n);
        for(int i = 0; i < n; ++i) cin >> fire[i];
        //모든 소방서에 연결된 가중치가 0인 임의의 시작점 생성
        //한번의 다익스트라로 모든 소방서에서 동시에 출발 가능
        for(int i = 0; i < m; ++i) {
            cin >> station;
            adj[0].push_back(make_pair(0, station));
        }
        cout << solve(fire) << endl;
    }
}

/*
1
8 12 3 2
1 2 3
1 6 9
2 3 6
3 4 4 
3 5 2
4 5 7
6 5 5 
8 6 5
6 7 3
8 7 3
7 5 1
2 8 3
2 3 5
4 6
*/