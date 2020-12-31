#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char

#define RS_CLR RS=0 
#define RS_SET RS=1
#define RW_CLR RW=0 
#define RW_SET RW=1 
#define EN_CLR E=0
#define EN_SET E=1

sbit RW=P2^5;
sbit RS=P2^6;
sbit E=P2^7;

sbit RST=P2^0;
sbit SCLK=P2^1;
sbit DATA=P2^2;


sbit setting=P1^0;
sbit add=P1^1;
sbit sub=P1^2;
sbit ok=P1^3;
sbit set_classtime=P1^4;
sbit set_overtime=P1^5;

sbit BEEP=P3^0;

//液晶第一显示lcd_display
uchar display1[]="2020-01-01";
uchar display2[]="00:00:00";
uchar display3[]="0123456789";

uchar num,runmode,count_setting,count_classtime,count_overtime;

void lcd_write_com(uchar cmd);
void lcd_write_data(uchar dat);
void lcd_display();

void write_byte(uchar cmd);
void write_data(uchar cmd, uchar dat);

struct time{
    uchar year;
    uchar mon;
    uchar day;
    uchar hou;
    uchar min;
    uchar sec;
};

struct classtime{
    uchar hou;
    uchar min;
    uchar sec;
};

struct overtime{
    uchar hou;
    uchar min;
    uchar sec;
};

struct keystate{
	uchar ring_pushflag;
	uchar overring_pushflag;
    uchar setting_pushflag;
    uchar add_pushflag;
    uchar sub_pushflag;
    uchar ok_pushflag;
};

void delay_ms(uint x)
{
 	uint i,j;
	for(i=x;i>0;i--)
		for(j=110;j>0;j--);
}

void delay_ns(uchar n)
{
	uchar i;
	for(i=0;i<n;i++);
}


void timer_delay10us(){     /* Timer0 delay function */
	TMOD = 0x01;			/* M0=1 */
	TH0 = 0xFF;			    /* 高八11111111 */
	TL0 = 0xF6;			    /* 低八11110110 */
	TR0 = 1;				/* Start timer0 */
	while(TF0 == 0);		/* Wait until timer0 flag set */
	TR0 = 0;				/* Stop timer0 */
	TF0 = 0;				/* Clear timer0 flag */
}

void lcd_init()
{
	E=0;
	lcd_write_com(0x38);	
	lcd_write_com(0x0c);	
	lcd_write_com(0x06);	
	lcd_write_com(0x01);	
	lcd_write_com(0x80+0x03); 
    lcd_display();
}

void lcd_display(){
    for(num=0;num<10;num++)
	{
		lcd_write_data(display1[num]);
		delay_ms(5);
	}

	lcd_write_com(0x80+0x42); //初始化显示

	for(num=0;num<8;num++)
	{
		lcd_write_data(display2[num]);
		delay_ms(5);
	}
}

void lcd_write_com(uchar cmd){		
		RS_CLR;
		timer_delay10us();
		RW_CLR;
		timer_delay10us();
		P0=cmd;
		timer_delay10us();
		EN_SET;
		timer_delay10us();
		EN_CLR;
}

void lcd_write_data(uchar dat){
		RS_SET;
		timer_delay10us();
		RW_CLR;
		timer_delay10us();
		P0=dat;
		timer_delay10us();
		EN_SET;
		timer_delay10us();
		EN_CLR;
		timer_delay10us();
}


void ds_init(){
    RST=0;
    SCLK=0;
    write_data(0x8e,0x00);
    write_data(0x80,0x00);
}

uchar read_byte(){
    uchar i,dat;

    delay_ns(2);       //稍微等待，使硬件做好准备
	for(i=0;i<8;i++)   //连续读8个二进制位数据
	{
	    dat>>=1;       //将dat的各数据位右移1位，因为先读出的是字节的最低位
		if(DATA==1)    //如果读出的数据是1
		dat|=0x80;    //将1取出，写在dat的最高位
		SCLK=1;       //将SCLK置于高电平，为下降沿读出
		delay_ns(2);  //稍微等待
		SCLK=0;       //拉低SCLK，形成脉冲下降沿
		delay_ns(2);  //稍微等待
	}	 
    return dat;        //将读出的数据返回 
}

uchar read_data(uchar cmd){
  	uchar dat;

  	RST=0;                 //拉低RST
  	SCLK=0;                //确保写数居前SCLK被拉低
  	RST=1;                 //启动数据传输
  	write_byte(cmd);       //写入命令字
  	dat=read_byte();       //读出数据
  	SCLK=1;              //将时钟电平置于已知状态
  	RST=0;               //禁止数据传递

  	return dat;          //将读出的数据返回
}

void write_byte(uchar dat){
    uchar i;
	uchar Data;

    SCLK=0;
    delay_ns(2);

    for(i=0;i<8;i++){
        delay_ns(2);
        Data = dat & 0x01;
		SCLK=1;          
        delay_ns(2);
        SCLK=0;      
		dat>>=1;          
    }
}

void write_data(uchar cmd, uchar dat){
   	RST=0;          //禁止数据传递
   	SCLK=0;        //确保写数居前SCLK被拉低
	RST=1;           //启动数据传输
	delay_ns(2);     //稍微等待，使硬件做好准备
	write_byte(cmd);  //写入命令字
	write_byte(dat);  //写数据
	SCLK=1;          //将时钟电平置于已知状态
	RST=0;           //禁止数据传递
}

void time2lcd(uchar add, uchar dat){
	int i,j;
	i=dat/10+'0';
	j=dat%10+'0';
 	lcd_write_com(0x80+add);
	lcd_write_data(i);
	lcd_write_data(j);
	delay_ms(5);
}

uchar bcd2dec(uchar bcd)
{
 	uchar dec;
	dec=(bcd/16)*10+(bcd%16);
	return dec;
}

void keyscan(struct keystate k){
	
 	if(setting==0)
	{
	 	delay_ms(5);	 		//软件去抖
		if(setting==0)
		{
			while(!setting); 		//等待按键抬起
			runmode=0;			    //功能键被按下，进入万年历参数设置
			k.setting_pushflag=1;	// 功能键被按下标志位
			count_setting++;		    //功能键被按下的次数
			if(count_setting>6)
				count_setting=1;	
		}
	}

	if(set_classtime==0){
	 	delay_ms(5);	 		
		if(set_classtime==0)
		{
			while(!set_classtime); 		
			runmode=2;			   
			k.ring_pushflag=1;	
			count_classtime++;		    
			if(count_classtime>3)
				count_classtime=1;	
		}
	}

	if(set_overtime==0){
	 	delay_ms(5);	 		
		if(set_overtime==0)
		{
			while(!set_overtime); 		
			runmode=3;			   
			k.overring_pushflag=1;	
			count_overtime++;		    
			if(count_overtime>3)
				count_overtime=1;	
		}
	}

	if(k.ring_pushflag==1)
	{
		if(add==0)
	 	{	delay_ms(10);	 		//软件去抖
			if(add==0)
			{
				while(!add); 		//等待按键抬起
				k.add_pushflag=1;	
			}
		}
		if(sub==0)
	 	{	delay_ms(10);	 		//软件去抖
			if(sub==0)
			{
				while(!sub); 		//等待按键抬起
				k.sub_pushflag=1;	
			}
		}
		if(ok==0)
	 	{	delay_ms(10);	 		
			if(ok==0)
			{
				while(!ok); 		
				k.ring_pushflag=0;	
				k.ok_pushflag=1;	
			}
		}
   	}

	if(k.overring_pushflag==1)
	{
		if(add==0)
	 	{	delay_ms(10);	 		//软件去抖
			if(add==0)
			{
				while(!add); 		//等待按键抬起
				k.add_pushflag=1;	
			}
		}
		if(sub==0)
	 	{	delay_ms(10);	 		//软件去抖
			if(sub==0)
			{
				while(!sub); 		//等待按键抬起
				k.sub_pushflag=1;	
			}
		}
		if(ok==0)
	 	{	delay_ms(10);	 		
			if(ok==0)
			{
				while(!ok); 		
				k.ring_pushflag=0;	
				k.ok_pushflag=1;	
			}
		}
   	}

	if(k.setting_pushflag==1)
	{
		if(add==0)
	 	{	delay_ms(10);	 		//软件去抖
			if(add==0)
			{
				while(!add); 		//等待按键抬起
				k.add_pushflag=1;	
			}
		}
		if(sub==0)
	 	{	delay_ms(10);	 		//软件去抖
			if(sub==0)
			{
				while(!sub); 		//等待按键抬起
				k.sub_pushflag=1;	
			}
		}
		if(ok==0)
	 	{	delay_ms(10);	 		
			if(ok==0)
			{
				while(!ok); 		
				k.setting_pushflag=0;	
				k.ok_pushflag=1;	
			}
		}
   	}
}

void key_set_time(struct time t,struct keystate k){
    uchar tmp;

    switch(count_setting){
        case 1:
            lcd_write_com(0x80+0x05);
            lcd_write_com(0x0f);

            if(k.add_pushflag == 1){
                t.year ++;
                if(t.year >99){
                    t.year =0;
                }
                k.add_pushflag=0;
                time2lcd(0x05,t.year);
                lcd_write_com(0x80+0x05);
            }else if(k.sub_pushflag == 0){
				t.year--;

				if(t.year<0)
				{
					t.year=99;	
				}

				k.sub_pushflag=0;		
				time2lcd(0x05,t.year);
				lcd_write_com(0x80+0x05);
			}
			break;

        case 2:
			lcd_write_com(0x80+0x08);	
			lcd_write_com(0x0f);		
			if(k.add_pushflag==1)
			{
				t.mon++;
				if(t.mon>12)
				{
					t.mon=1;	
				}
				k.add_pushflag=0;		
				time2lcd(0x08,t.mon);
				lcd_write_com(0x80+0x08);	
			}
			else if(k.sub_pushflag==1)
			{
				t.mon--;
				if(t.mon<0)
				{
					t.mon=12;	
				}
				k.sub_pushflag=0;		
				time2lcd(0x08,t.mon);
				lcd_write_com(0x80+0x08);
			}
			break;

		case 3:						//功能键按下1次，处理年的数据
			lcd_write_com(0x80+0x0b);	//光标置于年的位置
			lcd_write_com(0x0f);		//光标闪烁
			if(k.add_pushflag==1)
			{
				t.day++;
				if(t.day>30)
				{
					t.day=1;	
				}
				k.add_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x0b,t.day);
				lcd_write_com(0x80+0x0b);	
			}
			else if(k.sub_pushflag==1)
			{
				t.day--;
				if(t.day<0)
				{
					t.day=30;	
				}
				k.sub_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0xb,t.day);
				lcd_write_com(0x80+0x0b);
			}
			break;

		case 4:						//功能键按下1次，处理年的数据
			lcd_write_com(0x80+0x42);	//光标置于年的位置
			lcd_write_com(0x0f);		//光标闪烁
			if(k.add_pushflag==1)
			{
				t.hou++;
				if(t.hou>23)
				{
					t.hou=0;	
				}
				k.add_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x42,t.hou);
				lcd_write_com(0x80+0x42);	
			}
			else if(k.sub_pushflag==1)
			{
				t.hou--;
				if(t.hou<0)
				{
					t.hou=23;	
				}
				k.sub_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x42,t.hou);
				lcd_write_com(0x80+0x42);
			}
			break;
		case 5:						//功能键按下1次，处理年的数据
			lcd_write_com(0x80+0x45);	//光标置于年的位置
			lcd_write_com(0x0f);		//光标闪烁
			if(k.add_pushflag==1)
			{
				t.min++;
				if(t.min>59)
				{
					t.min=0;	
				}
				k.add_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x45,t.min);
				lcd_write_com(0x80+0x45);	
			}
			else if(k.sub_pushflag==1)
			{
				t.min--;
				if(t.min<0)
				{
					t.min=59;	
				}
				k.sub_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x45,t.min);
				lcd_write_com(0x80+0x45);
			}
			break;
		case 6:						//功能键按下1次，处理年的数据
			lcd_write_com(0x80+0x48);	//光标置于年的位置
			lcd_write_com(0x0f);		//光标闪烁
			if(k.add_pushflag==1)
			{
				t.sec++;
				if(t.sec>59)
				{
					t.sec=0;	
				}
				k.add_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x48,t.sec);
				lcd_write_com(0x80+0x48);	
			}
			else if(k.sub_pushflag==1)
			{
				t.sec--;
				if(t.sec<0)
				{
					t.sec=59;	
				}
				k.sub_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x48,t.sec);
				lcd_write_com(0x80+0x48);
			}
			break;
    }

    if(k.ok_pushflag == 1){
		tmp=bcd2dec(t.sec);
		write_data(0x8e,0x00);
		write_data(0x80,tmp);

		tmp=bcd2dec(t.min);
		write_data(0x8e,0x00);
		write_data(0x82,tmp);

		tmp=bcd2dec(t.hou);
		write_data(0x8e,0x00);
		write_data(0x84,tmp);

		tmp=bcd2dec(t.day);
		write_data(0x8e,0x00);
		write_data(0x86,tmp);

		tmp=bcd2dec(t.mon);
		write_data(0x8e,0x00);
		write_data(0x88,tmp);
	
		tmp=bcd2dec(t.year);
		write_data(0x8e,0x00);
		write_data(0x8c,tmp);
		lcd_write_com(0x0c);
		k.ok_pushflag=0;
		runmode=1;
		delay_ms(10);	
    }

}

void key_set_classtime(struct classtime ct,struct keystate k){

	switch(count_classtime){
		case 1:						//功能键按下1次，处理年的数据
			lcd_write_com(0x80+0x42);	//光标置于年的位置
			lcd_write_com(0x0f);		//光标闪烁
			if(k.add_pushflag==1)
			{
				ct.hou++;
				if(ct.hou>23)
				{
					ct.hou=0;	
				}
				k.add_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x42,ct.hou);
				lcd_write_com(0x80+0x42);	
			}
			else if(k.sub_pushflag==1)
			{
				ct.hou--;
				if(ct.hou<0)
				{
					ct.hou=23;	
				}
				k.sub_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x42,ct.hou);
				lcd_write_com(0x80+0x42);
			}
			break;
		case 2:						//功能键按下1次，处理年的数据
			lcd_write_com(0x80+0x45);	//光标置于年的位置
			lcd_write_com(0x0f);		//光标闪烁
			if(k.add_pushflag==1)
			{
				ct.min++;
				if(ct.min>59)
				{
					ct.min=0;	
				}
				k.add_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x45,ct.min);
				lcd_write_com(0x80+0x45);	
			}
			else if(k.sub_pushflag==1)
			{
				ct.min--;
				if(ct.min<0)
				{
					ct.min=59;	
				}
				k.sub_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x45,ct.min);
				lcd_write_com(0x80+0x45);
			}
			break;
		case 3:						//功能键按下1次，处理年的数据
			lcd_write_com(0x80+0x48);	//光标置于年的位置
			lcd_write_com(0x0f);		//光标闪烁
			if(k.add_pushflag==1)
			{
				ct.sec++;
				if(ct.sec>59)
				{
					ct.sec=0;	
				}
				k.add_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x48,ct.sec);
				lcd_write_com(0x80+0x48);	
			}
			else if(k.sub_pushflag==1)
			{
				ct.sec--;
				if(ct.sec<0)
				{
					ct.sec=59;	
				}
				k.sub_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x48,ct.sec);
				lcd_write_com(0x80+0x48);
			}
			break;
    }
}

void key_set_overclass(struct overtime ot,struct keystate k){
	switch(count_overtime){
		case 1:						
			lcd_write_com(0x80+0x42);	
			lcd_write_com(0x0f);		
			if(k.add_pushflag==1)
			{
				ot.hou++;
				if(ot.hou>23)
				{
					ot.hou=0;	
				}
				k.add_pushflag=0;		
				time2lcd(0x42,ot.hou);
				lcd_write_com(0x80+0x42);	
			}
			else if(k.sub_pushflag==1)
			{
				ot.hou--;
				if(ot.hou<0)
				{
					ot.hou=23;	
				}
				k.sub_pushflag=0;		
				time2lcd(0x42,ot.hou);
				lcd_write_com(0x80+0x42);
			}
			break;
		case 2:						
			lcd_write_com(0x80+0x45);	
			lcd_write_com(0x0f);		
			if(k.add_pushflag==1)
			{
				ot.min++;
				if(ot.min>59)
				{
					ot.min=0;	
				}
				k.add_pushflag=0;		
				time2lcd(0x45,ot.min);
				lcd_write_com(0x80+0x45);	
			}
			else if(k.sub_pushflag==1)
			{
				ot.min--;
				if(ot.min<0)
				{
					ot.min=59;	
				}
				k.sub_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x45,ot.min);
				lcd_write_com(0x80+0x45);
			}
			break;
		case 3:						//功能键按下1次，处理年的数据
			lcd_write_com(0x80+0x48);	//光标置于年的位置
			lcd_write_com(0x0f);		//光标闪烁
			if(k.add_pushflag==1)
			{
				ot.sec++;
				if(ot.sec>59)
				{
					ot.sec=0;	
				}
				k.add_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x48,ot.sec);
				lcd_write_com(0x80+0x48);	
			}
			else if(k.sub_pushflag==1)
			{
				ot.sec--;
				if(ot.sec<0)
				{
					ot.sec=59;	
				}
				k.sub_pushflag=0;		//清楚标志，防止按1次该键，数值一直增加
				time2lcd(0x48,ot.sec);
				lcd_write_com(0x80+0x48);
			}
			break;
    }
}

void beep(unsigned int time)
{
	unsigned int i;

	for(i=0;i<1;i++){
		BEEP=~BEEP;		  
		delay_ms(2000);
	}


	for(i=0;i<time;i++)
	{
		 BEEP=~BEEP;		  
		 delay_ms(500);	
	}
}

void longbeep(unsigned int time)
{
	unsigned int i;
	for(i=0;i<time;i++)
	{
		 BEEP=~BEEP;		  
		 delay_ms(3000);	
	}
}

void main()
{
	struct time t; 
	struct keystate k;
	struct classtime ct;
	struct overtime ot;

	runmode=1;

 	lcd_init();
	ds_init();

	while(1)
	{	
		keyscan(k);
		if(runmode==1)
		{	
			t.sec=bcd2dec(read_data(0x81));
			t.min=bcd2dec(read_data(0x83));
			t.hou=bcd2dec(read_data(0x85));
			t.day=bcd2dec(read_data(0x87));
			t.mon=bcd2dec(read_data(0x89));
			t.year=bcd2dec(read_data(0x8d));


			lcd_write_com(0x0c);
			time2lcd(0x48,t.sec);
			time2lcd(0x45,t.min);
			time2lcd(0x42,t.hou);
			time2lcd(0x0b,t.day);
			time2lcd(0x08,t.mon);
			time2lcd(0x05,t.year);
		}else if(runmode==2){
			key_set_classtime(ct,k);
		}else if(runmode==3){
			key_set_overclass(ot,k);
		}
		else{
			key_set_time(t,k);
		}

		//class time
		if(t.year==ct.hou&&t.year==ct.min&&t.year==ct.sec){
			beep(6);//1长3短   1 on 1 stop，6 times
		}

		//over class time
		if(t.year==ot.hou&&t.year==ot.min&&t.year==ot.sec){
			longbeep(6);//longbeep, 1 on 1 stop，6 times
		}
	}
}