//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2018-10-31
//  ����޸�   : 
//  ��������   : 
//              ˵��: 
//              ----------------------------------------------------------------
//              GND  ��Դ��
//              VCC  3.3v��Դ
//              D0   PA0��SCL��
//              D1   PA1��SDA��
//              RES  PA2
//              DC   PA3
//              CS   PA4 
//							BUSY PA5
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2018-10-31
//All rights reserved
//******************************************************************************/
#include "bmp.h"
#include "oled.h"
#include "delay.h"
#include "usart.h"

u8  Image_BW[4736];

//��Ļд������0ʱΪ��ɫ д������1ʱΪ��ɫ
//�ڰ׵���ֽ��Ļ֧�־ֲ�ˢ��;���Ǿֲ�ˢ����Ч�������ã����׳��ֲ�Ӱ;������ʹ��
int main()
{
	u8 t=' ';
  delay_init();
	OLED_GUIInit();
  Paint_NewImage(Image_BW,OLED_W,OLED_H,0,WHITE); 
  OLED_Clear(WHITE);	
	while(1)
	{
	  OLED_GUIInit();
		OLED_ShowPicture(0,0,296,128,gImage_1,BLACK);	
		OLED_Display(Image_BW);
		delay_ms(1000);		
		delay_ms(1000);		
		delay_ms(1000);
		OLED_Clear(WHITE);	
		OLED_GUIInit();
    OLED_ShowChinese(61,0,0,16,BLACK);//��
		OLED_ShowChinese(77,0,1,16,BLACK);//��
		OLED_ShowChinese(93,0,2,16,BLACK);//԰
		OLED_ShowChinese(109,0,3,16,BLACK);//��
		OLED_ShowChinese(125,0,4,16,BLACK);//��
		OLED_ShowChinese(141,0,5,16,BLACK);//��
		OLED_ShowChinese(157,0,6,16,BLACK);//��
		OLED_ShowChinese(173,0,7,16,BLACK);//��
		OLED_ShowChinese(189,0,8,16,BLACK);//��
		OLED_ShowChinese(205,0,9,16,BLACK);//��
		OLED_ShowChinese(221,0,10,16,BLACK);//˾
		OLED_ShowString(108,20,"2014/05/01",16,BLACK);
		OLED_ShowString(80,40,"ASCII:",16,BLACK);  
		OLED_ShowString(157,40,"CODE:",16,BLACK);
		OLED_ShowChar(131,40,t,16,BLACK); 
		OLED_ShowNum(198,40,t,3,16,BLACK);
		t++;
		if(t>'~')t=' ';	
		OLED_ShowString(33,56,"Welcome to 2.90-inch E-paper",16,BLACK);		
		OLED_ShowString(49,73,"with 296 x 128 resolution",16,BLACK);	
    OLED_DrawLine(1,89,296,89,BLACK);		
		OLED_ShowString(53,90,"Zhongjingyuan Electronic",16,BLACK);
		OLED_ShowString(75,106,"Technology Co.,Ltd.",16,BLACK);		
		OLED_Display(Image_BW);
		delay_ms(1000);		
		delay_ms(1000);		
		delay_ms(1000);
		OLED_GUIInit();
    OLED_DrawRectangle(1,1,296,128,BLACK,0);
		OLED_Display(Image_BW);
		delay_ms(1000);		
		delay_ms(1000);		
		delay_ms(1000);
		OLED_Clear(WHITE);		
	}
}

