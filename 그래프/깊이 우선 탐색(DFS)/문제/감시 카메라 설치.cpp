#include<iostream>
#include<vector>

using namespace std;

//c : 테스트 케이스 수(<= 50), g : 갤러리 수(<=1000), h : 복도의 수(<= g)
int c, g, h;

vector<int> adj[1001];
vector<bool> visited;

const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;

int installed;

//here로 부터 깊이 우선 탐색을 하고
int dfs(int here){
    visited[here] = true;
    //자식의 상태 표현.
    int children[3] = {0, 0, 0};
    for(int i = 0; i < adj[here].size(); ++i) {
        int there = adj[here][i];
        if(!visited[there]) {
            ++children[dfs(there)];
        }
    }
    //자식 중 하나라도 감시하고 있지 않은 경우
    if(children[0]){ 
        ++installed;
        return INSTALLED;
    }
    if(children[INSTALLED]){
        return WATCHED;
    }
    return UNWATCHED;
}

//감시에 필요한 최소 카메라 개수 반환
int installCamera(){
    installed = 0;
    visited = vector<bool>(g, false);
    for(int i = 0; i < g; ++i){
        if(!visited[i] && dfs(i) == UNWATCHED){
            ++installed;
        }
    }
    return installed;
}

void makeGraph(){
    for (int i = 0; i < g; i++) {
        adj[i].clear();
    }
    int a, b;
    for(int i = 0;  i < h; ++i){
        cin >> a >> b;
        //무향 그래프 이므로 양방향 간선을 표시
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
}

int main() {
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> g >> h;
        makeGraph();
        cout << installCamera() << endl;
    }
}

/*
3
6 5
0 1
1 2
1 3
2 5
0 4
4 2
0 1
2 3
1000 1
0 1
*/