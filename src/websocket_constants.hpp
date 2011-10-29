/*
 * Copyright (c) 2011, Peter Thorson. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the WebSocket++ Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * This Makefile was derived from a similar one included in the libjson project
 * It's authors were Jonathan Wallace and Bernhard Fluehmann.
 */

#ifndef WEBSOCKET_CONSTANTS_HPP
#define WEBSOCKET_CONSTANTS_HPP

#include <stdint.h>

// Defaults
namespace websocketpp {
	const uint64_t DEFAULT_MAX_MESSAGE_SIZE = 0xFFFFFF; // ~16MB
	
	// System logging levels
	static const uint16_t LOG_ALL = 0;
	static const uint16_t LOG_DEBUG = 1;
	static const uint16_t LOG_INFO = 2;
	static const uint16_t LOG_WARN = 3;
	static const uint16_t LOG_ERROR = 4;
	static const uint16_t LOG_FATAL = 5;
	static const uint16_t LOG_OFF = 6;
	
	// Access logging controls
	// Individual bits
	static const uint16_t ALOG_CONNECT = 0x1;
	static const uint16_t ALOG_DISCONNECT = 0x2;
	static const uint16_t ALOG_MISC_CONTROL = 0x4;
	static const uint16_t ALOG_FRAME = 0x8;
	static const uint16_t ALOG_MESSAGE = 0x10;
	static const uint16_t ALOG_INFO = 0x20;
	static const uint16_t ALOG_HANDSHAKE = 0x40;
	// Useful groups
	static const uint16_t ALOG_OFF = 0x0;
	static const uint16_t ALOG_CONTROL = ALOG_CONNECT 
									   & ALOG_DISCONNECT 
									   & ALOG_MISC_CONTROL;
	static const uint16_t ALOG_ALL = 0xFFFF;
	
	
	namespace close {
	namespace status {
		enum value {
			INVALID_END = 999,
			NORMAL = 1000,
			GOING_AWAY = 1001,
			PROTOCOL_ERROR = 1002,
			UNSUPPORTED_DATA = 1003,
			RSV_ADHOC_1 = 1004,
			NO_STATUS = 1005,
			ABNORMAL_CLOSE = 1006,
			INVALID_PAYLOAD = 1007,
			POLICY_VIOLATION = 1008,
			MESSAGE_TOO_BIG = 1009,
			EXTENSION_REQUIRE = 1010,
			RSV_START = 1011,
			RSV_END = 2999,
			INVALID_START = 5000
		};
		
		inline bool reserved(value s) {
			return ((s >= RSV_START && s <= RSV_END) || 
					s == RSV_ADHOC_1);
		}
		
		inline bool invalid(value s) {
			return ((s <= INVALID_END || s >= INVALID_START) || 
					s == NO_STATUS || 
					s == ABNORMAL_CLOSE);
		}
		
		// TODO functions for application ranges?
	}
	}
	
	namespace frame {
		namespace error {
			enum value {
				FATAL_SESSION_ERROR = 0,	// force session end
				SOFT_SESSION_ERROR = 1,		// should log and ignore
				PROTOCOL_VIOLATION = 2,		// must end session
				PAYLOAD_VIOLATION = 3,		// should end session
				INTERNAL_SERVER_ERROR = 4,	// cleanly end session
				MESSAGE_TOO_BIG = 5			// ???
			};
		}
		
		// Opcodes are 4 bits
		// See spec section 5.2
		namespace opcode {
			enum value {
				CONTINUATION = 0x0,
				TEXT = 0x1,
				BINARY = 0x2,
				RSV3 = 0x3,
				RSV4 = 0x4,
				RSV5 = 0x5,
				RSV6 = 0x6,
				RSV7 = 0x7,
				CLOSE = 0x8,
				PING = 0x9,
				PONG = 0xA,
				CONTROL_RSVB = 0xB,
				CONTROL_RSVC = 0xC,
				CONTROL_RSVD = 0xD,
				CONTROL_RSVE = 0xE,
				CONTROL_RSVF = 0xF,
			};
			
			inline bool reserved(value v) {
				return (v >= RSV3 && v <= RSV7) || 
				       (v >= CONTROL_RSVB && v <= CONTROL_RSVF);
			}
			
			inline bool invalid(value v) {
				return (v > 0xF || v < 0);
			}
			
			inline bool is_control(value v) {
				return v >= 0x8;
			}
		}
		
		namespace limits {
			static const uint8_t PAYLOAD_SIZE_BASIC = 125;
			static const uint16_t PAYLOAD_SIZE_EXTENDED = 0xFFFF; // 2^16, 65535
			static const uint64_t PAYLOAD_SIZE_JUMBO = 0x7FFFFFFFFFFFFFFF;//2^63
		}
	}
}

#endif // WEBSOCKET_CONSTANTS_HPP
