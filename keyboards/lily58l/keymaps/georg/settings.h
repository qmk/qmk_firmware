#pragma once

typedef union {
	uint32_t raw;
	struct {
		bool 	dead_keys :1;
	};
} user_config_t;

user_config_t user_config;