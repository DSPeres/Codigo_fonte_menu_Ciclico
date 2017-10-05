#include "Estados.h"
#include "Exibicao.h"
#include "Lerevento.h"
#include "Driver_Teclado.h"
#include "Driver_LCD.h"
#include "Funcoes_operacionais.h"
#include "Config.h"
#include "Timer.h"

int ev, Nivel = Alto, LDR_ = 1, POT_ = 1, fr = 150;
unsigned int tmp_var;
int main(void)
{
    Estados_enum estado;
    Inicializa_Teclado();
    LCD_iniciar();
    Liga_Desliga_Alarme_LDR(Alarme_LDR_Desligado);
    Liga_Desliga_Alarme_POT(Alarme_POT_Desligado);
    estado = INICIO;
    Config_Freq_Atualizacao(150);
    InicializaTimer();
    for (;;)
    {
        ResetaTimer(tempo());
        AtualizaDisplay(estado);
        ev = Lerevento();
        //Verificar_Alarme();
        if ((ev == ALARME_LDR) && (estado != CONF_LDR_INF) && (estado != CONF_LDR_SUP) && (estado != LDR_Desliga) && (estado != LDR_Liga))
        {
            estado = ESTADO_ALARME_LDR;
        }
        if ((ev == ALARME_POT) && (estado != CONF_POT_INF) && (estado != CONF_POT_SUP) && (estado != POT_Desliga) && (estado != POT_Liga))
        {
            estado = ESTADO_ALARME_POT;
        }
        switch (estado)
        {
        case INICIO:
            delay_ms(2000);
            estado = SENHA1;
            break;
        case SENHA1:
            Valor_SENHA1(ev);
            tmp_var = SENHA();
            if (ev == ESQUERDA)
                estado = SENHA4;
            if (ev == DIREITA)
                estado = SENHA2;
            if ((ev == ENTER) && (tmp_var == 2121))
                estado = LEITURAS1;
            if ((ev == ENTER) && (tmp_var != 2121))
                estado = SENHA_ERRADA;
            break;
        case SENHA2:
            Valor_SENHA2(ev);
            tmp_var = SENHA();
            if (ev == ESQUERDA)
                estado = SENHA1;
            if (ev == DIREITA)
                estado = SENHA3;
            if ((ev == ENTER) && (tmp_var == 2121))
                estado = LEITURAS1;
            if ((ev == ENTER) && (tmp_var != 2121))
                estado = SENHA_ERRADA;
            break;
        case SENHA3:
            Valor_SENHA3(ev);
            tmp_var = SENHA();
            if (ev == ESQUERDA)
                estado = SENHA2;
            if (ev == DIREITA)
                estado = SENHA4;
            if ((ev == ENTER) && (tmp_var == 2121))
                estado = LEITURAS1;
            if ((ev == ENTER) && (tmp_var != 2121))
                estado = SENHA_ERRADA;
            break;
        case SENHA4:
            Valor_SENHA4(ev);
            tmp_var = SENHA();
            if (ev == ESQUERDA)
                estado = SENHA3;
            if (ev == DIREITA)
                estado = SENHA1;
            if ((ev == ENTER) && (tmp_var == 2121))
                estado = LEITURAS1;
            if ((ev == ENTER) && (tmp_var != 2121))
                estado = SENHA_ERRADA;
            break;
        case SENHA_ERRADA:
            delay_ms(2000);
            estado = SENHA1;
            break;
        case LEITURAS1:
            if (ev == ESQUERDA)
                estado = FREQUENCIA_ATUALIZACAO;
            if (ev == DIREITA)
                estado = CONFIGURAR_DATA;
            if (ev == ENTER)
                estado = LEITURAS2;
            break;
        case LEITURAS2:
            if (ev == ESQUERDA)
                estado = FREQUENCIA_ATUALIZACAO;
            if (ev == DIREITA)
                estado = CONFIGURAR_DATA;
            if (ev == ENTER)
                estado = LEITURAS1;
            break;
        case ALARME_ALTO:
            Nivel = Alto;
            Alarme(Nivel);
            if (ev == ENTER)
                estado = LED_FINALIZADO;
            if ((ev == CIMA) || (ev == BAIXO))
                estado = ALARME_BAIXO;
            break;
        case ALARME_BAIXO:
            Nivel = Baixo;
            Alarme(Nivel);
            if (ev == ENTER)
                estado = LED_FINALIZADO;
            if ((ev == CIMA) || (ev == BAIXO))
                estado = ALARME_ALTO;
            break;
        case Freq_ATualizacao_100:
            fr = 100;
            Desliga_LED_BUZZER();
            Config_Freq_Atualizacao(100);
            if (ev == CIMA)
                estado = Freq_ATualizacao_150;
            if (ev == BAIXO)
                estado = Freq_ATualizacao_200;
            if (ev == ENTER)
                estado = FREQ_FINALIZADO;
            break;
        case Freq_ATualizacao_150:
            fr = 150;
            Desliga_LED_BUZZER();
            Config_Freq_Atualizacao(150);
            if (ev == CIMA)
                estado = Freq_ATualizacao_200;
            if (ev == BAIXO)
                estado = Freq_ATualizacao_100;
            if (ev == ENTER)
                estado = FREQ_FINALIZADO;
            break;
        case Freq_ATualizacao_200:
            fr = 200;
            Desliga_LED_BUZZER();
            Config_Freq_Atualizacao(200);
            if (ev == CIMA)
                estado = Freq_ATualizacao_100;
            if (ev == BAIXO)
                estado = Freq_ATualizacao_150;
            if (ev == ENTER)
                estado = FREQ_FINALIZADO;
            break;
        case LDR:
            if ((ev == ENTER) && (LDR_ == 0))
                estado = LDR_Liga;
            if ((ev == ENTER) && (LDR_ == 1))
                estado = LDR_Desliga;
            if (ev == ESQUERDA)
                estado = POT;
            if (ev == DIREITA)
                estado = CONFI_LED;
            break;
        case LDR_Desliga:
            LDR_ = 1;
            Desliga_LED_BUZZER();
            Liga_Desliga_Alarme_LDR(Alarme_LDR_Desligado);
            if ((ev == CIMA) || (ev == BAIXO))
                estado = LDR_Liga;
            if (ev == ENTER)
                estado = LDR_FINALIZADO;
            break;
        case LDR_Liga:
            LDR_ = 0;
            Liga_Desliga_Alarme_LDR(Alarme_LDR_Ligado);
            if ((ev == DIREITA) || (ev == ENTER))
                estado = CONF_LDR_INF;
            if ((ev == CIMA) || (ev == BAIXO))
                estado = LDR_Desliga;
            break;
        case CONF_LDR_SUP:
            LDR_sup(ev);
            if (ev == ESQUERDA)
                estado = CONF_LDR_INF;
            if (ev == ENTER)
                estado = LDR_FINALIZADO;
            break;
        case CONF_LDR_INF:
            LDR_inf(ev);
            if ((ev == DIREITA) || (ev == ENTER))
                estado = CONF_LDR_SUP;
            if ((ev == ESQUERDA) && (LDR_ == 0))
                estado = LDR_Liga;
            if ((ev == ESQUERDA) && (LDR_ == 1))
                estado = LDR_Desliga;
            break;
        case POT:
            if ((ev == ENTER) && (POT_ == 0))
                estado = POT_Liga;
            if ((ev == ENTER) && (POT_ == 1))
                estado = POT_Desliga;
            if (ev == DIREITA)
                estado = LDR;
            if (ev == ESQUERDA)
                estado = CONFIGURAR_DATA;
            break;
        case POT_Desliga:
            POT_ = 1;
            Desliga_LED_BUZZER();
            Liga_Desliga_Alarme_POT(Alarme_POT_Desligado);
            if ((ev == CIMA) || (ev == BAIXO))
                estado = POT_Liga;
            if (ev == ENTER)
                estado = POT_FINALIZADO;
            break;
        case POT_Liga:
            POT_ = 0;
            Liga_Desliga_Alarme_POT(Alarme_POT_Ligado);
            if ((ev == DIREITA) || (ev == ENTER))
                estado = CONF_POT_INF;
            if ((ev == CIMA) || (ev == BAIXO))
                estado = POT_Desliga;
            break;
        case CONF_POT_SUP:
            POT_sup(ev);
            if (ev == ESQUERDA)
                estado = CONF_POT_INF;
            if (ev == ENTER)
                estado = POT_FINALIZADO;
            break;
        case CONF_POT_INF:
            POT_inf(ev);
            if ((ev == DIREITA) || (ev == ENTER))
                estado = CONF_POT_SUP;
            if ((ev == ESQUERDA) && (POT_ == 0))
                estado = POT_Liga;
            if ((ev == ESQUERDA) && (POT_ == 1))
                estado = POT_Desliga;
            break;
        case CONFIGURAR_DATA:
            if  (ev == DIREITA)
                estado = POT;
            if (ev == ESQUERDA)
                estado = LEITURAS1;
            if (ev == ENTER)
                estado = CONF_DIA;
            break;
        case CONF_DIA:
            Valor_DIA(ev);
            if (ev == ESQUERDA)
                estado = CONF_ANO;
            if (ev == DIREITA)
                estado = CONF_MES;
            if (ev == ENTER)
                estado = DATA_FINALIZADO;
            break;
        case CONF_MES:
            Valor_MES(ev);
            if (ev == ESQUERDA)
                estado = CONF_DIA;
            if (ev == DIREITA)
                estado = CONF_ANO;
            if (ev == ENTER)
                estado = DATA_FINALIZADO;
            break;
        case CONF_ANO:
            Valor_ANO(ev);
            if (ev == ESQUERDA)
                estado = CONF_MES;
            if (ev == DIREITA)
                estado = CONF_DIA;
            if (ev == ENTER)
                estado = DATA_FINALIZADO;
            break;
        case ESTADO_ALARME_LDR:
            Alarme(Nivel);
            if (ev == ENTER)
                estado = LDR_Desliga;
            break;
        case ESTADO_ALARME_POT:
            Alarme(Nivel);
            if (ev == ENTER)
                estado = POT_Desliga;
            break;
        case LDR_FINALIZADO:
            delay_ms(2000);
            estado = LDR;
            break;
        case POT_FINALIZADO:
            delay_ms(2000);
            estado = POT;
            break;
        case DATA_FINALIZADO:
            delay_ms(2000);
            estado = CONFIGURAR_DATA;
            break;
        case LED_FINALIZADO:
            Desliga_LED_BUZZER();
            delay_ms(2000);
            estado = CONFI_LED;
            break;
        case FREQ_FINALIZADO:
            delay_ms(2000);
            estado = FREQUENCIA_ATUALIZACAO;
            break;
        case FREQUENCIA_ATUALIZACAO:
            if ((ev == ENTER) && (fr == 100))
                estado = Freq_ATualizacao_100;
            if ((ev == ENTER) && (fr == 150))
                estado = Freq_ATualizacao_150;
            if ((ev == ENTER) && (fr == 200))
                estado = Freq_ATualizacao_200;
            if (ev == ESQUERDA)
                estado = CONFI_LED;
            if (ev == DIREITA)
                estado = LEITURAS1;
            break;
        case CONFI_LED:
            if ((ev == ENTER) && (Nivel == Alto))
                estado = ALARME_ALTO;
            if ((ev == ENTER) && (Nivel == Baixo))
                estado = ALARME_BAIXO;
            if (ev == ESQUERDA)
                estado = LDR;
            if (ev == DIREITA)
                estado = FREQUENCIA_ATUALIZACAO;
        default:
            break;
        }
        AguardaTimer();
    }
}
