#ifndef __OLED_H
#define __OLED_H 

#include "stm32f3xx_hal.h"	

//-----------------����LED�˿ڶ���---------------- 

#define LED_ON HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12, GPIO_PIN_RESET)
#define LED_OFF HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12, GPIO_PIN_SET)

//-----------------OLED�˿ڶ���---------------- 

#define OLED_SCL_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_RESET)//SCL
#define OLED_SCL_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_SET)

#define OLED_SDA_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7, GPIO_PIN_RESET)//SDA
#define OLED_SDA_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7, GPIO_PIN_SET)

#define OLED_RES_Clr() HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2, GPIO_PIN_RESET)//RES
#define OLED_RES_Set() HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2, GPIO_PIN_SET)

#define OLED_DC_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET)//DC
#define OLED_DC_Set() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_SET)
 
#define OLED_CS_Clr()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4, GPIO_PIN_RESET)//CS
#define OLED_CS_Set()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4, GPIO_PIN_SET)



#define OLED_BUSY()    HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long int


#define OLED_W   128
#define OLED_H   296


typedef struct {
    u8 *Image;
    u16 Width;
    u16 Height;
    u16 WidthMemory;
    u16 HeightMemory;
    u16 Color;
    u16 Rotate;
    u16 WidthByte;
    u16 HeightByte;
} PAINT;
extern PAINT Paint;

#define ROTATE_0            0   //��Ļ������ʾ
#define ROTATE_90           90  //��Ļ��ת90����ʾ
#define ROTATE_180          180 //��Ļ��ת180����ʾ
#define ROTATE_270          270 //��Ļ��ת270����ʾ


#define WHITE          0xFF   //��ʾ��ɫ
#define BLACK          0x00   //��ʾ��ɫ

void OLED_GPIOInit(void);   //��ʼ��GPIO
void OLED_WR_Bus(u8 dat);   //ģ��SPIʱ��
void OLED_WR_REG(u8 reg);   //д��һ������
void OLED_WR_DATA8(u8 dat); //д��һ���ֽ�
void OLED_AddressSet(u16 xs,u16 ys,u16 xe,u16 ye);  //����λ�ú���
void OLED_Init(void);       //��ʼ����Ļ

void Epaper_READBUSY(void); 
void EPD_Update(void);      

void Paint_NewImage(u8 *image,u16 Width,u16 Height,u16 Rotate,u16 Color); 					 //��������������ʾ����
void OLED_Clear(u16 Color);																													 //��������
void OLED_DrawPoint(u16 Xpoint,u16 Ypoint,u16 Color);                                //����
void OLED_DrawLine(u16 Xstart,u16 Ystart,u16 Xend,u16 Yend,u16 Color);               //����
void OLED_DrawRectangle(u16 Xstart,u16 Ystart,u16 Xend,u16 Yend,u16 Color,u8 mode);  //������
void OLED_DrawCircle(u16 X_Center,u16 Y_Center,u16 Radius,u16 Color,u8 mode);        //��Բ
void OLED_ShowChar(u16 x,u16 y,u16 chr,u16 size1,u16 color);                         //��ʾ�ַ�
void OLED_ShowString(u16 x,u16 y,u8 *chr,u16 size1,u16 color);                       //��ʾ�ַ���
void OLED_ShowNum(u16 x,u16 y,u32 num,u16 len,u16 size1,u16 color);                  //��ʾ����
void OLED_ShowChinese(u16 x,u16 y,u16 num,u16 size1,u16 color);                      //��ʾ����
void OLED_ShowPicture(u16 x,u16 y,u16 sizex,u16 sizey,const u8 BMP[],u16 color);      //��ʾͼƬ
void OLED_Display(unsigned char *Image);																		 				 //���µ���Ļ
void OLED_GUIInit(void);																														 //��ĻGUI��ʼ��


#endif


