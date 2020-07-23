/*
 * messaging.cpp
 *
 *  Created on: July 19, 2020
 *      Author: Karthik
 */

#include "messaging.hpp"

Messaging::Messaging() {
	txMessage_ = nullptr;
	rxCallback_ = nullptr;
}

Messaging::Messaging(void (*txMessage_fcn)(Message* msg_buf),
                     void (*rxCallback_fcn)(Message &msg)) :
										 txMessage_(txMessage_fcn),
										 rxCallback_(rxCallback_fcn) { 
	rxLastMessage_.msgType = NULLMSG;
	txLastMessage_.msgType = NULLMSG;
}


bool Messaging::rxMessageSequence(uint8_t* const serial_data) {
	if(!parseMessage(serial_data)) return false;
	if(!reactMessage()) return false;
	return true;
}

// will return if the msg is valid and store it in rxLastMessage_
bool Messaging::parseMessage(uint8_t* serial_data) {
	if (serial_data[0] > 0x08) return false;
	Message* temp = (Message*)(serial_data);
	if(!checkMessageHash(temp)) return false;
	rxLastMessage_ = *temp;
	return true;
}

// react to lastMessage_
bool Messaging::reactMessage() {
	rxCallback_(rxLastMessage_);
	return true;
}

bool Messaging::checkMessageHash(Message* msg) {
	uint16_t computed_hash = DJBHash((msg->msgData), msg->msgLenBytes);
	return (computed_hash == msg->msgHash);
}

// the struct yourself first
bool Messaging::generateMessage(Message* msg_buf,
                                void* constructed_msg,
                                messageTypeIdentifier msgType_ID) {
	msg_buf->msgType = msgType_ID;
	msg_buf->msgLenBytes = messageSize_(msgType_ID);
	uint8_t* data = (uint8_t*)(constructed_msg);
	memcpy(msg_buf->msgData, data, msg_buf->msgLenBytes);
	msg_buf->msgHash = DJBHash((msg_buf->msgData), msg_buf->msgLenBytes);
	return true;
}

bool Messaging::txMessage(Message* msg_buf) {
	txMessage_(msg_buf);
	return true;
}

uint8_t Messaging::messageSize_(messageTypeIdentifier msgType_ID) {
	switch (msgType_ID) {
		case NULLMSG:               return 0;
		case VELOCITY_CMD:          return 4;
		case MANUAL_CMD:            return 12;
		case HEARTBEAT:             return 1;
		case MOTOR_REMAP:           return 3;
		case GLOBAL_PID:            return 12;
		case SINGLE_PID:            return 16;
		case NUCLEO_GENERAL_UPDATE: return 56;
	}
	return 0;
}

//http://www.partow.net/programming/hashfunctions/index.html
uint16_t Messaging::DJBHash(const uint8_t* msg_data, uint8_t length) {
	uint16_t hash = 5381;
	uint16_t i    = 0;

	for (i = 0; i < length; ++msg_data, ++i) {
		hash = ((hash << 5) + hash) + (*msg_data);
	}

	return hash;
}
