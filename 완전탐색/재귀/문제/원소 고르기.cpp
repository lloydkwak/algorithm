#include<iostream>
#include<vector>

void printPicked(std::vector<int>& picked){
	std::cout << "( ";
	for(auto& i : picked){ //auto 참조자로 vecter 요소 출력
		std::cout << i << " ";
	}
	std::cout << ")" << std::endl;
}

void pick(int n, std::vector<int>& picked, int toPick) {
	//기저 사례: 더 고를 원소가 없을때 고른 원소 출력
	if(toPick==0) {
		printPicked(picked);
		return;
	}
	//남은 원소 중 가장 작은 원소 계산
	//pick가 비어있으면 0, 아니면 마지막 원소 +1
	int smallest= picked.empty() ? 0 : picked.back() + 1;
	//원소 한개 고르기
	// 가장 작은 원소부터 차례대로 재귀를 통해 고름
	for(int next = smallest; next < n; ++next){
		picked.push_back(next);
		pick(n, picked, toPick-1);
		picked.pop_back();
	}
}

int main() {
    //n: 전체 원소의 수
	//toPick: 고라야 하는 원소의 수
	int n, toPick;
	std::cin >> n >> toPick;
	//picked: 지금까지 고른 원소
	std::vector<int> picked;
	pick(n, picked, toPick);
	return 0;
}