void breakout()
{
  int x_vel = 1;  //speed of ball
  int y_vel = 1;
  int ball_x = 40;  // position of ball
  int ball_y = 40;
  unsigned int ball_color = 0x7E0;  // ball color
  int ball_time = 0;  // current number of cycles
  int ball_time_cycles = 5;  // number of program cycles to update ball position, to control speed of ball without using delay
  int ball_num = 3;  // number of balls left
  int ball_size = 2;  // size of the ball
  char ball_num_str[2];
  
  int background_color = 0;  // color of the background

  int pad_x = 48;  // Paddle location
  int pad_x_last = 48;  // last paddle location, used for setting pad_vel
  int pad_size = 10;  // half the paddle size, extends this much left and right
  //int pad_vel = 0;  // velocity of the paddle, so that the ball can change x_vel when hitting the pad
  int pad_speed = 3;  // speed at which you can move the paddle

  int temp; // temp variable for using abs()

  unsigned int score = 0;
  char score_str[6];
  

  byte stage_change = 1;  // active to load stage
  byte stage = 0;  // index for current stage
  byte stage_num = 1; // number of stages
  int brick_color[4] = {0, fast_color, med_color, slow_color} ;
  byte bricksleft[1];  // number of hits on bricks on each stage, sum the numbers on the map
  const byte level_int[1][8][12] =  // stage maps
  {
    {
      {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0            }
      ,
      {
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3            }
      ,
      {
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2            }
      ,
      {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1            }
      ,
      {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0            }
      ,
      {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0            }
      ,
      {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0            }
      ,
      {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0            }
      ,      
    }
  };
  byte level[8][12]; // current loaded stage
  
  detachInterrupt(1);

  byte breakout_run = 1;
  while(breakout_run)
  {
    if(stage_change)
    {
      uoled.Cls(); // initialize the screen
      for(int i = 0; i < 8; i++)
      {
        for(int j = 0; j < 12; j++)
        {
          level[i][j] = level_int[stage][i][j];
          uoled.PutBMPChar(level[i][j] + 6, (j * 8) + screen_adjust_x, i * 8, brick_color[level[i][j]]); // initial draw the bricks
          bricksleft[stage] += level_int[stage][i][j]; // count the bricks in the stage (need to change when unbreakable bricks are added)
        }
      }
      stage_change = 0;      
    }
    
    pad_x_last = pad_x;
    trackball(pad_x, xy_empty);
    pad_x = pad_x + pad_speed * (pad_x - pad_x_last);  // control the pad speed
    if(pad_x + pad_size > 95) pad_x = 95 - pad_size;  // kept pad on screen
    if(pad_x - pad_size < 0) pad_x = 0 + pad_size;  
    //pad_vel = (pad_x - pad_x_last); // set pad_vel
    
    uoled.Line(0 + screen_adjust_x, 62, 95 + screen_adjust_x, 62, 0);  // clear paddle
    uoled.Line((pad_x - pad_size) + screen_adjust_x, 62, (pad_x + pad_size) + screen_adjust_x, 62, 0x7E0);  // draw paddle

    ball_time++;
    if(ball_time = ball_time_cycles)  // move the ball, put anything that interacts with the ball here, which is most things
    {
      uoled.Rectangle(0 + screen_adjust_x,56, 95 + screen_adjust_x,61, background_color, 1); // clear the play field without clearing the rest fo the screen
      uoled.Rectangle(0 + screen_adjust_x,63, 95 + screen_adjust_x,65, background_color, 1); // clear the play field without clearing the rest fo the screenball_time = 0;  // reset ball time
      
      
      /*  only updating the screen where the ball is so commenting this out
      for(int i = 0; i < 3; i++)
        {
          for(int j = 0; j < 12; j++)
          {
            //uoled.PutBMPChar(6, j * 8, i * 8, 0);  // clear the screen
            uoled.PutBMPChar(level[i][j] + 6, j * 8, 8 + (i * 8), level[i][j] * 150); // draw the bricks
          }
        }
        */  
      
      if(ball_x < 8 || (ball_x % 8 > 3 && ball_x < 88))
      {
        if(ball_y < 8 || (ball_y % 8 > 3 && ball_y < 56))
        {
          for(int j = (ball_x / 8); j < 2 + (ball_x / 8); j++)
          {
            for(int i = (ball_y / 8); i < 2 + (ball_y / 8); i++)
            {
              uoled.PutBMPChar(6, (j * 8) + screen_adjust_x, i * 8, 0);  // clear the spot
              uoled.PutBMPChar(level[i][j] + 6, (j * 8) + screen_adjust_x, i * 8, brick_color[level[i][j]]); // draw the bricks
            }
          }
        }
        else
        {
          for(int j = (ball_x / 8); j < 2 + (ball_x / 8); j++)
          {
            for(int i = (ball_y / 8) - 1; i < 1 + (ball_y / 8); i++)
            {
              uoled.PutBMPChar(6, (j * 8) + screen_adjust_x, i * 8, 0);  // clear the spot
              uoled.PutBMPChar(level[i][j] + 6, (j * 8) + screen_adjust_x, i * 8, brick_color[level[i][j]]); // draw the bricks
            }
          }
        }
      }
      else
      {
        if(ball_y < 8 || (ball_y % 8 > 3 && ball_y < 56))
        {
          for(int j = (ball_x / 8) - 1; j < 1 + (ball_x / 8); j++)
          {
            for(int i = (ball_y / 8); i < 2 + (ball_y / 8); i++)
            {
              uoled.PutBMPChar(6, (j * 8) + screen_adjust_x, i * 8, 0);  // clear the spot
              uoled.PutBMPChar(level[i][j] + 6, (j * 8) + screen_adjust_x, i * 8, brick_color[level[i][j]]); // draw the bricks
            }
          }
        }
        else
        {
          for(int j = (ball_x / 8) - 1; j < 1 + (ball_x / 8); j++)
          {
            for(int i = (ball_y / 8) - 1; i < 1 + (ball_y / 8); i++)
            {
              uoled.PutBMPChar(6, (j * 8) + screen_adjust_x, i * 8, 0);  // clear the spot
              uoled.PutBMPChar(level[i][j] + 6, (j * 8) + screen_adjust_x, i * 8, brick_color[level[i][j]]); // draw the bricks
            }
          }
        }
      }
      
      ball_x = ball_x + x_vel;  // move ball in x direction
      ball_y = ball_y + y_vel;  // move ball in y direction
      
      
      uoled.Circle(ball_x + screen_adjust_x, ball_y, ball_size, ball_color, 1);  // draw ball

      if(ball_y < 55 && level[ball_y / 8][ball_x / 8])  // ball hits a brick
      {
        score += (4 - level[ball_y / 8][ball_x / 8]) * 50; // raise the score
        level[ball_y / 8][ball_x / 8]--;
        bricksleft[stage]--; // decrease total number of bricks left on level
        y_vel = ~y_vel + 1;  // change the y_vel from pos to neg or neg to pos
        if(!bricksleft[stage])
        {
          stage++;
          ball_x = 48;  // reset position of ball and paddle for start of next stage
          ball_y = 40;
          pad_x = 48;
          stage_change = 1; // load the new stage
          if(stage == stage_num)
          {
            uoled.Text(4,2, 2, 150, "You Win!",1);  // you win!
            delay(1000);
            pad_size--; // now it's harder this time!
            stage = 0; // reset to stage 0
          }
        }
      }

      temp = ball_x - pad_x;
      if(ball_y == 62 && abs(temp) < pad_size) // ball hits pad
      {
        y_vel = ~y_vel + 1;  // change the y_vel from pos to neg or neg to pos
        //x_vel += pad_vel; // add the pad's velocity to the ball's velocity
        if(temp < -5) x_vel--;  // if you hit the left edge of the paddle angle to the left
        if(temp > 5) x_vel++;  // if you hit the right edge of the paddle angle to the right
      }
      if(ball_y < 1 + ball_size) // ball hits top wall
      {
        y_vel = ~y_vel + 1;  // change the y_vel from pos to neg or neg to pos
      }
      if(ball_x < 0 + ball_size || ball_x > 94 - ball_size)  // ball hits a side wall
      {
        x_vel = ~x_vel + 1;  // change the x_vel from pos to neg or neg to pos
      }
      if(ball_y == 63)
      {
        ball_num--;  // decrease number of balls left
        if(ball_num < 0)
        {
          attachInterrupt(1, click, FALLING);  // Reattach the interrupt
          uoled.Text(4,2, 2, 150, "Game Over",1);  // you lose!
          delay(1000);
          breakout_run = 0;
        }
        else
        {
          ball_x = 40;  // reset position of ball and pad
          ball_y = 40;
          pad_x = 48;
          x_vel = 1;  
          y_vel = 1;
        }
      }
      
      itoa(score, score_str, 10); // update score string
      uoled.Text(4, 0, 0, 150, score_str,1);  // note the update for this is in the if when the ball is active
      itoa(ball_num, ball_num_str, 10);  // update number of balls
      uoled.Text(18, 0, 0, 150, ball_num_str,1);  // note the update for this is in the if when the ball is active
    }
    
  }
}
