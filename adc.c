#include "adc.h"
#include <LPC11xx.h>
#include "system_LPC11xx.h"


int Ler_Pot (void)
{
    unsigned int uiValor_Pot;
    LPC_ADC->CR      = 0x0C04;
    LPC_ADC->CR     |= (1<<24);


    while(LPC_ADC->GDR&(1<<31));
    LPC_ADC->CR     &= ~(1<<24);


    uiValor_Pot = LPC_ADC->DR[2];
    uiValor_Pot = uiValor_Pot >> 6;
    uiValor_Pot = uiValor_Pot & 0x3FF;
    return (uiValor_Pot*100)/1023; // Configurado de 0 a 100%
}


int Ler_LDR (void)
{
    unsigned int uiValor_LDR;
    LPC_ADC->CR      = 0x0C02;
    LPC_ADC->CR     |= (1<<24);

    while(LPC_ADC->GDR&(1<<31));
    LPC_ADC->CR     &= ~(1<<24);

    uiValor_LDR = LPC_ADC->DR[1];
    uiValor_LDR = uiValor_LDR >> 6;
    uiValor_LDR = uiValor_LDR & 0x3FF;
    return 100-(uiValor_LDR*100)/1023;
}

int Ler_Dif (void)
{
    unsigned int uiValor_Dif;
    LPC_ADC->CR      = 0x0C08;
    LPC_ADC->CR     |= (1<<24);

    while(LPC_ADC->GDR&(1<<31));
    LPC_ADC->CR     &= ~(1<<24);

    uiValor_Dif = LPC_ADC->DR[3];
    uiValor_Dif = uiValor_Dif >> 6;
    uiValor_Dif = uiValor_Dif & 0x3FF;

    return (uiValor_Dif*100)/1023;
}
