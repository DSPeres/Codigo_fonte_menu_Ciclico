#ifndef FUNCOES_OPERACIONAIS_H_INCLUDED
#define FUNCOES_OPERACIONAIS_H_INCLUDED

#include <LPC11xx.h>			/* LPC11xx Peripheral Registers */
#include "system_LPC11xx.h"

void bit_set( volatile uint32_t *p_iValor, unsigned char v_ucBit );
void bit_clr( volatile uint32_t *p_iValor, unsigned char v_ucBit );
void delay_ms( unsigned int v_uiTempo );

#endif /* FUNCOES_OPERACIONAIS_H_INCLUDED */
