#include<iostream>

//n: 학생의 수(최대 10), m: 친구쌍의 수(최대 45)
int n, m;

int count(bool used[10], bool pair[10][10]){
	//남은 학생중 번호가 가장 빠른 학생의 번호 찾기
	int fastist = -1;
	for(int i=0; i<n; i++){
		if(!used[i]){
			fastist = i;
			break;
		}
	}
	//기저 사례: 남은 학생이 없을 경우
	if(fastist == -1) return 1;
	//ret: 가능한 경우를 모두 더한 결과
	int ret = 0;
	//짝지을 학생 정하기
	for(int i=fastist+1; i<n; i++){
		//아직 사용하지 않은 학생과 쌍인 경우
		if(!used[i] && pair[fastist][i]){
			//현재 번호와 사용한 학생의 번호를 true 로 변경
			used[fastist] = used[i] = true;
			//다음 번호로 넘어가는 재귀함수
			ret += count(used, pair); //이때 현재 위치를 함께 넘기면 dp로도 문제해결 가능
			//다른 짝을 찾을 경우
			used[fastist] = used[i] = false;
		}
	}
	return ret;
}

int main() {
	//c: 테스트 케이스의 수
	int c;
	std:: cin >> c;
	//테스트 케이스 만큼 계산
	for(int i=0; i<c; i++){
		std::cin >> n >> m;
		//pair: 친구 여부를 저장한 배열
		bool pair[10][10] = {};		
		//used: 친구 쌍 사용 여부를 저장한 배열
		bool used[10] = {};
		//친구쌍 입력 받기
		for(int j=0; j<m; j++){
			//a, b: 학생 번호
			int a, b;
			std::cin >> a >> b;
			pair[a][b] = true;
		}
		std::cout << count(used, pair) << std::endl;
	}
	return 0;
}