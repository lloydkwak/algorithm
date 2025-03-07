#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

//c : 테스트 케이스 수(<= 50), n : 포함된 단어 수(<=200)
int c, n;
vector<string> words;
//그래프 인접 행렬 표현
vector<vector<int>> adj;

//i로 시작해서 j로 끝나는 단어 목록 만들기
vector<string> graph[26][26];
//i로 시작하는 단어 수, i로 끝나는 단어 수
vector<int> indegree, outdegree;

//그래프 만들기
void makeGraph(){
    //변수 초기화
    for(int i = 0; i < 26; ++i){
        for(int j = 0; j < 26; ++j){
            graph[i][j].clear();
        }
    }
    adj = vector<vector<int>>(26, vector<int>(26, 0));
    indegree = outdegree = vector<int>(26, 0);
    //간선 추가
    for(int i = 0; i < n; ++i){
        int a = words[i].front() - 'a';
        int b = words[i].back() - 'a';
        graph[a][b].push_back(words[i]);
        adj[a][b]++;
        outdegree[a]++;
        indegree[b]++;
    }
}

//오일러 트레일, 서킷 만들기
void getEulerCircuit(int here, vector<int>& circuit){
    for(int there = 0; there < adj.size(); ++there){
        while(adj[here][there] > 0){
            adj[here][there]--;
            getEulerCircuit(there, circuit);
        }
    }
    circuit.push_back(here);
}

//현대 그래프의 오일러 트레일/서킷 반환
vector<int> getEulerTrailOrCircuit() {
    vector<int> circuit;
    //트레일 찾기 : 시작점의 indgree가 outdgree 보다 1 커야한다
    for(int i = 0; i < 26; ++i){
        if(outdegree[i] == indegree[i] + 1){
            getEulerCircuit(i, circuit);
            return circuit;
        }
    }
    //서킷인 경우
    for(int i = 0; i < 26; ++i){
        if(outdegree[i]) {
            getEulerCircuit(i, circuit);
            return circuit;
        }
    }
    return circuit;
}

//현재 그래프 오일러 트레일/서킷 존재여부 확인
bool checkEuler(){
    int start = 0, end = 0;
    for(int i = 0; i < 26; ++i){
        int delta = outdegree[i] - indegree[i];
        if(delta < -1 || delta > 1) return  false;
        if(delta == 1) start++;
        if(delta == -1) end++;
    }
    //시작과 끝이 각각 하나이거나 없어야 한다.
    return (start == 1 && end == 1) || (start == 0 && end == 0);
}

string solve(){
    makeGraph();
    //오일러 트레일/서킷이 없는 경우
    if(!checkEuler()) return "IMPOSSIBLE";
    //오일러 트레일/서킷 계산
    vector<int> circuit = getEulerTrailOrCircuit();
    //모든 간선을 방문 했는지 확인
    if(circuit.size() != words.size() + 1) return "IMPOSSIBLE";
    reverse(circuit.begin(), circuit.end());
    string ret;
    for(int i = 1; i < circuit.size(); ++i){
        int a = circuit[i - 1], b = circuit[i];
        if(ret.size()) ret += " ";
        ret += graph[a][b].back();
        graph[a][b].pop_back();
    }
    return ret;
}

int main() {
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n;
        words = vector<string>(n);
        for(int j = 0; j < n; ++j){
            cin >> words[j];
        }
        cout << solve() << endl;
    }
}