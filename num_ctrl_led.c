void num_ctrl_led()
{
	int n; //ÊäÈëµÄÊý×Ö
	
	if(n > 15)
	{
		my_printf("cmd fail");
	}
	else
	{
		my_printf("");
	}
	
		if(n & 0x01)  //1
		{
			 GPBDAT &= ~(0x1<<5);
		}
		else 
		{
			GPBDAT |= (0x1<<5);
		}
		if(n & 0x02)	//2
		{
			GPBDAT &= ~(0x1<<6);
		}
		else
		{
			GPBDAT |= (0x1<<6);
		}
		if(n & 0x04)	//3
		{
			GPADAT &= ~(0x1<<25);
		}
		else
		{
			GPADAT |= (0x1<<25);
		}
		if(n & 0x08)	//4
		{
			GPADAT &= ~(0x1<<26);
		}
		else
		{
			GPADAT |= (0x1<<26);
		}

}