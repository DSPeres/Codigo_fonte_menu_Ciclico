#include <LPC11xx.h>			/* LPC11xx Peripheral Registers */
#include "system_LPC11xx.h"
#include "Driver_Teclado.h"

unsigned int Verificar_Teclado(unsigned char tecla)
{
    if ( LPC_GPIO2->DATA & (1 << tecla) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void Inicializa_Teclado (void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);    // habilitar o clock para o módulo IOCON (UM10398, 3.5.14)
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);    // habilitar o clock para o módulo GPIO (UM10398, 3.5.14)
    LPC_IOCON->PIO2_6 = 0xC8;
    LPC_IOCON->PIO2_7 = 0xC8;
    LPC_IOCON->PIO2_8 = 0xC8;
    LPC_IOCON->PIO2_9 = 0xC8;
    LPC_IOCON->PIO2_10 = 0xC8;
    LPC_GPIO2->DIR  &= ~(1 << PINO_TECLA_CIMA);    // configurar o pino PTO2_6 como entrada digital (UM10398, 12.3.2)
    LPC_GPIO2->DIR  &= ~(1 << PINO_TECLA_CENTRO);    // configurar o pino PTO2_7 como entrada digital (UM10398, 12.3.2)
    LPC_GPIO2->DIR  &= ~(1 << PINO_TECLA_BAIXO);    // configurar o pino PTO2_8 como entrada digital (UM10398, 12.3.2)
    LPC_GPIO2->DIR  &= ~(1 << PINO_TECLA_ESQUERDA);    // configurar o pino PTO2_9 como entrada digital (UM10398, 12.3.2)
    LPC_GPIO2->DIR  &= ~(1 << PINO_TECLA_DIREITA);    // configurar o pino PTO2_10 como entrada digital (UM10398, 12.3.2)
}
