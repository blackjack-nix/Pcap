#include <stdio.h>
#include <pcap.h>
#include <unistd.h>


#include "functions.h"

char * detect_device() {
    char *device; /* Name of device (e.g. eth0, wlan0) */
    char error_buffer[PCAP_ERRBUF_SIZE]; /* Size defined in pcap.h */

    /* Find a device */
    device = pcap_lookupdev(error_buffer);
    if (device == NULL) {
        printf("Error finding device: %s\n", error_buffer);
        return NULL;
    }

    printf("Network device found: %s\n", device);
    return device;
}

void detect_all_devices(){
	pcap_if_t *all_devices;
	char * device;
	char error_buffer[PCAP_ERRBUF_SIZE];

	pcap_findalldevs(&all_devices, error_buffer);

	printf("%s ",all_devices -> name);

	while (1){
		printf(" %s",all_devices->name);
		all_devices = all_devices->next;
		if (all_devices->next == NULL)
		{
			return;
		}
	}
}

pcap_t * test_device(char * device){
	pcap_t * handle;
	char error_buffer[PCAP_ERRBUF_SIZE];
	handle = pcap_open_live(device,BUFSIZ,1, 1000, error_buffer);
	if(handle==NULL){
		printf("Error while opening device %s : %S", device, error_buffer);
		return NULL; 
	}
	printf("Connection successful with %s", device);
	return handle;
}

void print_help(){
	printf("Welcome on sniffer based on pcap lib \nUse ./sniffer -h to display this help. \nAll parameters : \n-L : To list all interfaces available to sniff on;\n-t device : To test the connection on the device passed");
}