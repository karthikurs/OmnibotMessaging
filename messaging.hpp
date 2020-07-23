/*
 * messaging.hpp
 *
 *  Created on: July 19, 2020
 *      Author: Karthik
 */

#ifndef INC_MESSAGING_HPP_
#define INC_MESSAGING_HPP_

#include "nu2pi.h"
#include "pi2nu.h"

#include <stdint.h>
#include <stdlib.h>

class Messaging {
	public:
		// for message distinction
		enum messageTypeIdentifier : uint8_t {
			NULLMSG               = 0x00,
			VELOCITY_CMD          = 0x01,
			MANUAL_CMD            = 0x02,
			HEARTBEAT             = 0x03,
			STATE_TRANSITION      = 0x04,
			MOTOR_REMAP           = 0x05,
			GLOBAL_PID            = 0x06,
			SINGLE_PID            = 0x06
		};

		enum messagingError_t : uint8_t {
			//
		};

		typedef struct {
			messageTypeIdentifier msgType;
			uint8_t               msgLenBytes;
			uint8_t               msgData[60];
			uint16_t              msgHash;
		} Message;

		Messaging();

		Messaging(void (*txMessage_fcn)(Message* msg_buf),
		          void (*rxCallback_fcn)(Message &msg));

		bool rxMessageSequence(uint8_t* serial_data);

		// will return if the msg is valid and store it in rxLastMessage_
		bool parseMessage(uint8_t* serial_data);

		// react to lastMessage_
		bool reactMessage();

		bool checkMessageHash(Message* msg);

		// to be used if you did make the struct yourself
		// needs overloaded protos for each msg
		bool generateMessage(Message* msg_buf, nu2pi &nu2pi_msg);
		bool generateMessage(Message* msg_buf, pi2nu &pi2nu_msg);

		bool txMessage(Message* msg_buf);
	private:
		Message rxLastMessage_;
		Message txLastMessage_;
		// function pointer to tx message with
		void (*txMessage_)(Message* msg_buf);

		// function poiner to message reaction
		void (*rxCallback_)(Message &msg);
		// hash function for error checking
		uint16_t DJBHash(const uint8_t* msg_data, uint8_t length);

};

#endif /* INC_MESSAGING_HPP_ */
