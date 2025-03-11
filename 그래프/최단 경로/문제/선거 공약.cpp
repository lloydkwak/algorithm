#include<iostream>
using namespace std;

const int INF = 987654321;

//c : 테스트 케이스 수(<= 50), v : 도시의 수(<= 200), 
//m : 존재 하는 고속도로 수, n : 건설할 도로의 수(n+m <= 1000)
int c, v, m, n;

//그래프의 인접 행렬 표현
int adj[200][200];

void floyd(){
    for(int k = 0; k < v; ++k){
        for(int i = 0; i < v; ++i){
            for(int j = 0; j < v; ++j){
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
}

//추가 된 간선 c에 대해 adj 업데이트(추가된 간선 하나만 경우 여부를 확인하면 됨)
void update(int a, int b, int c){
    for(int i = 0; i < v; ++i){
        for(int j = 0; j < v; ++j){
            adj[i][j] = 
                min(adj[i][j], min(adj[i][a] + c + adj[b][j], adj[i][b] + c + adj[a][j]));
        }
    }
}

int main(){
    cin >> c;
    while(c--){
        cin >> v >> m >> n;
        for (int i = 0; i < 200; ++i){
            for(int j = 0; j < 200; ++j){
                if(i == j){
                    adj[i][j] = 0;
                    continue;
                }
                adj[i][j] = INF;
            }
        }
        int a, b, c;
        for(int i = 0; i < m; ++i){
            cin >> a >> b >> c;
            adj[a][b] = min(adj[a][b], c);
            adj[b][a] = min(adj[b][a], c);
        }   
        floyd();
        int ans = 0;
        for(int i = 0; i < n; ++i){
            cin >> a >> b >> c;
            if(adj[a][b] <= c) ++ans;
            else{
                update(a, b, c);
            }

        }
        cout << ans << endl;
    }
}


/*
2
4 2 2
0 1 4
0 3 1
0 2 2
1 2 6
4 2 2
0 1 4
0 3 1
1 2 6
0 2 2
*/

/*
1
0
*/