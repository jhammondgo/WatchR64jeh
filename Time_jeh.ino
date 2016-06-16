void time_jeh()
{
  DateTime now = RTC.now();
  year = now.year();
  month = now.month();
  day = now.day();
  hour = now.hour();
  minute = now.minute();
  sec = now.second();
  /*
  hour = RTC.get(DS1307_HR,true); //read the hour and also update all the values by pushing in true
  minute = RTC.get(DS1307_MIN,false);  //read minutes without update (false)
  sec = RTC.get(DS1307_SEC,false);  //read seconds
  day = RTC.get(DS1307_DATE,false);  //read day of month
  month = RTC.get(DS1307_MTH,false);  //read month
  year = RTC.get(DS1307_YR,false);  //read year
  */
  itoa(hour, hour_str, 10);   
  itoa(minute, minute_str, 10);  
  itoa(sec, sec_str, 10);   
  itoa(day, day_str, 10);   
  //itoa(month, month_str, 10); //commented out to use abrev. word months
  itoa(year, year_str, 10);


  if(hour > 9)
  {
    time_str[0] = hour_str[0];  
    time_str[1] = hour_str[1];
  }
  else
  {    
    time_str[0] = ' ';  
    time_str[1] = hour_str[0];
  }

  time_str[2] = ':';

  if(minute > 9)
  {  
    time_str[3] = minute_str[0];
    time_str[4] = minute_str[1];
  }
  else
  {
    time_str[3] = '0';
    time_str[4] = minute_str[0];
  }

  time_str[5] = ':';

  if(sec > 9)
  {
    time_str[6] = sec_str[0];
    time_str[7] = sec_str[1];
  }
  else
  {
    time_str[6] = '0';
    time_str[7] = sec_str[0];
  }

  switch(month)
  {
  case 1:
    strcpy(month_str, "Jan");
    break;
  case 2:
    strcpy(month_str, "Feb");
    break;
  case 3:
    strcpy(month_str, "Mar");
    break;
  case 4:
    strcpy(month_str, "Apr");
    break;
  case 5:
    strcpy(month_str, "May");
    break;
  case 6:
    strcpy(month_str, "Jun");
    break;
  case 7:
    strcpy(month_str, "Jul");
    break;
  case 8:
    strcpy(month_str, "Aug");
    break;
  case 9:
    strcpy(month_str, "Sep");
    break;
  case 10:
    strcpy(month_str, "Oct");
    break;
  case 11:
    strcpy(month_str, "Nov");
    break;
  case 12:
    strcpy(month_str, "Dec");
    break;
  }
  //Fomat month, day, year for display
  strcpy(date_str, month_str);
  date_str[3] = ' ';
  if(day > 9)
  {
    date_str[4] = day_str[0];  
    date_str[5] = day_str[1];
  }
  else
  {    
    date_str[4] = ' ';  
    date_str[5] = day_str[0];
  }
  date_str[6] = ',';
  date_str[7] = ' ';
  date_str[8] = year_str[0];
  date_str[9] = year_str[1];
  date_str[10] = year_str[2];
  date_str[11] = year_str[3];
}
