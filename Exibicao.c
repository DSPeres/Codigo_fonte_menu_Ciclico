#include <LPC11xx.h>
#include "system_LPC11xx.h"
#include "Driver_LCD.h"
#include "Exibicao.h"
#include "Estados.h"
#include "Config.h"
#include "adc.h"


void AtualizaDisplay(int estado)
{
    unsigned int tmp_var;
    switch (estado)
    {
    case INICIO:
    {
        LCD_comando(0x80);
        lcdString("   Bem Vindo!   ");
        LCD_comando(0xC0);
        lcdString("                ");
    }
    break;
    case SENHA1:
    {
        LCD_comando(0x80);
        lcdString("Digite a senha: ");
        LCD_comando(0xC0);
        lcdString("      ");
        tmp_var = SENHA();
        LCD_number4(tmp_var);
        lcdString("      ");
    }
    break;
    case SENHA2:
    {
        LCD_comando(0x80);
        lcdString("Digite a senha: ");
        LCD_comando(0xC0);
        lcdString("      ");
        tmp_var = SENHA();
        LCD_number4(tmp_var);
        lcdString("      ");
    }
    break;
    case SENHA3:
    {
        LCD_comando(0x80);
        lcdString("Digite a senha: ");
        LCD_comando(0xC0);
        lcdString("      ");
        tmp_var = SENHA();
        LCD_number4(tmp_var);
        lcdString("      ");
    }
    break;
    case SENHA4:
    {
        LCD_comando(0x80);
        lcdString("Digite a senha: ");
        LCD_comando(0xC0);
        lcdString("      ");
        tmp_var = SENHA();
        LCD_number4(tmp_var);
        lcdString("      ");
    }
    break;
    case SENHA_ERRADA:
    {
        LCD_comando(0x80);
        lcdString("  SENHA ERRADA  ");
        LCD_comando(0xC0);
        lcdString("                ");
    }
    break;
    case LEITURAS1:
    {
        tmp_var = DIA();
        LCD_comando(0x80);
        lcdString("   ");
        LCD_number2(tmp_var);
        lcdString("/");
        tmp_var = MES();
        LCD_number2(tmp_var);
        lcdString("/");
        tmp_var = ANO();
        LCD_number4(tmp_var);
        lcdString("   ");
        LCD_comando(0xC0);
        tmp_var = Ler_LDR();
        lcdString("  LUMINO: 070%  ");
    }
    break;
    case LEITURAS2:
    {
        tmp_var = DIA();
        LCD_comando(0x80);
        lcdString("   ");
        LCD_number2(tmp_var);
        lcdString("/");
        tmp_var = MES();
        LCD_number2(tmp_var);
        lcdString("/");
        tmp_var = ANO();
        LCD_number4(tmp_var);
        lcdString("   ");
        LCD_comando(0xC0);
        tmp_var = Ler_Pot();
        lcdString("  POTENC: 030%  ");
    }
    break;
    case ALARME:
    {
        LCD_comando(0x80);
        lcdString("     OUTRAS     ");
        LCD_comando(0xC0);
        lcdString("  CONFIGURACOES  ");
    }
    break;
    case ALARME_ALTO:
    {
        LCD_comando(0x80);
        lcdString("Altura -> Alto  ");
        LCD_comando(0xC0);
        lcdString("          Baixo ");
    }
    break;
    case ALARME_BAIXO:
    {
        LCD_comando(0x80);
        lcdString("Altura -> Baixo ");
        LCD_comando(0xC0);
        lcdString("          Alto  ");
    }
    break;
    case Freq_ATualizacao_100:
    {
        LCD_comando(0x80);
        lcdString("     Tempo:     ");
        LCD_comando(0xC0);
        lcdString(" 0,10  segundos ");
    }
    break;
    case Freq_ATualizacao_150:
    {
        LCD_comando(0x80);
        lcdString("     Tempo:     ");
        LCD_comando(0xC0);
        lcdString(" 0,15  segundos ");
    }
    break;
    case Freq_ATualizacao_200:
    {
        LCD_comando(0x80);
        lcdString("     Tempo:     ");
        LCD_comando(0xC0);
        lcdString(" 0,20  segundos ");
    }
    break;
    case LDR:
    {
        LCD_comando(0x80);
        lcdString("   ALARME DE    ");
        LCD_comando(0xC0);
        lcdString("  LUMINOSIDADE  ");
    }
    break;
    case LDR_Desliga:
    {
        LCD_comando(0x80);
        lcdString("Alarme Luminosid");
        LCD_comando(0xC0);
        lcdString("   >Desligado    ");
    }
    break;
    case LDR_Liga:
    {
        LCD_comando(0x80);
        lcdString("Alarme Luminosid");
        LCD_comando(0xC0);
        lcdString("    >Ligado     ");
    }
    break;
    case CONF_LDR_INF:
    {
        tmp_var = LDR_infe();
        LCD_comando(0x80);
        lcdString("Nivel inferior: ");
        LCD_comando(0xC0);
        lcdString("  LUMINO: ");
        LCD_number3(tmp_var);
        lcdString("%  ");
    }
    break;
    case CONF_LDR_SUP:
    {
        tmp_var = LDR_supe();
        LCD_comando(0x80);
        lcdString("Nivel superior: ");
        LCD_comando(0xC0);
        lcdString("  LUMINO: ");
        LCD_number3(tmp_var);
        lcdString("%  ");
    }
    break;
    case POT:
    {
        LCD_comando(0x80);
        lcdString("   ALARME DO    ");
        LCD_comando(0xC0);
        lcdString("  POTENCIOMETRO ");
    }
    break;
    case POT_Desliga:
    {
        LCD_comando(0x80);
        lcdString("Alarme Potenciom");
        LCD_comando(0xC0);
        lcdString("   >Desligado    ");
    }
    break;
    case POT_Liga:
    {
        LCD_comando(0x80);
        lcdString("Alarme Potenciom");
        LCD_comando(0xC0);
        lcdString("    >Ligado     ");
    }
    break;
    case CONF_POT_INF:
    {
        tmp_var = POT_infe();
        LCD_comando(0x80);
        lcdString("Nivel inferior: ");
        LCD_comando(0xC0);
        lcdString("  POTENC: ");
        LCD_number3(tmp_var);
        lcdString("%  ");
    }
    break;
    case CONF_POT_SUP:
    {
        tmp_var = POT_supe();
        LCD_comando(0x80);
        lcdString("Nivel superior: ");
        LCD_comando(0xC0);
        lcdString("  POTENC: ");
        LCD_number3(tmp_var);
        lcdString("%  ");
    }
    break;
    case CONFIGURAR_DATA:
    {
        LCD_comando(0x80);
        lcdString("CONFIGURACAO DA ");
        LCD_comando(0xC0);
        lcdString("      DATA      ");
    }
    break;
    case CONF_DIA:
    {
        LCD_comando(0x80);
        lcdString("CONFIGURE O DIA ");
        tmp_var = DIA();
        LCD_comando(0xC0);
        lcdString("   ");
        LCD_number2(tmp_var);
        lcdString("/");
        tmp_var = MES();
        LCD_number2(tmp_var);
        lcdString("/");
        tmp_var = ANO();
        LCD_number4(tmp_var);
        lcdString("   ");
    }
    break;
    case CONF_MES:
    {
        LCD_comando(0x80);
        lcdString("CONFIGURE O MES ");
        tmp_var = DIA();
        LCD_comando(0xC0);
        lcdString("   ");
        LCD_number2(tmp_var);
        lcdString("/");
        tmp_var = MES();
        LCD_number2(tmp_var);
        lcdString("/");
        tmp_var = ANO();
        LCD_number4(tmp_var);
        lcdString("   ");
    }
    break;
    case CONF_ANO:
    {
        LCD_comando(0x80);
        lcdString("CONFIGURE O ANO ");
        tmp_var = DIA();
        LCD_comando(0xC0);
        lcdString("   ");
        LCD_number2(tmp_var);
        lcdString("/");
        tmp_var = MES();
        LCD_number2(tmp_var);
        lcdString("/");
        tmp_var = ANO();
        LCD_number4(tmp_var);
        lcdString("   ");
    }
    break;
    case ESTADO_ALARME_LDR:
    {
        tmp_var = LDR_infe();
        LCD_comando(0x80);
        lcdString("ALARME LUMIN!   ");
        LCD_comando(0xC0);
        LCD_number3(tmp_var);
        LCD_caractere('<');
        LCD_number3(Ler_LDR());
        LCD_caractere('<');
        tmp_var = LDR_supe();
        LCD_number3(tmp_var);
        lcdString("      ");
    }
    break;
    case ESTADO_ALARME_POT:
    {
        tmp_var = POT_infe();
        LCD_comando(0x80);
        lcdString("ALARME POTENC!  ");
        LCD_comando(0xC0);
        LCD_number3(tmp_var);
        LCD_caractere('<');
        LCD_number3(Ler_Pot());
        LCD_caractere('<');
        tmp_var = POT_supe();
        LCD_number3(tmp_var);
        lcdString("      ");
    }
    break;
    case LDR_FINALIZADO:
    {
        LCD_comando(0x80);
        lcdString("  CONFIGURACAO  ");
        LCD_comando(0xC0);
        lcdString("   FINALIZADA   ");
    }
    break;
    case POT_FINALIZADO:
    {
        LCD_comando(0x80);
        lcdString("  CONFIGURACAO  ");
        LCD_comando(0xC0);
        lcdString("   FINALIZADA   ");
    }
    break;
    case DATA_FINALIZADO:
    {
        LCD_comando(0x80);
        lcdString("  CONFIGURACAO  ");
        LCD_comando(0xC0);
        lcdString("   FINALIZADA   ");
    }
    break;
    case CONFI_LED:
    {
        LCD_comando(0x80);
        lcdString("CONFIGURACAO DO ");
        LCD_comando(0xC0);
        lcdString("  LED E BUZZER  ");
    }
    break;
    case FREQUENCIA_ATUALIZACAO:
    {
        LCD_comando(0x80);
        lcdString("    TEMPO DE    ");
        LCD_comando(0xC0);
        lcdString("  ATUALIZACAO   ");
    }
    break;
    case FREQ_FINALIZADO:
    {
        LCD_comando(0x80);
        lcdString("  CONFIGURACAO  ");
        LCD_comando(0xC0);
        lcdString("   FINALIZADA   ");
    }
    break;
    case LED_FINALIZADO:
    {
        LCD_comando(0x80);
        lcdString("  CONFIGURACAO  ");
        LCD_comando(0xC0);
        lcdString("   FINALIZADA   ");
    }
    break;
    default:
        break;
    }
}
