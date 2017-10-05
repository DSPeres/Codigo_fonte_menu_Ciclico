#include <LPC11xx.h>			/* LPC11xx Peripheral Registers */
#include "system_LPC11xx.h"
#include "Funcoes_operacionais.h"
// LCD_comando
// Enviar um comando ao LCD
void LCD_comando(char v_cComando)
{
    // Sinalizar o envio de um comando
    bit_clr( &LPC_GPIO1->DATA, 10 );
    // Enviar o comando aos pinos de dados D0 a D7
    if((v_cComando & 0x01) == 0)  //B0
    {
        bit_clr( &LPC_GPIO1->DATA, 5 );
    }
    else
    {
        bit_set( &LPC_GPIO1->DATA, 5 );
    }

    if((v_cComando & 0x02) == 0)  //B1
    {
        bit_clr( &LPC_GPIO1->DATA, 8 );
    }
    else
    {
        bit_set( &LPC_GPIO1->DATA, 8 );
    }

    if((v_cComando & 0x04) == 0)  //B2
    {
        bit_clr( &LPC_GPIO1->DATA, 9 );
    }
    else
    {
        bit_set( &LPC_GPIO1->DATA, 9 );
    }

    if((v_cComando & 0x08) == 0)  //B3
    {
        bit_clr( &LPC_GPIO1->DATA, 11 );
    }
    else
    {
        bit_set( &LPC_GPIO1->DATA, 11 );
    }

    if((v_cComando & 0x10) == 0)  //B4
    {
        bit_clr( &LPC_GPIO2->DATA, 0 );
    }
    else
    {
        bit_set( &LPC_GPIO2->DATA, 0 );
    }

    if((v_cComando & 0x20) == 0)  //B5
    {
        bit_clr( &LPC_GPIO2->DATA, 1 );
    }
    else
    {
        bit_set( &LPC_GPIO2->DATA, 1 );
    }

    if((v_cComando & 0x40) == 0)  //B6
    {
        bit_clr( &LPC_GPIO2->DATA, 2 );
    }
    else
    {
        bit_set( &LPC_GPIO2->DATA, 2 );
    }

    if((v_cComando & 0x80) == 0)  //B7
    {
        bit_clr( &LPC_GPIO2->DATA, 3 );
    }
    else
    {
        bit_set( &LPC_GPIO2->DATA, 3 );
    }
    delay_ms(1);
    // Enviar o sinal de dados válidos (pulso positivo no pino E)
    bit_set( &LPC_GPIO2->DATA, 4 );
    delay_ms(1);
    bit_clr( &LPC_GPIO2->DATA, 4 );
}
void LCD_iniciar(void)
{
//
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);    				// habilitar o clock para o módulo GPIO (UM10398, 3.5.14)
    LPC_GPIO2->DIR |= (1 << 4); // pino E como sáida digital
    LPC_GPIO1->DIR |= (1 << 10); //pino RS como sáida digital
// configurar como saídas digitais os 8 primeiros pinos da porta de dados do LCD
    LPC_GPIO1->DIR |= (1 << 5); //DB0
    LPC_GPIO1->DIR |= (1 << 8); //DB1
    LPC_GPIO1->DIR |= (1 << 9); //DB2
    LPC_GPIO1->DIR |= (1 << 11); //DB3
    LPC_GPIO2->DIR |= (1 << 0); //DB4
    LPC_GPIO2->DIR |= (1 << 1); //DB5
    LPC_GPIO2->DIR |= (1 << 2); //DB6
    LPC_GPIO2->DIR |= (1 << 3); //DB7

    LPC_IOCON->R_PIO1_0      = 0x02;       // configurar o pino PIO1_0 (AD1) como entrada analógica (UM10398, 7.4.29)
    LPC_IOCON->R_PIO1_1      = 0x02;       // configurar o pino PIO1_1 (AD2) como entrada analógica (UM10398, 7.4.29)
    LPC_IOCON->R_PIO1_2      = 0x02;       // configurar o pino PIO1_2 (AD3) como entrada analógica (UM10398, 7.4.29)
    // Configurar o AD para amostrar

    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);   // habilitar o clock para o bloco AD (UM10398, 3.5.14)
    LPC_SYSCON->PDRUNCFG      &= ~(1<<4);   // ativar o AD (UM10398,3.5.36)

    bit_clr( &LPC_GPIO2->DATA, 4 );
    bit_clr( &LPC_GPIO1->DATA, 10);
    // Esperar pela inicialização do visor
    delay_ms(1000);
    // Enviar a sequência 0b0011****
    LCD_comando(0x30);
    delay_ms(5);
    // Enviar a sequência 0b0011****
    LCD_comando(0x30);
    delay_ms(5);
    // Enviar a sequência 0b0011****
    LCD_comando(0x30);
    delay_ms(5);
    // Requisitar modo de 8 bits, 2 linhas e fonte 5x10
    LCD_comando(0x3C);
    delay_ms(20);
    // Ligar o visor, ligar o cursor e colocá-lo piscando
    LCD_comando(0x0F);
    delay_ms(20);
    // Limpar o visor
    LCD_comando(0x01);
    delay_ms(20);
    // I/D = 1, S=0
    LCD_comando(0x06);
    delay_ms(20);
}
// LCD_caractere
// Enviar um caractere ao LCD
void LCD_caractere( char v_cCaractere )
{
    // Sinalizar o envio de um caractere
    bit_set( &LPC_GPIO1->DATA, 10 );
    // Enviar o caractere aos pinos de dados D0 a D7
    if((v_cCaractere & 0x01) == 0)  //B0
    {
        bit_clr( &LPC_GPIO1->DATA, 5 );
    }
    else
    {
        bit_set( &LPC_GPIO1->DATA, 5 );
    }

    if((v_cCaractere & 0x02) == 0)  //B1
    {
        bit_clr( &LPC_GPIO1->DATA, 8 );
    }
    else
    {
        bit_set( &LPC_GPIO1->DATA, 8 );
    }

    if((v_cCaractere & 0x04) == 0)  //B2
    {
        bit_clr( &LPC_GPIO1->DATA, 9 );
    }
    else
    {
        bit_set( &LPC_GPIO1->DATA, 9 );
    }

    if((v_cCaractere & 0x08) == 0)  //B3
    {
        bit_clr( &LPC_GPIO1->DATA, 11 );
    }
    else
    {
        bit_set( &LPC_GPIO1->DATA, 11 );
    }

    if((v_cCaractere & 0x10) == 0)  //B4
    {
        bit_clr( &LPC_GPIO2->DATA, 0 );
    }
    else
    {
        bit_set( &LPC_GPIO2->DATA, 0 );
    }

    if((v_cCaractere & 0x20) == 0)  //B5
    {
        bit_clr( &LPC_GPIO2->DATA, 1 );
    }
    else
    {
        bit_set( &LPC_GPIO2->DATA, 1 );
    }

    if((v_cCaractere & 0x40) == 0)  //B6
    {
        bit_clr( &LPC_GPIO2->DATA, 2 );
    }
    else
    {
        bit_set( &LPC_GPIO2->DATA, 2 );
    }

    if((v_cCaractere & 0x80) == 0)  //B7
    {
        bit_clr( &LPC_GPIO2->DATA, 3 );
    }
    else
    {
        bit_set( &LPC_GPIO2->DATA, 3 );
    }
    delay_ms(1);
    // Enviar o sinal de dados válidos (pulso positivo no pino E)
    bit_set( &LPC_GPIO2->DATA, 4 );
    delay_ms(1);
    bit_clr( &LPC_GPIO2->DATA, 4 );
}
void lcdString(char * txt)
{
    while (*txt != 0)
    {
        LCD_caractere(*txt);
        txt++;
    }
}
void LCD_number4(unsigned int a){

    LCD_caractere((a/1000)%10+'0');
    LCD_caractere((a/100)%10+'0');
    LCD_caractere((a/10)%10+'0');
    LCD_caractere(a%10+'0');
}
void LCD_number3(unsigned int a){

    LCD_caractere((a/100)%10+'0');
    LCD_caractere((a/10)%10+'0');
    LCD_caractere(a%10+'0');
}
void LCD_number2(unsigned int a){

    LCD_caractere((a/10)%10+'0');
    LCD_caractere(a%10+'0');
}
