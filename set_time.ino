void set_time()
{
  byte set_time_run = 1;
  
  //byte time_remain = 0;
  while(set_time_run)
  {
    trackball(time_x, time_y);
    /*
    time_remain = time_x % 2;
    time_x /= 2;
    */
    if(time_x > 5) time_x = 1;
    if(time_x < 1) time_x = 5;
    if(time_y > 2) time_y = 2; 
    
    
    
    if(time_x < 3) 
    {
      //uoled.Line(0, 55, 127, 55, background_color);  //clear line
      uoled.Line(15 * time_x + 10 + screen_adjust_x, 26 + screen_adjust_y, (15 * time_x) + 26 + screen_adjust_x, 26 + screen_adjust_y, 0xFFFF);  // white overline
    }
    if(time_x > 2) 
    {      
      //uoled.Line(0, 64, 127, 64, background_color);  //clear line
      uoled.Line(15 * (time_x - 3) + 10, 43 + screen_adjust_y, (15 * time_x) + 26, 43 + screen_adjust_y, 0xFFFF);  // white overline
    }
    
    switch (time_x)
    {
      case 1: 
        if(time_y < 1) 
        {
          hour++;  // remember trackball y goes down with up
          if(hour > 23) hour = 0;
        }
        if(time_y > 1) 
        {
          hour--;
          if(hour < 0) hour = 23;
        }
      break;
      
      case 2:
        if(time_y < 1) 
        {
          minute++;  // remember trackball y goes down with up
          if(minute > 59) minute = 0;
        }
        if(time_y > 1) 
        {
          minute--;
          if(minute < 0) minute = 59;
        }
      break;
      /*
      case 3:
        if(time_y < 1) 
        {
          sec++;  // remember trackball y goes down with up
          if(sec > 59) sec = 0;
        }
        if(time_y > 1) 
        {
          sec--;
          if(sec < 0) sec = 59;
        }
      break;
      */
      case 3:
        if(time_y < 1) 
        {
          month++;  // remember trackball y goes down with up
          if(month > 59) month = 0;
        }
        if(time_y > 1) 
        {
          month--;
          if(month < 0) month = 59;
        }
      break;
      
      case 4:
        if(time_y < 1) 
        {
          day++;  // remember trackball y goes down with up
          if(day > 31) day = 0;
        }
        if(time_y > 1) 
        {
          day--;
          if(day < 0) day = 31;
        }
      break;
      
      case 5:
        if(time_y < 1) 
        {
          year++;  // remember trackball y goes down with up
          if(year > 2099) year = 2000;
        }
        if(time_y > 1) 
        {
          year--;
          if(year < 0) year = 2099;
        }
      break;
    }
    //time_x = time_x * 2 + time_remain;
    time_y = 1;  // reset y so it is controlable 
    RTC.adjust(DateTime(year, month, day, hour, minute, sec));
    /*
    RTC.stop();
    RTC.set(DS1307_SEC, sec);        //set the seconds
    RTC.set(DS1307_MIN, minute);     //set the minutes
    RTC.set(DS1307_HR, hour);       //set the hours
    RTC.set(DS1307_DOW, 5);       //set the day of the week
    RTC.set(DS1307_DATE, day);       //set the date
    RTC.set(DS1307_MTH, month);        //set the month
    RTC.set(DS1307_YR, year - 2000);         //set the year
    RTC.start();	
    */
    time_jeh();
    uoled.Text(4,4, 2, 75, time_str,1);
    uoled.Text(2,5, 2, 75, date_str,1);
    
    if(buttonstate) set_time_run = 0;
    
    if(time_x < 3) 
    {
      uoled.Line(0, 58, 95, 40, background_color);  //clear line
    }
    if(time_x > 2) 
    {      
      uoled.Line(0, 75, 95, 40, background_color);  //clear line
    }
    
    
    //Start debug code
    char time_x_str[2];
    itoa(time_x, time_x_str, 10); 
    uoled.Text(0,0, 0, 75, time_x_str,1);
    
    char time_y_str[2];
    itoa(time_y, time_y_str, 10); 
    uoled.Text(0,1, 0, 75, time_y_str,1);
    
    itoa(hour, hour_str, 10); 
    uoled.Text(0,3, 0, 75, hour_str,1);
    
    itoa(minute, minute_str, 10); 
    uoled.Text(0,4, 0, 75, minute_str,1);
    
    itoa(sec, sec_str, 10); 
    uoled.Text(0,5, 0, 75, sec_str,1);
    
    itoa(year, year_str, 10); 
    uoled.Text(0,6, 0, 75, year_str,1);
    //End debug code
    
  }
  
}
