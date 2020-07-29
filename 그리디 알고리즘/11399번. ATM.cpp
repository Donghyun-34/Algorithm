#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int arr[1001]={0}; //사람들의 인출 시간을 저장하는 배열(최대수가 1000명이므로 1001칸 선언) 
	int n=0;
	cin>>n;
	for(int i=0; i<n; i++){
		cin>>arr[i];
	}
	sort(arr, arr+n); //기본적으로 오름차순으로 정렬.
	int sum=0;
	for(int i=0;i<n;i++){
		sum+=arr[i]*(n-i);//n-i를 곱하는 이유는 i번째 값이 총 n-i번 계산에 사용되기 때문이다. 
	}
	cout<<sum;
}

