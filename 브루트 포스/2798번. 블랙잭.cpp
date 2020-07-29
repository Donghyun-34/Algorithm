/*
	브루트 포스 알고리즘 연습용 문제.(백준 2798번. 블랙잭)
	문제 분석 : 주어진 N개의 양의 정수중에서 3개를 합해서, 
	주어진 M에 최대한 가까운 값을 찾는 문제.
	해 선택 전략 : 주어지는 N의 범위가 3~100이므로 가장 단순한 비교 정렬 기법(Counting Sort)을 사용,
				오름차순으로 정렬 후,  가장 큰 수 부터 순차적으로 합 비교 시작. 
*/
#include <iostream>
#include <algorithm>
using namespace std;
int N, M;

int cal(int *num){
	int sum=0, max_of_card=0, mid_of_card=0, min_of_card;
	int max_of_sum=0;
	
	for(int i=N; i>=3; i--){
		max_of_card=num[i-1];
		for(int j=i-1; j>=2; j--){
			mid_of_card=num[j-1];
			if(max_of_card+mid_of_card>M)
				continue;//최대와 차대 값 2개의 합만으로도 M을 넘어서면 다음 순번으로 넘긴다.
			min_of_card=j-2;
			while(min_of_card>=0){
				sum=max_of_card+mid_of_card+num[min_of_card];
				if(sum<=M && sum>max_of_sum) // 결과가 나오면 바로 출력 하는 것이 아니라 끝까지 다 검사 해보고 최대값을 출력 
					max_of_sum=sum;
				min_of_card--;
			}
		}
	}
	return max_of_sum;
}

int main(){
	int num[100]={0};
	cin>>N>>M;
	
	int i=0;
	while(i<N){
		cin>>num[i];
		i++;
	}
	sort(num, num+N);//sort 함수를 이용해서 오름차순으로 정렬.
	cout<<cal(num);
}
