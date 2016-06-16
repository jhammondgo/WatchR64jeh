void clockbinary()
{
  int binaryoffset_x = 16;
  if(modechange)
  {
    modechange = 0;
    for(int i = 0; i < 6; i++)
    {
      uoled.Circle(5 + binaryoffset_x, 55-10*i, 3, slow_color, 1);
    }
    for(int i = 0; i < 4; i++)
    {
      uoled.Circle(20 + binaryoffset_x,55-10*i, 3, med_color, 1);
    }
    for(int i = 0; i < 5; i++)
    {
      uoled.Circle(35 + binaryoffset_x,55-10*i, 3, fast_color, 1);
    }
    for(int i = 0; i < 5; i++)
    {
      uoled.Circle(55 + binaryoffset_x,55-10*i, 3, slow_color, 1);
    }
    for(int i = 0; i < 6; i++)
    {
      uoled.Circle(70 + binaryoffset_x,55-10*i, 3, med_color, 1);
    }
    for(int i = 0; i < 6; i++)
    {
      uoled.Circle(85 + binaryoffset_x,55-10*i, 3, fast_color, 1);
    }
  }

  for(int i = 0; i < 6; i++)
  {
    if(((year - 2000) >> i) & 1)
    {
      uoled.Circle(5 + binaryoffset_x,55-10*i, 3, slow_color, 1);
    }
    else
    {
      uoled.Circle(5 + binaryoffset_x,55-10*i, 2, background_color, 1);
    }
  }
  for(int i = 0; i < 4; i++)
  {
    if((month >> i) & 1)
    {
      uoled.Circle(20 + binaryoffset_x,55-10*i, 3, med_color, 1);
    }
    else
    {
      uoled.Circle(20 + binaryoffset_x,55-10*i, 2, background_color, 1);
    }
  }
  for(int i = 0; i < 5; i++)
  {
    if((day >> i) & 1)
    {
      uoled.Circle(35 + binaryoffset_x,55-10*i, 3, fast_color, 1);
    }
    else
    {
      uoled.Circle(35 + binaryoffset_x,55-10*i, 2, background_color, 1);
    }  
  }
  for(int i = 0; i < 6; i++)
  {
    if((hour >> i) & 1)
    {
      uoled.Circle(55 + binaryoffset_x,55-10*i, 3, slow_color, 1);
    }
    else
    {
      uoled.Circle(55 + binaryoffset_x,55-10*i, 2, background_color, 1);
    }
  }
  for(int i = 0; i < 6; i++)
  {
    if((minute >> i) & 1)
    {
      uoled.Circle(70 + binaryoffset_x,55-10*i, 3, med_color, 1);
    }
    else
    {
      uoled.Circle(70 + binaryoffset_x,55-10*i, 2, background_color, 1);
    }
  }
  for(int i = 0; i < 6; i++)
  {
    if((sec >> i) & 1)
    {
      uoled.Circle(85 + binaryoffset_x,55-10*i, 3, fast_color, 1);
    }
    else
    {
      uoled.Circle(85 + binaryoffset_x,55-10*i, 2, background_color, 1);
    }  
  }
}  

