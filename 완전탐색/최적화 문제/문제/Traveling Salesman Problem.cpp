#include<iostream>
#include<vector>
#include <cfloat>
using namespace std;

//n: 도시의 개
int n;
//dist: 각 도시 사이의 거리를 저장한 vector
double dist[20][20];

//모든 도시를 방문할때 이동거리의 최소 값을 구하는 재귀함수
double shortestPath(vector<int>& path, vector<bool>& visited, double sumLength){
	//here: 현재위치
	int here = path.back();
	//기저 사례: 모든 도시를 방문(다시 처음 도시로 돌아가는 거리를 더하면 됨)
	if(path.size() == n) return sumLength + dist[0][here];
	double ret = DBL_MAX;
	//현재 위치에서 다음 도시 방문
	for(int i=0; i<n; ++i){
		if(visited[i]) continue;
		visited[i] = true;
		path.push_back(i);
		ret = min(ret, shortestPath(path, visited, sumLength + dist[here][i]));
		visited[i] = false;
		path.pop_back();
	}
	return ret;
}

int main() {
	cin >> n;
	
	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			cin >> dist[i][j];
		}
	}
	//path: 지나온 경로를 순서대로 저장, visited: 도시 방문 여부를 저장
	vector<int> path;
	//출발 도시를 0번으로 고정(거리가 양방향이기에 가능한 전제)
	path.push_back(0);
	vector<bool> visited(n, false);
	visited[0] = true;
	cout << shortestPath(path, visited, 0) << endl;
	return 0;
}