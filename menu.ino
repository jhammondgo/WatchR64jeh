void menu()
{
  if(modechange)
  {
    x_pos = 48;
    y_pos = 32;
    modechange = 0;

    uoled.TextGraphic(item3_corner_x + 1, item3_corner_y + 2, 0, 75, 1, 1, "Breakout",1);
    uoled.Rectangle(item3_corner_x, item3_corner_y, item3_corner_x + item_size_x, item3_corner_y + item_size_y, slow_color, 0);

    uoled.TextGraphic(item2_corner_x + 1, item2_corner_y + 2, 0, 75, 1, 1, "Paint",1);
    uoled.Rectangle(item2_corner_x, item2_corner_y, item2_corner_x + item_size_x, item2_corner_y + item_size_y, slow_color, 0);

    uoled.TextGraphic(item4_corner_x + 1, item4_corner_y + 2, 0, 75, 1, 1, "Temper",1);
    uoled.Rectangle(item4_corner_x, item4_corner_y, item4_corner_x + item_size_x, item4_corner_y + item_size_y, slow_color, 0);

    uoled.TextGraphic(item5_corner_x + 1, item5_corner_y + 2, 0, 75, 1, 1, "Range",1);
    uoled.Rectangle(item5_corner_x, item5_corner_y, item5_corner_x + item_size_x, item5_corner_y + item_size_y, slow_color, 0);

    uoled.TextGraphic(item6_corner_x + 1,item6_corner_y + 2, 0, 75, 1, 1, "Set Time",1);
    uoled.Rectangle(item6_corner_x, item6_corner_y, item6_corner_x + item_size_x, item6_corner_y + item_size_y, slow_color, 0);

    uoled.TextGraphic(item1_corner_x + 1, item1_corner_y + 2, 1, 75, 1, 1, "Shut Down",1);
    uoled.Line(0,item1_corner_y - 1, screen_pixels_y, item1_corner_y - 1, 0xF800);

  }


  trackball(x_pos, y_pos);
  uoled.PutPixel(x_pos, y_pos, color);

  if(x_pos < item3_corner_x + item_size_x && x_pos > item3_corner_x && y_pos < item3_corner_y + item_size_y && y_pos > item3_corner_y)
  {
    mode = 6;
  }

  if(x_pos < item2_corner_x + item_size_x && x_pos > item2_corner_x && y_pos < item2_corner_y + item_size_y && y_pos > item2_corner_y)
  {
    mode = 5;
  }

  if(x_pos < item4_corner_x + item_size_x && x_pos > item4_corner_x && y_pos < item4_corner_y + item_size_y && y_pos > item4_corner_y)
  {
    mode = 7;
  }

  if(x_pos < item5_corner_x + item_size_x && x_pos > item5_corner_x && y_pos < item5_corner_y + item_size_y && y_pos > item5_corner_y)
  {
    mode = 8;
  }

  if(x_pos < item6_corner_x + item_size_x && x_pos > item6_corner_x && y_pos < item6_corner_y + item_size_y && y_pos > item6_corner_y)
  {
    mode = 9;
  }

  if(y_pos > item1_corner_y - 1)  //Shutdown crossline
  {
    detachInterrupt(1);  // Disconnect button for power down 
    uoled.SetPowerState(0); // Power down the OLED
    xy_empty = 1;  // repurpose xy_empty variable to hold open this while loop
    while(xy_empty)
    {
      digitalWrite(powerpin, LOW);  //Power down trackball
      delay(1000);
      digitalWrite(powerpin, HIGH);  //Power up trackball to check for button press
      delay(10);  // Wait for button to power up, DO I NEED THIS?
      if(!digitalRead(buttonpin)) xy_empty = 0;  // check for button press to power back up
      /* 
       n++;
       if(n == 10)
       {
       xy_empty = 0;
       }
       */
    }
    attachInterrupt(1, click, FALLING);  // Reattach the interrupt
    uoled.SetPowerState(1); // Power up the OLED
    x_pos = 48;  // Reset cursor so it doesn't automatic shut down again
    y_pos = 32;
  }
}
