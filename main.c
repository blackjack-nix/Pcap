#include "functions.h"
#include "functions.c"

int main(char * argc, char * argv[]){
	char * device = detect_device();
	if (device == NULL){
		return 1;
	}



}