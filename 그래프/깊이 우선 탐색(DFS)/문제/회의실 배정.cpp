#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>

using namespace std;

//c : 테스트 케이스 수(<= 50), n : 팀 수(<=100)
int c, n;
vector<int> ans;

vector<vector<int>> adj;
vector<int> sccId;
vector<int> discoverd;
stack<int> st;
int sccCounter, vertexCounter;

//두 구간이 겹치는지 확인
bool disjoint(const pair<int, int>& a, const pair<int, int>& b){
    return a.second <= b.first || b.second <= a.first;
}

//2-SAT문제로 변환하여 함의 그래프 생성성
void makeGraph(const vector<pair<int, int>>& meetings){
    int teams = meetings.size();
    adj.clear();
    adj.resize(teams * 2);
    //2n개의 변수, 참 거짓이 존재하므로 한 그래프에 4n개 존재
    //i, j 중 적어도 하나의 회의는 반드시 해야함(짝수 : 참, 홀수 : 거짓)
    for(int i = 0; i < teams; i += 2){
        int j = i + 1;
        adj[i * 2 + 1].push_back(j * 2);    //!i -> j
        adj[j * 2 + 1].push_back(i * 2);    //!j -> i
    }
    for(int i = 0; i < teams; ++i){
        for(int j = 0; j < i; ++j){
            if(!disjoint(meetings[i], meetings[j])){
                //겹칠 경우 하나를 하면 다른 회의는 하면 안된다.
                adj[i * 2].push_back(j * 2 + 1);    //i -> !j
                adj[j * 2].push_back(i * 2 + 1);    //j -> !i
            }
        }
    }
}

int scc(int here){
    int ret = discoverd[here] = vertexCounter++;
    //스택에 here을 넣는다. here의 후손은 모두 스택에 here 보다 늦게 들어간다.
    st.push(here);
    for(int i = 0; i < adj[here].size(); ++i){
        int there = adj[here][i];
        //(here, there)가 트리 간선
        if(discoverd[there] == -1){
            ret = min(ret, scc(there));
        }
        //there 이 무시해야하는 교차 간선이 아니라면
        else if(sccId[there] == -1){
            ret = min(ret, discoverd[there]);
        }
    }
    if(ret == discoverd[here]){
        while(true) {
            int t = st.top();
            st.pop();
            sccId[t] = sccCounter;
            if(t == here) break;
        }
        ++sccCounter;
    }
    return ret;
}
//Tarjan의 scc 알고리즘
vector<int> tarjanSCC(){
    //배열 초기화
    sccId = discoverd = vector<int>(adj.size(), -1);
    //카운터 초기화
    sccCounter = vertexCounter = 0;
    //모든 정점에 대해 scc 호출
    for(int i = 0; i < adj.size(); ++i){
        if(discoverd[i] == -1) scc(i);
    }
    return sccId;
}

//2-SAT 문제에 대한 답 반환
vector<int> solve2SAT() {
    int N = adj.size() / 2;  //변수의 수
    vector<int> label = tarjanSCC();
    //한 변수의 참, 거짓이 하나의 SCC 요소에 속한 경우
    for(int i = 0; i < 2 * N; i += 2){
        if(label[i] == label[i + 1]){
            return vector<int>();
        }
    }
    vector<int> value(2 * N, -1);
    vector<pair<int, int>> order;
    for(int i = 0; i < 2 * N; ++i){
        order.push_back(make_pair(-label[i], i));
    }
    sort(order.begin(), order.end());
    for(int i = 0; i < 2 * N; ++i){
        int vertex = order[i].second;
        int variable = vertex / 2, isTrue = vertex % 2 == 0;
        if(value[variable] != -1) continue;
        value[variable] = !isTrue;
    }
    return value;
}

int main() {
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> n;
        vector<pair<int, int>> meetings;
        for(int j = 0; j < n; ++j){
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            meetings.push_back(make_pair(a, b));
            meetings.push_back(make_pair(c, d));
        }
        makeGraph(meetings);
        ans = solve2SAT();
        if(ans.empty()){
            cout << "IMPOSSIBLE" << endl;
            continue;
        }
        cout << "POSSIBLE" << endl;
        for(int j = 0; j < n; ++j){
            if(ans[j * 2]){
                cout << meetings[j * 2].first << ' ' << meetings[j * 2].second << endl;
            }
            else {
                cout << meetings[j * 2 + 1].first << ' ' << meetings[j * 2 + 1].second << endl;
            }
            
        }
    }
}


/*
1
2
1 20 40 50
5 25 10 35
*/

/*
3
2
1 10 10 20
1 10 10 20
3
1 10 10 20
1 10 10 20
1 10 10 20
3
2 5 6 9
1 3 8 10
4 7 11 12
*/