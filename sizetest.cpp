#include <iostream>

#include "pi2nu.h"
#include "nu2pi.h"

int main() {
	velocityCmd velocityCmd_msg;
	std::cout << sizeof(velocityCmd_msg) << std::endl;
	manualCmd manualCmd_msg;
	std::cout << sizeof(manualCmd_msg) << std::endl;
	heartbeat heartbeat_msg;
	std::cout << sizeof(heartbeat_msg) << std::endl;
	motorRemap motorRemap_msg;
	std::cout << sizeof(motorRemap_msg) << std::endl;
	globalPID globalPID_msg;
	std::cout << sizeof(globalPID_msg) << std::endl;
	singlePID singlePID_msg;
	std::cout << sizeof(singlePID_msg) << std::endl;

	return 0;
}