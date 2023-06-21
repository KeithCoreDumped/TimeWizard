//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2018-0101
//  最近修改   : 
//  功能描述   : STM32L053C8T6开发板点亮显示屏实验
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   PA0（SCL）
//              D1   PA1（SDA）
//              RES  PA2
//              DC   PA3
//              CS   PA4 
//              BUSY PA5
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2018
#include "main.h"
#include "stm32l0xx_hal.h"
#include "oled.h"
#include "bmp.h"
u8  Image_BW[4796];
void SystemClock_Config(void);

int main(void)
{
	u8 t=' ';
	HAL_Init();
	SystemClock_Config();
	OLED_GUIInit();
  Paint_NewImage(Image_BW,OLED_W,OLED_H,0,WHITE); 
  OLED_Clear(WHITE);	
	while(1)
	{
	  OLED_GUIInit();
    OLED_ShowPicture(0,0,296,128,gImage_1,BLACK);	
		OLED_Display(Image_BW);
		HAL_Delay(1000);		
		HAL_Delay(1000);		
		HAL_Delay(1000);
		OLED_Clear(WHITE);	
		OLED_GUIInit();
	  OLED_ShowChinese(61,0,0,16,BLACK);//中
		OLED_ShowChinese(77,0,1,16,BLACK);//景
		OLED_ShowChinese(93,0,2,16,BLACK);//园
		OLED_ShowChinese(109,0,3,16,BLACK);//电
		OLED_ShowChinese(125,0,4,16,BLACK);//子
		OLED_ShowChinese(141,0,5,16,BLACK);//技
	  OLED_ShowChinese(157,0,6,16,BLACK);//术
		OLED_ShowChinese(173,0,7,16,BLACK);//有
		OLED_ShowChinese(189,0,8,16,BLACK);//限
		OLED_ShowChinese(205,0,9,16,BLACK);//公
		OLED_ShowChinese(221,0,10,16,BLACK);//司
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
		HAL_Delay(1000);		
		HAL_Delay(1000);		
		HAL_Delay(1000);
		OLED_GUIInit();
    OLED_DrawRectangle(1,1,296,128,BLACK,0);
		OLED_Display(Image_BW);
		HAL_Delay(1000);		
		HAL_Delay(1000);		
		HAL_Delay(1000);
		OLED_Clear(WHITE);	
	}
}



void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {

  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {

  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}
