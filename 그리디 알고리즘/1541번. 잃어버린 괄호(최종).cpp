/*
	greedy 알고리즘 연습용 문제(백준 1541번. 잃어버린 괄호)
	문제 분석 : 숫자와 '+', '-'가 주어지고 해당 값들을 가지고 만들 수 있는 최소값 구하기. 
	해 선택 전략 : '-'의 존재 여부를 기준으로 경우를 나눈다.
					1. '-' 없는 경우 : 그냥 전체 합이 곧 최소값.
					2. '-' 존재 : -가 나오기 전과 후의 식을 더한 값이 최소값. 
						-> -가 2개 이상일 경우에도 순차적으로 작용하면 된다.(결과적으로 잘못된 생각은 아니었지만,
							식이 너무 복잡해져서 비효율적이었다.
					3. 최종 전략 : '-'가 하나라도 나오면 그 뒤에 오는 나머지 식들은 전부 '-'로 계산하면 최소값이 나온다. 
	접근 방법 : 계산식의 결과 중 최소값을 찾는 문제이므로, '-'의 갯수에 집중. 
*/
#include <iostream>
#include <string>
using namespace std;
string calcul;

int Result(void)
{
        int result = 0;
        string temp = "";
        bool minus = false;
        for (int i = 0; i <= calcul.size(); i++)
        {
            if (calcul[i] == '+' || calcul[i] == '-' || calcul[i] == '\0')
			{
				if (minus)
					result -= stoi(temp);
				else
					result += stoi(temp);
				temp = "";
				if (calcul[i] == '-'){//'-'가 하나라도 나오면 그 뒤에 있는 모든 식은 다 뺄셈으로 계산되는 것이 최소값이다. 
					minus = true;
				}
			}
			else
				temp += calcul[i];
		}
		return result;
}

int main(void)
{
	cin >> calcul;
	cout << Result() << endl;
	return 0;
}
