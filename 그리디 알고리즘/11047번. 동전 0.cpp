#include <iostream>
using namespace std;

int main(void){
	int money=0, length=0;
	cin>>length>>money; //금액의 크기와 동전의 종류수를 입력받는다. 
	int * array=new int[length];
	int i=0;
	for(i=0; i<length; i++){
		cin>>array[i];
	}
	int count=0;
	while(1){
		count+=money/array[i-1];//위에서 사용한 i를 재사용함(크기가 최대값과 같으므로 1을 빼주고 사용한다.) 
		if(money%array[i-1]==0)
			break;
		money=money%array[i-1];
		i--;
	}
	cout<<count;
}
