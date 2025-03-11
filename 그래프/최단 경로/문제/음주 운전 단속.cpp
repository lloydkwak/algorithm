#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>

using namespace std;

const int INF = 987654321;

//v : 장소의 개수(<= 500), e : 도로의 수, T : 테스트 케이스 수(<= 1000)
int v, e, T;
int delay[501];

//그래프의 인접 행렬 표현
int adj[501][501];
int path[501][501];

void makeGraph(){
    int a, b, c;
    //INF 같은 큰수로 초기화할 때는 memset을 사용하면 안됨(0, -1에 사용)
    fill(&adj[0][0], &adj[500][501], INF);
    fill(&path[0][0], &path[500][501], INF);
    for(int i = 0; i < e; ++i){
        cin >> a >> b >> c;
        adj[a - 1][b - 1] = c;
        path[a - 1][b - 1] = c;
        //양방향 그래프
        adj[b - 1][a - 1] = c;
        path[b - 1][a - 1] = c;
    }
}

void floyd(){
    vector<pair<int, int>> order;
    //지연 시간이 작은 순으로 정렬
    for(int i = 0; i < v; ++i){
        order.push_back(make_pair(delay[i], i));
        path[i][i] = 0;
        adj[i][i] = 0;
    }
    sort(order.begin(), order.end());
    //정점을 거치지 않고 얻을 수 있는 최단경로
    for(int k = 0; k < v; ++k){
        //지연 시간이 가장 짧은 정점부터 경유
        int w = order[k].second;
        for(int i = 0; i < v; ++i){
            for(int j = 0; j < v; ++j){
                adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
                path[i][j] = min(path[i][j], adj[i][w] + delay[w] + adj[w][j]);
            }
        }
    }
}

int main(){
    cin >> v >> e;
    for(int i  = 0; i < v; ++i){
        cin >> delay[i];
    }
    makeGraph();
    floyd();
    cin >> T;
    while(T--){
        int s, t;
        cin >> s >> t;
        cout << path[s - 1][t - 1] << endl;
    }
}


/*
8 12
8 6 5 8 3 5 8 4
1 6 9
1 2 3
2 8 3
6 8 5
6 7 3
8 7 3
6 5 5
4 5 7
3 4 4
3 5 2
2 3 6
7 5 1
2
1 5
6 3
*/

/*
17
10
*/