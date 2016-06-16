void temper()
{
  float temper_values[temper_num]; // temperature values
  char temper_str[13];  // for storing the temperature value in string format to display it
  temper_sensors.requestTemperatures(); // Send the command to get temperatures
  for(int i = 0; i < temper_num; i++)
  {
    temper_values[i] = temper_sensors.getTempFByIndex(i); // collect the data
    //dtostrf(temper_values[i],5,5,5);
    itoa(temper_values[i], temper_str, 10);
    uoled.Text(4, i, 2, 150, temper_str, 1);
    uoled.Text(7, i, 2, 150, "deg F",1);
  }
  if(temper_values[0] > 100.0) uoled.Rectangle(0,64, screen_pixels_x,screen_pixels_y, slow_color, 1);
  else if(temper_values[0] < 50.0) uoled.Rectangle(0,64, screen_pixels_x,screen_pixels_y, med_color, 1);
  else uoled.Rectangle(0,64, screen_pixels_x,screen_pixels_y, 0, 1);
}

