#ifndef _LCD_H
#define _LCD_H

#include "main.h"

//LCD��ַ�ṹ��
typedef struct
{
    volatile uint16_t LCD_REG;
    volatile uint16_t LCD_RAM;
} LCD_TypeDef;
//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A6��Ϊ��������������
//ע������ʱSTM32�ڲ�������һλ����! 111 1110=0X7E
#define LCD_BASE ((uint32_t)(0x6C000000 | 0x0000007E))
#define LCD ((LCD_TypeDef *)LCD_BASE)
//////////////////////////////////////////////////////////////////////////////////

//ɨ�跽����
#define L2R_U2D 0 //������,���ϵ���
#define L2R_D2U 1 //������,���µ���
#define R2L_U2D 2 //���ҵ���,���ϵ���
#define R2L_D2U 3 //���ҵ���,���µ���

#define U2D_L2R 4 //���ϵ���,������
#define U2D_R2L 5 //���ϵ���,���ҵ���
#define D2U_L2R 6 //���µ���,������
#define D2U_R2L 7 //���µ���,���ҵ���


void LCD_WRITE_CMD(uint16_t data);
void LCD_WRITE_DATA(uint16_t data);
uint16_t LCD_READ_DATA(void);

void LCD_Init(void);
void LCD_Clear(uint16_t Color);
void LCD_DrawLine();
#endif
