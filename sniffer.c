#include <string.h>

#include "functions.h"
#include "functions.c"

int main(int argc, char * argv[]){
	

	if(argc == 1){
		printf("Use ./sniffer -h to print help");
		return 1;
	}

	if(strcmp(argv[1],"-h") == 0 && argc == 2){
		print_help();
		return 0;
	}

	if(strcmp(argv[1],"-L") == 0 && argc == 2){
		detect_all_devices();
		return 0;
	}

	if(strcmp(argv[1],"-t") == 0 && argc == 3){
		test_device(argv[2]);
	}


}