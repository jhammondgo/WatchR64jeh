void paint()
{
  if(modechange)  // paint initialization
  {
    detachInterrupt(1);
    modechange = 0;
  }
  trackball(x_pos, y_pos);
  if(y_pos > screen_pixels_y) y_pos = screen_pixels_y;
  if(x_pos > screen_pixels_x) x_pos = screen_pixels_x;
  uoled.PutBMPChar(1, 87, screen_pixels_y - 8, 63488); // Put the exit icon in the corner
  uoled.PutBMPChar(2, 79, screen_pixels_y - 8, 150); // Put the erase icon next to the exit icon
  uoled.PutBMPChar(3, 60, screen_pixels_y - 8, color); // Put the color icon
  uoled.PutBMPChar(4, 40, screen_pixels_y - 8, 150); // Put the save icon
  uoled.PutBMPChar(5, 30, screen_pixels_y - 8, 0x03F0); // Put the load icon
  if(buttonstate == 1 && buttonlaststate == 0) painttoggle = !painttoggle;
  if(painttoggle) uoled.PutPixel(x_pos, y_pos, color);

  
  if(y_pos > screen_pixels_y - 8)  // Enter into the menu area at the bottom of the screen
  {
    if(x_pos > 60 && x_pos < 68 && buttonstate) // Start the color selector
    {
      byte color_select_run = 1;
      while(color_select_run)
      {
        trackball(color_x, color_y);
        //color_y = (color >> color_x) & 1;
        //trackball(xy_empty, color_y);
        if(color_y > 2) color_y = 2; 
        if(color_y != 1) bitWrite(color, (15 - color_x), !color_y); //this is used for toggling color bits on (y=0) and off (y=2)
        color_y = 1;  // so that when switching bits they are not toggled
        if(color_x > 15) color_x = 15;  //this keeps the x value within the 2 byte range

        //color is a 16 bit value bits 0-4 are for blue (5bits), 5-10 are for green (6bits), 11-15 are for red (5bits)

        uoled.Rectangle(96,screen_pixels_y - 9, screen_pixels_x,screen_pixels_y - 1, color, 1);  // background behind the bits to show what color you are selecting
        uoled.Line(0,screen_pixels_y, 29,screen_pixels_y, 0xF800);  // red underline for red bits
        uoled.Line(30,screen_pixels_y, 65,screen_pixels_y, 0x7E0);  // green underline for green bits
        uoled.Line(66,screen_pixels_y, 95,screen_pixels_y, 0x1F);  // blue underline for blue bits
        uoled.Line(0, screen_pixels_y - 9, 95, screen_pixels_y - 9, 0);  // clear the white overline to know what bit you are on
        uoled.Line(6 * color_x, screen_pixels_y - 9, (6 * color_x) + 6, screen_pixels_y - 9, 0xFFFF);  // white overline to know what bit you are on
        for(int i = 0; i < 16; i++)
        {
          uoled.CharacterGraphic(((color >> i) & 1) + 48, 90 - (i * 6), screen_pixels_y - 8, 0xFFFF, 1, 1, 1);
        }

        if(buttonstate == 1 && buttonlaststate == 0) 
        {
          color_select_run = 0;  // exit the while loop and go back to paintin
          uoled.Rectangle(0,screen_pixels_y - 9, screen_pixels_x,screen_pixels_y, background_color, 1); // clear the menu bar for the icons without clearing the rest of the screen
          x_pos = 64;  // reset position so it doesn't automatically go back into the color picker
          y_pos = screen_pixels_y - 15;
          painttoggle = 0;
        }
      }
    }
    if(x_pos > 87 && buttonstate) attachInterrupt(1, click, FALLING); //exit paint

    if(x_pos < 87 && x_pos > 79 && buttonstate) uoled.Cls();  // clear screen button
    
    if(x_pos > 40 && x_pos < 48 && buttonstate)  // save screen button
    {
    }
    
    if(x_pos > 30 && x_pos < 38 && buttonstate)  // load screen button
    {
    }

    uoled.PutPixel(x_pos, y_pos, 65504);  // Make the cursor visible for the menu bar
  }
  
  char x_pos_str[3];
  itoa(x_pos, x_pos_str, 10); 
  uoled.Text(0,0, 0, 150, x_pos_str,1);

  char y_pos_str[3];
  itoa(y_pos, y_pos_str, 10); 
  uoled.Text(0,1, 0, 150, y_pos_str,1);
  
}
