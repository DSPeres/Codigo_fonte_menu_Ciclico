#include "Funcoes_operacionais.h"

void bit_set( volatile uint32_t *p_uiValor, unsigned char v_ucBit )
{
	(*p_uiValor) |= (1 << v_ucBit);
}
// bit_clr
void bit_clr( volatile uint32_t *p_uiValor, unsigned char v_ucBit )
{
	(*p_uiValor) &= ~(1 << v_ucBit);
}

void delay_ms( unsigned int v_uiTempo )
{
	unsigned int vuiI1;

	do
	{
			// Gerar um atraso aproximado a 1 milissegundo
			for( vuiI1 = 0; vuiI1 < 3000; vuiI1++ );

			v_uiTempo--;

	} while( v_uiTempo > 0 );
}
