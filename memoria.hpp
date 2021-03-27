

#ifndef __MEMORIA_H__
#define __MEMORIA_H__

#include <stdint.h>
#include "globals.h"
int32_t mem[MEM_SIZE];

inline void check_address_range(uint32_t address){
	if((address>>2)>MEM_SIZE){
		cout<< "Erro:endereço fora dos limites da memoria -"<< address;
		return;
	}
}

inline int32_t lb(const uint32_t &address, int32_t kte){
	uint32_t tmp = address + kte;
	check_address_range(tmp);
	int8_t *pb = (int8_t *)&mem;

	return(*(pb+tmp));
}

inline uint32_t lbu(const uint32_t &address, int32_t kte) {
	uint32_t tmp = address + kte;
	check_address_range(tmp);
	uint8_t *pb = (uint8_t *)&mem;

	return(*(pb+tmp));

}

inline int32_t lw(const uint32_t &address, int32_t kte){
	uint32_t tmp = address + kte;
	check_address_range(tmp);
	int32_t word = mem[tmp>>2];
	return word;
}

inline void sb(const uint32_t &address, int32_t kte, int8_t dado){
	uint32_t tmp = address + kte;
	check_address_range(tmp);

	uint32_t bi = (tmp%4);
	uint8_t *pb = (uint8_t *)&mem[tmp>>2];
	pb += bi;

	*pb = (uint8_t)dado;
}

inline void sw(const uint32_t &address, int32_t kte, int32_t dado){
	uint32_t tmp = address +kte;
	check_address_range(tmp);
	mem[tmp>>2] = dado;
}

#endif