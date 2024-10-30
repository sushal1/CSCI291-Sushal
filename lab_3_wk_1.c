#include <stdio.h>
#include <stdbool.h> 

bool isValid(const int arr[],int length, int pos);
int arr[] = {1,2,3,4,5};



int main(){
	int length = 5;
	printf("%s ", isValid(arr, length, 1)?"true" : "false");
	
	
}



bool isValid(const int arr[], int length, int pos){
return pos>=0 && pos<length;
}
