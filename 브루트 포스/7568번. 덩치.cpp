/*
	브루트 포스 알고리즘 연습용 문제(백준 7568번. 덩치) 
	문제 분석 : 몸무게와 키를 하나의 쌍으로 입력 받고 해당 쌍들 중에서 크기 비교를 하고,
				비교군 중에서 몇등인지를 출력. 
	해 선택 전략 : C++의 STL 중 하나인 VECTOR를 사용해서 키와 몸무게를 하나로 저장하고, 크기 비교 실행. 
*/
#include <iostream>
#include <vector>
using namespace std;

class People{
	public:
		int weight;
		int height;
		int rank=1;//자신보다 덩치가 큰 사람이 한명도 없으면 1이므로 1로 초기화. 
		People(int weight, int height) : weight(weight), height(height){}
		void plus_rank(){
			this->rank+=1;
		}
	
	bool operator<(People temp){
		if(this->weight<temp.weight && this->height<temp.height)
			return 1;
		else
			return 0;
	}
};

int main(){
	vector<People> temp;
	int n=0;
	cin>>n;
	int wei, hei;
	for(int i=0; i<n; i++){
		cin>>wei>>hei;
		temp.push_back(People(wei,hei));
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i==j) continue;
			else if((temp[i]<temp[j])==1)
				temp[i].plus_rank();
		}
	}
	for(int i=0; i<n; i++){
		cout<<temp[i].rank<<" ";
	}
}
