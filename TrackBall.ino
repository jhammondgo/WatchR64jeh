void click()
{
  mode++;
  if(mode > 4)
  {
    mode = 0;
  }
}

void trackball(int &x, int &y)
{
  if(rightstate != digitalRead(rightpin))
  {
    x++; //increases x to move right
    rightstate = !rightstate;
    //if(x > uoled.x_res) x = uoled.x_res;  
  }
  if(leftstate != digitalRead(leftpin))
  {
    x--; //decrease x to move left
    leftstate = !leftstate;
    if(x < 0) x = 0;         
  }
  if(upstate != digitalRead(uppin))
  {
    y++; //increase y to move up
    upstate = !upstate;
  }
  if(downstate != digitalRead(downpin))
  {
    y--; //decrease y to move down
    downstate = !downstate;
    if(y < 0) y = 0;
  }
  buttonlaststate = buttonstate;
  buttonstate = !digitalRead(buttonpin);    
}
