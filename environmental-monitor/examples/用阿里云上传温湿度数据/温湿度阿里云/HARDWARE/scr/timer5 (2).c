#include "stm32f10x.h"  //包含需要的头文件
/*-------------------------------------------------*/
/*函数名：定时器5使能40s定时                        */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void TIM5_ENABLE_40S(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;            //定义一个设置定时器的变量
	NVIC_InitTypeDef NVIC_InitStructure;                          //定义一个设置中断的变量
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);               //设置中断向量分组：第2组 抢先优先级：0 1 2 3 子优先级：0 1 2 3		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);           //使能TIM5时钟
	TIM_DeInit(TIM5);                                             //定时器5寄存器恢复默认值	
	TIM_TimeBaseInitStructure.TIM_Period = 50000-1; 	          //设置自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=57600-1;               //设置定时器预分频数
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;     //1分频
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);            //设置TIM5
	
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);                    //清除溢出中断标志位
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);                      //使能TIM5溢出中断    
	TIM_Cmd(TIM5,ENABLE);                                         //开TIM5                          
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn;                 //设置TIM5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;       //抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;              //子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;                 //中断通道使能
	NVIC_Init(&NVIC_InitStructure);                               //设置中断
}
