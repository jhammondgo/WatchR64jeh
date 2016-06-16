void clockanalog()
{
  //Start clockanalog variables
  float Pi = 3.14159;
  float clock_size = 40.0;
  float x_clock = 48.0; 
  float y_clock = 48.0;
  //End clockanalog variables
  
  //uoled.Cls();
  uoled.Circle(x_clock,y_clock, 0.85 * clock_size, background_color,1);
  uoled.Circle(x_clock,y_clock, clock_size, slow_color,0);
  uoled.Line(x_clock, y_clock, x_clock + 0.6 * clock_size  * sin(Pi * (float(minute)/60.0 + float(hour))/6.0), y_clock - 0.6 * clock_size * cos(Pi * (float(minute)/60.0 + float(hour))/6.0), slow_color);
  uoled.Line(x_clock, y_clock, x_clock + 0.8 * clock_size * sin(Pi * float(minute)/30.0), y_clock - 0.8 * clock_size * cos(Pi * float(minute)/30.0), med_color);
  uoled.Line(x_clock, y_clock, x_clock + 0.8 * clock_size * sin(Pi * float(sec)/30.0), y_clock - 0.8 * clock_size * cos(Pi * float(sec)/30.0), fast_color);
  for(int i = 1; i < 13; i++)
  {
    //uoled.CharacterGraphic(i + 48.0, x_clock + clock_size * 1.2 * sin(Pi * float(i) / 6.0), y_clock - clock_size * 1.2 * cos(Pi * float(i) / 6.0), slow_color, 1, 1, 1);
    uoled.Line(x_clock + 0.9 * clock_size * sin(Pi * float(i)/6.0), y_clock - 0.9 * clock_size * cos(Pi * float(i)/6.0), x_clock + clock_size * sin(Pi * float(i)/6.0), y_clock - clock_size * cos(Pi * float(i)/6.0), slow_color);
  }
  //uoled.Text(0,4, 2, 150, time_str,1);  // debug line
}
