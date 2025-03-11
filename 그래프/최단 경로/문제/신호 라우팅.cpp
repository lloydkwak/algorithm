#include<iostream>
#include<queue>
#include<cmath>
#include<algorithm>

using namespace std;

//c : 테스트 케이스 수(<=50), n : 컴퓨터 수(<=10000), m : 외선의 수(<= 20000)
int c, n, m;

//그래프 인접 행렬 표현
vector<pair<int, double>> adj[10001];

vector<double> noise;

void makeGraph(){
    //그래프 초기화화
    for(int i = 0; i < n; ++i) {
        adj[i].clear();
    }
    int a, b;
    double w;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> w;
        //로그 연산으로 곱하기를 더하기로 변형형
        adj[a].push_back({b, log(w)});
        adj[b].push_back({a, log(w)});
    }
}

//0번에서 n-1번으로 가는 경로중 노이즈가 최소가 되는 경로의 노이즈 반환
void dijkstra(int src){
    noise = vector<double> (n, 1e9);
    noise[src] = 0.0;   //로그를 사용하기 때문에 초기값 0;
    priority_queue<pair<double, int>> pq;
    pq.push(make_pair(-0.0, src));
    while(!pq.empty()){
        double cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        if(noise[here] < cost) continue;
        for(int i = 0;  i < adj[here].size(); ++i){
            int there = adj[here][i].first;
            double nextNoise = cost + adj[here][i].second;
            if(noise[there] > nextNoise){
                noise[there] = nextNoise;
                pq.push(make_pair(-nextNoise, there));
            }
        }
    }
    return;
}


int main(){
    cin >> c;
    while(c--){
        cin >> n >> m;
        makeGraph();
        dijkstra(0);
        cout << fixed;
        cout.precision(10);
        //로그값 해제 후 출력
        cout << exp(noise[n-1]) << endl;
    }
}


/*
1
7 14
0 1 1.3
0 2 1.1
0 3 1.24
3 4 1.17
3 5 1.24
3 1 2
1 2 1.31
1 2 1.26
1 4 1.11
1 5 1.37
5 4 1.24
4 6 1.77
5 6 1.11
2 6 1.2
*/