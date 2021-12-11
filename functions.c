#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pcap.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <time.h>


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

pcap_t * open_device(char * device){
	pcap_t * handle;
	char error_buffer[PCAP_ERRBUF_SIZE];
	handle = pcap_open_live(device,BUFSIZ,1, 1000, error_buffer);
	if(handle==NULL){
		printf("Error while opening device %s : %s \n", device, error_buffer);
		return NULL; 
	}
	printf("Connection successful with %s \n", device);
	return handle;
}

u_char * intercept_paquet(char * device){
	const u_char *packet;
	pcap_t * handle;
	struct pcap_pkthdr hdr;

	handle = open_device(device);
	packet = pcap_next(handle,&hdr);

	if (packet == NULL){
		printf("Did'n grab any paquet \n");
		return NULL;
	}

	printf("Grabbed packet of length %d\n",hdr.len);
    printf("Recieved at ..... %s",ctime((const time_t *)&hdr.ts.tv_sec)); 
    printf("Ethernet address length is %d\n",ETHER_HDR_LEN);
	return (u_char *)packet;
}

void analyse_packet(u_char * packet){
	struct ether_header *eptr = (struct ether_header *)packet;
	int type = ntohs(eptr->ether_type);

	if(type == ETHERTYPE_IP){
		printf("Ethernet type %d is an IP packet\n",type);
	} else if(type == ETHERTYPE_ARP){
		printf("Ethernet type %d is an ARP packet\n",type);
	} else {
		printf("Ethernet type %d is not IP\n",type);
	}

}

uid_t checkSudo(){
	uid_t user = getuid();
	if((int)user != 0){
		printf("Please, run this as root or with sudo permissions.");
	}
	return user;
}

		

void print_help(){
	printf("Welcome on sniffer based on pcap lib \nUse ./sniffer -h to display this help. \nAll parameters : \n-L : To list all interfaces available to sniff on;\n-t device : To test the connection on the device passed\n-i interface : precise the interface and grab one packet");
}