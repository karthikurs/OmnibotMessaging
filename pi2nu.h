#ifndef PI2NU_H_
#define PI2NU_H_

#include <stdint.h>

struct velocityCmd {
	// 8 bit integer to represent speed of each wheel
	// 0 for stop
	// + 127 max CCW
	// - 127 max CW
	int8_t vel_a;
	int8_t vel_b;
	int8_t vel_c;
	// Error code(State)
	int8_t error;
};

// direct throttle control of motors
struct manualCmd {
	float cmd_a;
	float cmd_b;
	float cmd_c;
}

// check on connection status
struct heartbeat {
	bool beat;
};

// ask nucleo to transition state
struct stateTransition {
	//
};

// remap motor A/B/C
struct motorRemap {
	int8_t newMotorA;
	int8_t newMotorB;
	int8_t newMotorC;
};

struct globalPID{
	float pGain;
	float iGain;
	float dGain;
};

struct singlePID{
	int8_t motorID;
	float pGain;
	float iGain;
	float dGain;
};

#endif
