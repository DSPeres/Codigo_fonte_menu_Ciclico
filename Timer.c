#include <LPC11xx.h>
#include "system_LPC11xx.h"

void AguardaTimer(void)
{
    // esperar pelo estouro do timer (bit EM0, UM10398, 18.7.10)
    while ( !( LPC_TMR16B0->EMR & 0x01 ) );
    LPC_TMR16B0->TCR  = 0x00;               // desabilitar o TMR16 (bit CEn, UM10398, 18.7.2)
}

//tempo em mS
void ResetaTimer(unsigned int tempo)
{
    LPC_TMR16B0->PR  = (0xFFFF & tempo);    // estipular o pré-escalar do TMR16 para a quantidade de milissegundos a esperar (UM10398, 18.7.4).
    LPC_TMR16B0->TCR  = 0x01;               // habilitar o TMR16 (bit CEn, UM10398, 18.7.2)

    LPC_TMR16B0->EMR  = ~(0x01);            // limpar o sinal de estouro do temporizador (bit EM0, UM10398, 18.7.10)
}

void InicializaTimer(void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);    // habilitar o clock para o bloco TMR16 (UM10398, 3.5.14)
    LPC_TMR16B0->MR0          = 0xBB80;     // registro de correspondência em 48000 (UM10398, 18.7.7)
    LPC_TMR16B0->MCR          |= (1<<1);    // ao ocorrer uma correspondência, o TMR16 deve reiniciar (UM10398, 18.7.6)
    LPC_TMR16B0->CTCR         =  0x00;      // habilitar o modo temporizador do TMR16 (UM10398, 18.7.11)
}
