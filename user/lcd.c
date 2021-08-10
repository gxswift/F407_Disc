#include "lcd.h"

void LCD_WRITE_CMD(uint16_t data)
{
	LCD->LCD_REG = data; //写入要写的寄存器序号
}

void LCD_WRITE_DATA(uint16_t data)
{
	LCD->LCD_RAM = data;
}
uint16_t LCD_READ_DATA(void)
{
	return LCD->LCD_RAM;
}

//0x548066
static uint32_t LCD_ReadID(void)
{
	uint16_t buf[4];

	LCD_WRITE_CMD(0x04);
	buf[0] = LCD_READ_DATA();		   // 第一个读取数据无效
	buf[1] = LCD_READ_DATA() & 0x00ff; // 只有低8位数据有效
	buf[2] = LCD_READ_DATA() & 0x00ff; // 只有低8位数据有效
	buf[3] = LCD_READ_DATA() & 0x00ff; // 只有低8位数据有效
	return (buf[1] << 16) + (buf[2] << 8) + buf[3];
}
//ILI9488
#if 1
void LCD_Init(void)
{
	//------------------------------------
	uint32_t ID;
	ID = LCD_ReadID();
	printf("ID = %x\r\n",ID);
	//------------------------------------
	LCD_WRITE_CMD(0XF1);
	LCD_WRITE_DATA(0x36);
	LCD_WRITE_DATA(0x04);
	LCD_WRITE_DATA(0x00);
	LCD_WRITE_DATA(0x3C);
	LCD_WRITE_DATA(0x0F);
	LCD_WRITE_DATA(0x8F);

	LCD_WRITE_CMD(0XF2);
	LCD_WRITE_DATA(0x18);
	LCD_WRITE_DATA(0xA3);
	LCD_WRITE_DATA(0x12);
	LCD_WRITE_DATA(0x02);
	LCD_WRITE_DATA(0xB2);
	LCD_WRITE_DATA(0x12);
	LCD_WRITE_DATA(0xFF);
	LCD_WRITE_DATA(0x10);
	LCD_WRITE_DATA(0x00);

	LCD_WRITE_CMD(0XF8);
	LCD_WRITE_DATA(0x21);
	LCD_WRITE_DATA(0x04);

	LCD_WRITE_CMD(0XF9);
	LCD_WRITE_DATA(0x00);
	LCD_WRITE_DATA(0x08);
/* PGAMCTRL (Positive Gamma Control) (E0h) */
	LCD_WRITE_CMD(0xE0);
	/*
	LCD_WRITE_DATA(0x07);
	LCD_WRITE_DATA(0x10);
	LCD_WRITE_DATA(0x0F);
	LCD_WRITE_DATA(0x0E);
	LCD_WRITE_DATA(0x11);
	LCD_WRITE_DATA(0x0A);
	LCD_WRITE_DATA(0x41);
	LCD_WRITE_DATA(0x77);
	LCD_WRITE_DATA(0x38);
	LCD_WRITE_DATA(0x08);
	LCD_WRITE_DATA(0x13);
	LCD_WRITE_DATA(0x05);
	LCD_WRITE_DATA(0x0B);
	LCD_WRITE_DATA(0x02);
	LCD_WRITE_DATA(0x0F);
	*/
	LCD_WRITE_DATA(0x0F);
	LCD_WRITE_DATA(0x36);
	LCD_WRITE_DATA(0x2E);
	LCD_WRITE_DATA(0x09);
	LCD_WRITE_DATA(0x0A);
	LCD_WRITE_DATA(0x04);
	LCD_WRITE_DATA(0x46);
	LCD_WRITE_DATA(0x66);
	LCD_WRITE_DATA(0x37);
	LCD_WRITE_DATA(0x06);
	LCD_WRITE_DATA(0x10);
	LCD_WRITE_DATA(0x04);
	LCD_WRITE_DATA(0x24);
	LCD_WRITE_DATA(0x20);
	LCD_WRITE_DATA(0x00);
/* NGAMCTRL (Negative Gamma Control) (E1h)  */
	LCD_WRITE_CMD(0XE1);
	LCD_WRITE_DATA(0x0F);
	LCD_WRITE_DATA(0x3B);
	LCD_WRITE_DATA(0x39);
	LCD_WRITE_DATA(0x0D);
	LCD_WRITE_DATA(0x0F);
	LCD_WRITE_DATA(0x05);
	LCD_WRITE_DATA(0x53);
	LCD_WRITE_DATA(0x43);
	LCD_WRITE_DATA(0x3D);
	LCD_WRITE_DATA(0x05);
	LCD_WRITE_DATA(0x0F);
	LCD_WRITE_DATA(0x04);
	LCD_WRITE_DATA(0x23);
	LCD_WRITE_DATA(0x1F);
	LCD_WRITE_DATA(0x0F);

	LCD_WRITE_CMD(0x36);
	LCD_WRITE_DATA(0x08);

	LCD_WRITE_CMD(0x3A);
	LCD_WRITE_DATA(0x55); // 8bit,16bit=0x55 18bit=0x66

	LCD_WRITE_CMD(0XB1); // Frame rate 70Hz b0 11
	LCD_WRITE_DATA(0xB0);
	LCD_WRITE_DATA(0x11);

	LCD_WRITE_CMD(0XB4);
	LCD_WRITE_DATA(0x02);

	LCD_WRITE_CMD(0XB6);
	LCD_WRITE_DATA(0x00); //MCU:0x02  RGB:0x22
	LCD_WRITE_DATA(0x42); // rotate 180 degree 0x42
	LCD_WRITE_DATA(0x3B);

	LCD_WRITE_CMD(0XB7);
	LCD_WRITE_DATA(0xC6);

	LCD_WRITE_CMD(0XC0);
	LCD_WRITE_DATA(0x05);
	LCD_WRITE_DATA(0x05);

	LCD_WRITE_CMD(0XC1);
	LCD_WRITE_DATA(0x41);
	LCD_WRITE_DATA(0x00);

	LCD_WRITE_CMD(0XC2);
	LCD_WRITE_DATA(0x22);

	LCD_WRITE_CMD(0XC5);
	LCD_WRITE_DATA(0x00);
	LCD_WRITE_DATA(0x31); // Adjust Flicker
	LCD_WRITE_DATA(0x80);

	LCD_WRITE_CMD(0x11);//Exit Sleep
	HAL_Delay(120);
	LCD_WRITE_CMD(0x29);//display on

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1); //点亮背光
}
#else
void LCD_Init(void)
{
	/* PGAMCTRL (Positive Gamma Control) (E0h) */
	LCD_WRITE_CMD(0xE0);
	LCD_WRITE_DATA(0x00);
	LCD_WRITE_DATA(0x07);
	LCD_WRITE_DATA(0x10);
	LCD_WRITE_DATA(0x09);
	LCD_WRITE_DATA(0x17);
	LCD_WRITE_DATA(0x0B);
	LCD_WRITE_DATA(0x41);
	LCD_WRITE_DATA(0x89);
	LCD_WRITE_DATA(0x4B);
	LCD_WRITE_DATA(0x0A);
	LCD_WRITE_DATA(0x0C);
	LCD_WRITE_DATA(0x0E);
	LCD_WRITE_DATA(0x18);
	LCD_WRITE_DATA(0x1B);
	LCD_WRITE_DATA(0x0F);

	/* NGAMCTRL (Negative Gamma Control) (E1h)  */
	LCD_WRITE_CMD(0XE1);
	LCD_WRITE_DATA(0x00);
	LCD_WRITE_DATA(0x17);
	LCD_WRITE_DATA(0x1A);
	LCD_WRITE_DATA(0x04);
	LCD_WRITE_DATA(0x0E);
	LCD_WRITE_DATA(0x06);
	LCD_WRITE_DATA(0x2F);
	LCD_WRITE_DATA(0x45);
	LCD_WRITE_DATA(0x43);
	LCD_WRITE_DATA(0x02);
	LCD_WRITE_DATA(0x0A);
	LCD_WRITE_DATA(0x09);
	LCD_WRITE_DATA(0x32);
	LCD_WRITE_DATA(0x36);
	LCD_WRITE_DATA(0x0F);

	/* Adjust Control 3 (F7h)  */
	LCD_WRITE_CMD(0XF7);
	LCD_WRITE_DATA(0xA9);
	LCD_WRITE_DATA(0x51);
	LCD_WRITE_DATA(0x2C);
	LCD_WRITE_DATA(0x82); /* DSI write DCS command, use loose packet RGB 666 */

	/* Power Control 1 (C0h)  */
	LCD_WRITE_CMD(0xC0);
	LCD_WRITE_DATA(0x11);
	LCD_WRITE_DATA(0x09);

	/* Power Control 2 (C1h) */
	LCD_WRITE_CMD(0xC1);
	LCD_WRITE_DATA(0x41);

	/* VCOM Control (C5h)  */
	LCD_WRITE_CMD(0XC5);
	LCD_WRITE_DATA(0x00);
	LCD_WRITE_DATA(0x0A);
	LCD_WRITE_DATA(0x80);

	/* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
	LCD_WRITE_CMD(0xB1);
	LCD_WRITE_DATA(0xB0);
	LCD_WRITE_DATA(0x11);

	/* Display Inversion Control (B4h) */
	LCD_WRITE_CMD(0xB4);
	LCD_WRITE_DATA(0x02);

	/* Display Function Control (B6h)  */
	LCD_WRITE_CMD(0xB6);
	LCD_WRITE_DATA(0x02);
	LCD_WRITE_DATA(0x22);

	/* Entry Mode Set (B7h)  */
	LCD_WRITE_CMD(0xB7);
	LCD_WRITE_DATA(0xc6);

	/* HS Lanes Control (BEh) */
	LCD_WRITE_CMD(0xBE);
	LCD_WRITE_DATA(0x00);
	LCD_WRITE_DATA(0x04);

	/* Set Image Function (E9h)  */
	LCD_WRITE_CMD(0xE9);
	LCD_WRITE_DATA(0x00);

	/* 设置屏幕方向和尺寸 */
	LCD_WRITE_CMD(0x36);
	LCD_WRITE_DATA(0x08);
	LCD_WRITE_CMD(0x2A);
	LCD_WRITE_DATA(0x00); /* x start */
	LCD_WRITE_DATA(0x00);
	LCD_WRITE_DATA(0x01); /* x end */
	LCD_WRITE_DATA(0x3F);

	LCD_WRITE_CMD(0x2B);
	LCD_WRITE_DATA(0x00); /* y start */
	LCD_WRITE_DATA(0x00);
	LCD_WRITE_DATA(0x01); /* y end */
	LCD_WRITE_DATA(0xdF);

	/* write gram start */
	LCD_WRITE_CMD(0x2C);

	/* Interface Pixel Format (3Ah) */
	LCD_WRITE_CMD(0x3A);
	LCD_WRITE_DATA(0x55); /* 0x55 : 16 bits/pixel  */

	/* Sleep Out (11h) */
	LCD_WRITE_CMD(0x11);
	HAL_Delay(120);
	/* Display On */
	LCD_WRITE_CMD(0x29);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1); //点亮背光
}

#endif
void LCD_SetWindow(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd)
{
	LCD_WRITE_CMD(0x2A);
	LCD_WRITE_DATA(xStar >> 8);
	LCD_WRITE_DATA(0x00FF & xStar);
	LCD_WRITE_DATA(xEnd >> 8);
	LCD_WRITE_DATA(0x00FF & xEnd);

	LCD_WRITE_CMD(0x2B);
	LCD_WRITE_DATA(yStar >> 8);
	LCD_WRITE_DATA(0x00FF & yStar);
	LCD_WRITE_DATA(yEnd >> 8);
	LCD_WRITE_DATA(0x00FF & yEnd);

	LCD_WRITE_CMD(0x2C);
}

void LCD_Clear(uint16_t Color)
{
	uint32_t index = 0;

	LCD_SetWindow(0, 0, 320, 480);

	for (index = 0; index < 320 * 480; index++)
	{
		LCD->LCD_RAM = Color;
	}
}

void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
	LCD_SetWindow(x, y, x, y);
	LCD_WRITE_DATA(color);
}

void LCD_Draw(uint16_t x1, uint16_t y1,uint16_t x2, uint16_t y2,uint16_t *data)
{
	LCD_SetWindow(x1, y1, x2, y2);
	for (size_t i = 0; i < (x2-x1)*(y2-y1); i++)
	{
		LCD_WRITE_DATA(*data++);
	}
	

}
void LCD_DraWR()
{
	uint32_t index = 0;

	LCD_SetWindow(40, 40, 80, 80);

	for (index = 0; index < 153600; index++)
	{
		LCD->LCD_RAM = 0x1180;
	}
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
