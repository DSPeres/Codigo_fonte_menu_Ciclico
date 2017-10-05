#include <LPC11xx.h>			/* LPC11xx Peripheral Registers */
#include "system_LPC11xx.h"
#include "Serial.h"
#include "Lerevento.h"
#include "Config.h"

char serial, ind, caractere[7];

void Config_Serial (void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);   // habilitar o clock para o bloco IOCON (UM10398, 3.5.14)
    LPC_IOCON->PIO1_7         |= 0x01;      // configurar o pino UART TXD (UM10398, 7.4.41)
    LPC_IOCON->PIO1_6         |= 0x01;      // configurar o pino UART RXD (UM10398, 7.4.41)

    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);    // habilitar o clock para o bloco UART (UM10398, 3.5.14)
    LPC_SYSCON->UARTCLKDIV    |= 0x04;       // estipular o clock do módulo UART (divisor de 4) para gerar BR de 9600 (UM10398, 3.5.16)
    LPC_UART->LCR             |= (1<<7);     // habilitar o acesso aos registros do divisor de clock da UART com DLAB=1 (UM10398, 13.5.7)
    LPC_UART->DLM              = 0x0;        // DLM=0 (UM10398, 3.5.13)
    LPC_UART->DLL              = 0x34;       // DLL=52 (UM10398, 3.5.13)
    LPC_UART->FDR              = 0x21;       // DIVADDVAL = 1, MULVAL = 2 (UM10398, 3.5.15)
    LPC_UART->FCR             |= 0x01;       // habiltiar o FIFO (necessário para operar) (UM10398, 13.5.6)
    LPC_UART->LCR             =  0x03;       // estipular (UM10398, 13.5.7):
    LPC_UART->TER             |= 0x80;       // habilitar a transmissão (UM10398, 13.5.16)
}

int getSerial(void)
{
    if ( LPC_UART->LSR & 0x01 )
    {
        // Esperar pelo fim da transmissão atual (bit TEMT, UM10398, 13.5.9)
        while ( ( LPC_UART->LSR & ( 1 << 6 ) ) == 0 );
        // obter o dado recebido (UM10398, 13.5.1)
        serial = LPC_UART->RBR;

        if (serial == 'e')   // Código ASCII da tecla enter
        {
            return ENTER;
        }
        if (serial == 'a')   // Código ASCII da tecla esquerda
        {
            return ESQUERDA;
        }
        if (serial == 'w')   // Código ASCII da tecla cima
        {
            return CIMA;
        }
        if (serial == 'd')   // Código ASCII da tecla direita
        {
            return DIREITA;
        }
        if (serial == 's')   // Código ASCII da tecla baixo
        {
            return BAIXO;
        }

        if(serial == '$')
        {
            ind = 0;
        }
        caractere[ind] = serial;
        ind++;

        if(ind == 8)
        {

            if(caractere[6]=='\n' && caractere[7]== '\0')
            {
                Protocolo_Serial();
            }
            ind = 0;
        }

    }
    return 0;
}

void serialString(char * txt)
{
    while (*txt != 0)
    {
        LPC_UART->THR=*txt;
        txt++;
    }
    LPC_UART->THR=0x0a;
}

void Protocolo_Serial(void)
{

    if((caractere[1]=='L')&&(caractere[2]=='D'))
    {
        // Ligar Alarme Diferencial
        Liga_Desliga_Alarme_Dif(Alarme_Dif_Ligado);
    }

    if((caractere[1]=='D')&&(caractere[2]=='D'))
    {
        // Desliga Alarme Diferencial
        Liga_Desliga_Alarme_Dif(Alarme_Dif_Desligado);
    }

    if((caractere[1]=='L')&&(caractere[2]=='L'))
    {
        // Ligar Alarme LDR
        Liga_Desliga_Alarme_LDR(Alarme_LDR_Ligado);
    }

    if((caractere[1]=='D')&&(caractere[2]=='L'))
    {
        // Desliga Alarme LDR
        Liga_Desliga_Alarme_LDR(Alarme_LDR_Desligado);
    }

    if((caractere[1]=='D')&&(caractere[2]=='S'))
    {
        // Diferencial Superior
        if ((((caractere[3]*100) + (caractere[4]*10) + caractere[5]) > 100) || (((caractere[3]*100) + (caractere[4]*10) + caractere[5]) < 1))
        {
            serialString("Numero invalido!/n/0");
        }
        else
        {
            Config_Dif_sup(Serial);
        }
    }

    if((caractere[1]=='D')&&(caractere[2]=='I'))
    {
        // Diferencial Inferior
        if ((((caractere[3]*100) + (caractere[4]*10) + caractere[5]) > 99) || (((caractere[3]*100) + (caractere[4]*10) + caractere[5]) < 0))
        {
            serialString("Numero invalido!/n/0");
        }
        else
        {
            Config_Dif_inf(Serial);
        }
    }

    if((caractere[1]=='L')&&(caractere[2]=='S'))
    {
        // LDR Superior
        if ((((caractere[3]*100) + (caractere[4]*10) + caractere[5]) > 100) || (((caractere[3]*100) + (caractere[4]*10) + caractere[5]) < 1))
        {
            serialString("Numero invalido!/n/0");
        }
        else
        {
            Config_LDR_sup(Serial);
        }
    }

    if((caractere[1]=='L')&&(caractere[2]=='I'))
    {
        // LDR Inferior
        if ((((caractere[3]*100) + (caractere[4]*10) + caractere[5]) > 99) || (((caractere[3]*100) + (caractere[4]*10) + caractere[5]) < 0))
        {
            serialString("Numero invalido!/n/0");
        }
        else
        {
            Config_LDR_inf(Serial);
        }
    }
}

int Config_nivel_Alarme (void)
{
    return ((caractere[3]*100) + (caractere[4]*10) + caractere[5]);
}
