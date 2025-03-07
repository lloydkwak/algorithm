#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

//c : 테스트 케이스 수(<= 50), n : 포함된 단어 수(<=200)
int c, n;

//알파벳을 정점으로 가지는 그래프 표현
vector<vector<bool>> alphabet;
//간선 연결하기
void makeGraph(const vector<string>& words){
    alphabet = vector<vector<bool>>(26, vector<bool>(26, false));
    for(int j = 1; j < words.size(); ++j){
        int i = j - 1, len = min(words[i].size(), words[j].size());
        for(int k = 0; k < len; ++k){
            if(words[i][k] != words[j][k]){
                int a = words[i][k] - 'a';
                int b = words[j][k] - 'a';
                alphabet[a][b] = true;
                break;
            }
        }
    }
}

//방문 여부
vector<bool> visited;
vector<int> ordered;
//깊이 우선 탐색
void dfs(int here){
    visited[here] = true;
    for(int there = 0; there < 26; ++there){
        if(alphabet[here][there] && !visited[there]) dfs(there);
    }
    ordered.push_back(here);
}
//깊이 우선 탐색을 통한 위상 정렬 구현
vector<int> topologicalSort(){
    visited = vector<bool>(26, false);
    ordered.clear();
    for(int i = 0; i < 26; ++i){
        if(!visited[i]) dfs(i);
    }
    //결과 뒤집기
    reverse(ordered.begin(), ordered.end());
    //그래프에 사이클이 존재한다면 역방향 간선이 존재한다.
    for(int i = 0; i < 26; ++i){
        for(int j = i + 1; j < 26; ++j){
            //거꾸로 가는 간선 존재
            if(alphabet[ordered[j]][ordered[i]]) return vector<int>();
        }
    }
    return ordered;
}

int main() {
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n;
        vector<string> words(n);
        vector<int> ans;
        for(int j = 0; j < n; ++j){
            cin >> words[j];
        }
        makeGraph(words);
        ans = topologicalSort();
        if(ans.empty()) cout << "INVALID HYPOTHESIS";
        else {
            for(int j = 0; j < ans.size(); ++j){
                cout << char(ans[j] + 'a');
            }
        }
        cout << endl;
    }
}