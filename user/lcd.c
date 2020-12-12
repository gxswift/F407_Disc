#include "lcd.h"

void LCD_WR_REG(uint16_t data)
{
	LCD->LCD_REG = data; //Ð´ÈëÒªÐ´µÄ¼Ä´æÆ÷ÐòºÅ
}

void LCD_WR_DATA(uint16_t data)
{
	LCD->LCD_RAM = data;
}
uint16_t LCD_RD_DATA(void)
{
	return LCD->LCD_RAM;
}
void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
	LCD->LCD_REG = LCD_Reg;		 //Ð´ÈëÒªÐ´µÄ¼Ä´æÆ÷ÐòºÅ
	LCD->LCD_RAM = LCD_RegValue; //Ð´ÈëÊý¾Ý
}

void LCD_Init(void)
{
	//------------------------------------
	uint8_t ID;
	LCD_WR_REG(0);
	LCD_WR_DATA(1);
	HAL_Delay(50);
	LCD_WR_REG(0);
	HAL_Delay(1);
	ID = LCD_RD_DATA();
	printf("ID = %x\r\n",ID);
	//------------------------------------
	LCD_WR_REG(0XF1);
	LCD_WR_DATA(0x36);
	LCD_WR_DATA(0x04);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x3C);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x8F);

	LCD_WR_REG(0XF2);
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0xA3);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0xB2);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0xFF);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0XF8);
	LCD_WR_DATA(0x21);
	LCD_WR_DATA(0x04);

	LCD_WR_REG(0XF9);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x08);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x44);
	LCD_WR_DATA(0x77);
	LCD_WR_DATA(0x38);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x13);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x0B);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0XE1);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x3B);
	LCD_WR_DATA(0x39);
	LCD_WR_DATA(0x0D);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x53);
	LCD_WR_DATA(0x43);
	LCD_WR_DATA(0x3D);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x04);
	LCD_WR_DATA(0x23);
	LCD_WR_DATA(0x1F);
	LCD_WR_DATA(0x0F);

	LCD_WR_REG(0x36);
	LCD_WR_DATA(0x08);

	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x55); // 8bit,16bit=0x55 18bit=0x66

	LCD_WR_REG(0XB1); // Frame rate 70Hz b0 11
	LCD_WR_DATA(0xB0);
	LCD_WR_DATA(0x11);

	LCD_WR_REG(0XB4);
	LCD_WR_DATA(0x02);

	LCD_WR_REG(0XB6);
	LCD_WR_DATA(0x00); //MCU:0x02  RGB:0x22
	LCD_WR_DATA(0x42); // rotate 180 degree 0x42
	LCD_WR_DATA(0x3B);

	LCD_WR_REG(0XB7);
	LCD_WR_DATA(0xC6);

	LCD_WR_REG(0XC0);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x05);

	LCD_WR_REG(0XC1);
	LCD_WR_DATA(0x41);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0XC2);
	LCD_WR_DATA(0x22);

	LCD_WR_REG(0XC5);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x31); // Adjust Flicker
	LCD_WR_DATA(0x80);

	LCD_WR_REG(0x11);
	HAL_Delay(120);
	LCD_WR_REG(0x29);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1); //µãÁÁ±³¹â
}

void LCD_SetWindow(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd)
{
	LCD_WR_REG(0x2A);
	LCD_WR_DATA(xStar >> 8);
	LCD_WR_DATA(0x00FF & xStar);
	LCD_WR_DATA(xEnd >> 8);
	LCD_WR_DATA(0x00FF & xEnd);

	LCD_WR_REG(0x2B);
	LCD_WR_DATA(yStar >> 8);
	LCD_WR_DATA(0x00FF & yStar);
	LCD_WR_DATA(yEnd >> 8);
	LCD_WR_DATA(0x00FF & yEnd);

	LCD_WR_REG(0x2C);
}

void LCD_Clear(uint16_t Color)
{
	uint32_t index = 0;

	LCD_SetWindow(0, 0, 320, 480);

	for (index = 0; index < 153600; index++)
	{
		LCD->LCD_RAM = Color;
	}
}

void LCD_DraWR()
{
	uint32_t index = 0;

	LCD_SetWindow(40, 40, 80, 80);

	for (index = 0; index < 153600; index++)
	{
		LCD->LCD_RAM = 0x1111;
	}
}
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
	LCD_SetWindow(x, y, x, y);
	LCD_WR_DATA(color);
}


void LCD_DrawLine()
{
	uint16_t i, j;
	LCD_DraWR();
	for (i = 0; i < 100; i++)
	{
		LCD_DrawPoint(50, i, 0xFF);
	}
	for (i = 0; i < 100; i++)
	{
		LCD_DrawPoint(i, 50, 0xF000);
	}

}
