#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>

#define INF 987654321
using namespace std;

//c : 테스트 케이스 수(<=50), g : 은하 수(<=100), w : 웜홀 수(<=1000)
int c, g, w;

//그래프의 인접 리스트 표현: (정점, 가중치)
vector<pair<int, int>> adjMin[101];
vector<pair<int, int>> adjMax[101];
//path[i][j] : i에서 j로 가는 경로가 존재 하는지 여부 저장장
bool path[101][101];
// floyd 도달 가능성 알고리즘을 이용해서  path 계산
void calcPath() {
	for(int i = 0; i < g; ++i)
        path[i][i] = true;
	for(int k = 0; k < g; ++k)
		for(int i = 0; i < g; ++i)
			for(int j = 0; j < g; ++j)
				path[i][j] = path[i][j] || (path[i][k] && path[k][j]);
}

void makeGraph(){
    //그래프 초기화
    for(int i = 0; i < g; ++i){
        adjMin[i].clear();
        adjMax[i].clear();
    }
    int a, b, d;
    for(int i = 0; i < w; ++i){
        cin >> a >> b >> d;
        adjMin[a].push_back(make_pair(b, d));
        adjMax[a].push_back(make_pair(b, -d));
        path[a][b] = true;
    }
}

int bellmanFord(int src, int target, vector<pair<int, int>>* adj){
    vector<int> upper(g, INF);
    upper[src] = 0;
    //g-1번 순회회
    for(int iter = 0; iter < g - 1; ++iter){
        for(int here = 0; here < g; ++here){
            for(int i = 0; i < adj[here].size(); ++i){
                int there = adj[here][i].first;
                int cost = adj[here][i].second;
                upper[there] = min(upper[there], upper[here] + cost);
            }
        }
    }
    //음수 사이클 확인
    for(int here = 0; here < g; ++here){
        for(int i = 0; i < adj[here].size(); ++i){
            int there = adj[here][i].first;
            int cost = adj[here][i].second;
            //v번째 완화 여부 확인
            if(upper[there] > upper[here] + cost){
                //사이클 포함 경로 존재 여부 확인
                if(path[src][here] && path[here][target]) return -INF;
            }
        }
    }
    return upper[target];
}

int main(){
    cin >> c;
    while(c--){
        memset(path, false, sizeof(path));
        cin >> g >> w;
        makeGraph();
        calcPath();
        int m, M;
        m = bellmanFord(0, 1, adjMin);
        M = bellmanFord(0, 1, adjMax);

        if(!path[0][1]){
            cout << "UNREACHABLE" << endl;
            continue;
        }
        if(m == -INF) cout << "INFINITY" << ' ';
        else cout << m << ' ';
        if(M == -INF) cout << "INFINITY" << endl;
        else cout << -M << endl;
    }
}

/*
4
2 2
0 1 1
0 1 3
4 4
0 2 -7
0 3 -4
3 2 9
2 1 3
4 3
0 2 0
2 2 1
2 1 0
3 0
*/

/*
1 3
-4 8
0 INFINITY
UNREACHABLE
*/