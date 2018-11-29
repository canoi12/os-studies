#include "data.h"

int main (int argc, char ** argv) {

	Data * data = init_data();

	print_fcfs(data);
	print_sstf(data);
	print_scan_desce(data);
	print_scan_sobe(data);

	return 0;
}