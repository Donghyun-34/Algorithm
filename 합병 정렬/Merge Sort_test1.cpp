/*
	Merge Sort 알고리즘 연습용.
*/
# include <stdio.h>
# define MAX_SIZE 8

int sorted[MAX_SIZE];


/* 정렬된 리스트들을 하나로 병합 */
void merge(int list[], int left, int mid, int right){
  int i, j, k, l;
  i = left;
  j = mid+1;
  k = left;

	/*
	i: 정렬된 왼쪽 리스트에 대한 인덱스	
	j: 정렬된 오른쪽 리스트에 대한 인덱스	
	k: 정렬될 리스트에 대한 인덱스 
	*/ 
  while(i<=mid && j<=right){
    if(list[i]<=list[j])//왼쪽 리스트 값이 더 큰 경우, 해당 값을 sorted배열에 넣고 왼쪽 리스트의 위치 이동. 
      sorted[k++] = list[i++];
    else//오른쪽 리스트 값이 더 큰 경우, 해당 값을 sorted배열에 넣고 오른쪽 리스트의 위치 이동. 
      sorted[k++] = list[j++];
  }

  if(i>mid){//오른쪽 리스트에 값이 남아있을 경우 
    for(l=j; l<=right; l++)
		sorted[k++] = list[l];
  }
  else{//왼쪽 리스트에 값이 남아있을 경우 
    for(l=i; l<=mid; l++)
		sorted[k++] = list[l];
  }

  // 임시 배열의 리스트를 배열 list[]로 재복사
  for(l=left; l<=right; l++){
    list[l] = sorted[l];
  }
}

// 합병 정렬
void merge_sort(int list[], int left, int right){
  int mid;

  if(left<right){
    mid = (left+right)/2; // 중간 위치를 계산하여 리스트를 균등 분할 -분할(Divide)
    merge_sort(list, left, mid); // 앞쪽 부분 리스트 정렬 -정복(Conquer)
    merge_sort(list, mid+1, right); // 뒤쪽 부분 리스트 정렬 -정복(Conquer)
    merge(list, left, mid, right); // 정렬된 2개의 부분 배열을 합병하는 과정 -결합(Combine)
  }
  
}

int main(){
  int i;
  int n = MAX_SIZE;
  int list[n] = {21, 10, 12, 20, 25, 13, 15, 22};

  // 합병 정렬 수행
  merge_sort(list, 0, n-1);

  // 정렬 결과 출력
  for(i=0; i<n; i++){
    printf("%d\n", list[i]);
  }
  
  return 0; 
}
