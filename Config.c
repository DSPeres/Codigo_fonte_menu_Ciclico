#include <LPC11xx.h>
#include "system_LPC11xx.h"
#include "Config.h"
#include "Funcoes_operacionais.h"
#include "Lerevento.h"
#include "adc.h"
#define LED_PORT LPC_GPIO3
#define LED_PIN  5 // Pino GPIO3_5
#define BUZZER_PORT LPC_GPIO3
#define BUZZER_PIN  4 // Pino GPIO3_4


int Valor_LDR, Valor_LDR_Inf, Valor_LDR_Sup, Valor_POT, Valor_POT_Inf,
    Valor_POT_Sup, Al_LDR, Al_POT, SEN1=0, SEN2=0, SEN3=0, SEN4=0, S,
    f = 100, D=1, M=1, A=2017, Valor_tempo;
void Liga_Desliga_Alarme_LDR (int status)
{
    if (status == Alarme_LDR_Ligado)
        Al_LDR = Alarme_LDR_Ligado;
    else if (status == Alarme_LDR_Desligado)
        Al_LDR = Alarme_LDR_Desligado;
}
void Liga_Desliga_Alarme_POT (int status)
{
    if (status == Alarme_POT_Ligado)
        Al_POT = Alarme_POT_Ligado;
    else if (status == Alarme_POT_Desligado)
        Al_POT = Alarme_POT_Desligado;
}
//int Verificar_Alarme (void)
//{
//    Valor_LDR = Ler_LDR();
//    if (Al_LDR == Alarme_LDR_Ligado)
//    {
//       if (Valor_LDR <= Valor_LDR_Inf || Valor_LDR >= Valor_LDR_Sup)
//        {
//            return ALARME_LDR;
//        }
//    }
//    Valor_POT = Ler_Pot();
 //   if (Al_POT == Alarme_POT_Ligado)
  //  {
    //    if (Valor_POT <= Valor_POT_Inf || Valor_POT >= Valor_POT_Sup)
      //  {
        //    return ALARME_POT;
 //       }
  //  }
   // return NO_EVENT;
//}
int LDR_inf (int evento)
{
    if (( evento == CIMA) && (Valor_LDR_Inf <= 99))
    {
        Valor_LDR_Inf = Valor_LDR_Inf + 1;
    }
    if ((evento == CIMA) && (Valor_LDR_Inf > 99))
    {
        Valor_LDR_Inf = 0;
    }
    if ((evento == BAIXO) && (Valor_LDR_Inf >= 0))
    {
        Valor_LDR_Inf = Valor_LDR_Inf - 1;
    }
    if ((evento == BAIXO) && (Valor_LDR_Inf < 0))
    {
        Valor_LDR_Inf = 100;
    }
    if (evento == NO_EVENT)
    {
        return Valor_LDR_Inf;
    }
    else
        return Valor_LDR_Inf;
}
int LDR_sup (int evento)
{
    if (( evento == CIMA) && (Valor_LDR_Sup <= 99))
    {
        Valor_LDR_Sup = Valor_LDR_Sup + 1;
    }
    if ((evento == CIMA) && (Valor_LDR_Sup> 99))
    {
        Valor_LDR_Sup = 0;
    }
    if ((evento == BAIXO) && (Valor_LDR_Sup >= 0))
    {
        Valor_LDR_Sup = Valor_LDR_Sup - 1;
    }
    if ((evento == BAIXO) && (Valor_LDR_Sup < 0))
    {
        Valor_LDR_Sup = 100;
    }
    if (evento == NO_EVENT)
    {
        return Valor_LDR_Sup;
    }
    else
        return Valor_LDR_Sup;
}
int LDR_supe(void)
{
    return Valor_LDR_Sup;
}
int LDR_infe(void)
{
    return Valor_LDR_Inf;
}
void Config_Freq_Atualizacao (int valor)
{
    Valor_tempo = valor;
}
int tempo (void)
{
    return Valor_tempo;
}
    unsigned int delay=0;
  void Alarme(int Lvl) {
      // Configurar o pino PT3_5 como saída
      LED_PORT->DIR  |= (1 << LED_PIN);
      // Configurar o pino PT3_4 como saída
      BUZZER_PORT->DIR  |= (1 << BUZZER_PIN);
      delay++;
      if (Lvl == Alto) {
          if(delay>1) {
              // Alternar o nível lógico no pino PT3_5
              LED_PORT->DATA ^= (1 << LED_PIN);
              // Alternar o nível lógico no pino PT3_4
              BUZZER_PORT->DATA ^= (1 << BUZZER_PIN);
              delay=0;
          }
     }
      if (Lvl == Baixo) {
          if (delay>6) {
             // Alternar o nível lógico no pino PT3_5
              LED_PORT->DATA ^= (1 << LED_PIN);
              // Alternar o nível lógico no pino PT3_4
              BUZZER_PORT->DATA ^= (1 << BUZZER_PIN);
              delay=0;
          }
      }
  }
  void Desliga_LED_BUZZER(void) {
      BUZZER_PORT->DATA &= (0 << BUZZER_PIN);
      LED_PORT->DATA |= (1 << LED_PIN);
 }
        int Valor_Freq(int evento)
        {
            if (( evento == CIMA) && (f <= 200))
            {
                f = f + 10;
            }
            if ((evento == CIMA) && (f > 200))
            {
                f = 100;
            }
            if ((evento == BAIXO) && (f >= 100 ))
            {
                f = f - 10;
            }
            if ((evento == BAIXO) && (f < 100))
            {
                f = 200;
            }
            if (evento == NO_EVENT)
            {
                return f;
            }
            else
                return f;
        }
        int Freq(void)
        {
            return f;
        }
        int Valor_SENHA1(int evento)
        {
            if (( evento == CIMA) && (SEN1 <= 9))
            {
                SEN1 = SEN1 + 1;
            }
            if ((evento == CIMA) && (SEN1 > 9))
            {
                SEN1 = 0;
            }
            if ((evento == BAIXO) && (SEN1 >= 0))
            {
                SEN1 = SEN1 - 1;
            }
            if ((evento == BAIXO) && (SEN1 < 0))
            {
                SEN1 = 9;
            }
            if (evento == NO_EVENT)
            {
                return SEN1;
            }
            else
                return SEN1;
        }
        int Valor_SENHA2(int evento)
        {
            if (( evento == CIMA) && (SEN2 <= 9))
            {
                SEN2 = SEN2 + 1;
            }
            if ((evento == CIMA) && (SEN2 > 9))
            {
                SEN2 = 0;
            }
            if ((evento == BAIXO) && (SEN2 >= 0))
            {
                SEN2 = SEN2 - 1;
            }
            if ((evento == BAIXO) && (SEN2 < 0))
            {
                SEN2 = 9;
            }
            if (evento == NO_EVENT)
            {
                return SEN2;
            }
            else
                return SEN2;
        }
        int Valor_SENHA3(int evento)
        {
            if (( evento == CIMA) && (SEN3 <= 9))
            {
                SEN3 = SEN3 + 1;
            }
            if ((evento == CIMA) && (SEN3 > 9))
            {
                SEN3 = 0;
            }
            if ((evento == BAIXO) && (SEN3 >= 0))
            {
                SEN3 = SEN3 - 1;
            }
            if ((evento == BAIXO) && (SEN3 < 0))
            {
                SEN3 = 9;
            }
            if (evento == NO_EVENT)
            {
                return SEN3;
            }
            else
                return SEN3;
        }
        int Valor_SENHA4(int evento)
        {
            if (( evento == CIMA) && (SEN4 <= 9))
            {
                SEN4 = SEN4 + 1;
            }
            if ((evento == CIMA) && (SEN4 > 9))
            {
                SEN4 = 0;
            }
            if ((evento == BAIXO) && (SEN4 >= 0))
            {
                SEN4 = SEN4 - 1;
            }
            if ((evento == BAIXO) && (SEN4 < 0))
            {
                SEN4 = 9;
            }
            if (evento == NO_EVENT)
            {
                return SEN4;
            }
            else
                return SEN4;
        }
        int SENHA(void)
        {
            S = SEN1*1000 + SEN2*100 + SEN3*10 + SEN4;

            return S;
        }
        int Valor_DIA(int evento)
        {
            if (( evento == CIMA) && (D <= 31))
            {
                D = D + 1;
            }
            if ((evento == CIMA) && (D > 31))
            {
                D = 1;
            }
            if ((evento == BAIXO) && (D >= 1))
            {
                D = D - 1;
            }
            if ((evento == BAIXO) && (D < 1))
            {
                D = 31;
            }
            if (evento == NO_EVENT)
            {
                return D;
            }
            else
                return D;
        }
        int Valor_MES(int evento)
        {
            if (( evento == CIMA) && (M <= 12))
            {
                M = M + 1;
            }
            if ((evento == CIMA) && (M > 12))
            {
                M = 1;
            }
            if ((evento == BAIXO) && (M >= 1))
            {
                M = M - 1;
            }
            if ((evento == BAIXO) && (M < 1))
            {
                M = 12;
            }
            if (evento == NO_EVENT)
            {
                return M;
            }
            else
                return M;
        }
        int Valor_ANO(int evento)
        {
            if (( evento == CIMA) && (A <= 2100))
            {
                A = A + 1;
            }
            if ((evento == CIMA) && (A > 2100))
            {
                A = 2017;
            }
            if ((evento == BAIXO) && (A >= 2017))
            {
                A = A - 1;
            }
            if ((evento == BAIXO) && (A < 2017))
            {
                A = 2100;
            }
            if (evento == NO_EVENT)
            {
                return A;
            }
            else
                return A;
        }
        int DIA(void)
        {
            return D;
        }
        int MES(void)
        {
            return M;
        }
        int ANO(void)
        {
            return A;
        }
        int POT_inf (int evento)
        {
            if (( evento == CIMA) && (Valor_POT_Inf <= 99))
            {
                Valor_POT_Inf = Valor_POT_Inf + 1;
            }
            if ((evento == CIMA) && (Valor_POT_Inf > 99))
            {
                Valor_POT_Inf = 0;
            }
            if ((evento == BAIXO) && (Valor_POT_Inf >= 0))
            {
                Valor_POT_Inf = Valor_POT_Inf - 1;
            }
            if ((evento == BAIXO) && (Valor_POT_Inf < 0))
            {
                Valor_POT_Inf = 100;
            }
            if (evento == NO_EVENT)
            {
                return Valor_POT_Inf;
            }
            else
                return Valor_POT_Inf;
        }
        int POT_sup (int evento)
        {
            if (( evento == CIMA) && (Valor_POT_Sup <= 99))
            {
                Valor_POT_Sup = Valor_POT_Sup + 1;
            }
            if ((evento == CIMA) && (Valor_POT_Sup> 99))
            {
                Valor_POT_Sup = 0;
            }
            if ((evento == BAIXO) && (Valor_POT_Sup >= 0))
            {
                Valor_POT_Sup = Valor_POT_Sup - 1;
            }
            if ((evento == BAIXO) && (Valor_POT_Sup < 0))
            {
                Valor_POT_Sup = 100;
            }
            if (evento == NO_EVENT)
            {
                return Valor_POT_Sup;
            }
            else
                return Valor_POT_Sup;
        }
        int POT_supe(void)
        {
            return Valor_POT_Sup;
        }
        int POT_infe(void)
        {
            return Valor_POT_Inf;
        }
