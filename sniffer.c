#include <string.h>
#include <unistd.h>

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
		uid_t user =  getuid();
		if((int)user != 0){
			printf("Please, run this as root or with sudo permissions.");
			return 1;
		}

		open_device(argv[2]);
		return 0;
	}

	if(strcmp(argv[1],"-i") == 0 && argc == 3){
		u_char * paquet = intercept_paquet(argv[2]);
		if(paquet == NULL){
			return 1;
		}
		return 0;
	}


}