#include <iostream>
using namespace std;

int main(){
	//int arr[6]={500, 100, 50, 10, 5, 1};
	int money;
	cin>>money;
	money=1000-money; // 1000원에서 거슬러줘야하는 금액을 구하는 식. 
	int count=0;
	while(1){
		if(money>=500)
			money-=500;
		else if(money>=100)
			money-=100;
		else if(money>=50)
			money-=50;
		else if(money>=10)
			money-=10;
		else if(money>=5)
			money-=5;
		else if(money>=1)
			money-=1;
		else //money==0 이면 반복문 종료. 
			break;
		count++; 
	}
	cout<<count;
}
