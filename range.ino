void range()
{
  maxsonar();

  char sonar_in_str[4];
  itoa(sonar_in, sonar_in_str, 10);
  sonar_in_str[3] = ' ';
  if(sonar_in < 10) 
  {
    sonar_in_str[2] = sonar_in_str[0];
    sonar_in_str[1] = ' ';
    sonar_in_str[0] = ' ';
  }
  else if(sonar_in < 100)
  {
    sonar_in_str[2] = sonar_in_str[1];
    sonar_in_str[1] = sonar_in_str[0];
    sonar_in_str[0] = ' ';
  }

  uoled.Text(0,0, 2, 150, sonar_in_str,1);
  uoled.Text(4,0, 2, 150, "inches",1);

  char sonar_cm_str[4];
  itoa(sonar_cm, sonar_cm_str, 10); 
  sonar_cm_str[3] = ' ';

  if(sonar_cm < 10) 
  {
    sonar_cm_str[2] = sonar_cm_str[0];
    sonar_cm_str[1] = ' ';
    sonar_cm_str[0] = ' ';
  }
  else if(sonar_cm < 100)
  {
    sonar_cm_str[2] = sonar_cm_str[1];
    sonar_cm_str[1] = sonar_cm_str[0];
    sonar_cm_str[0] = ' ';
  }

  uoled.Text(0,2, 2, 150, sonar_cm_str,1);
  uoled.Text(4,2, 2, 150, "cm",1);

  //if(sonar_in < 89) uoled.playTone(sonar_in - 4, 1000);  // play piano keys for the first 7.5ft, more pleasant
  //if(sonar_in > 88) uoled.playTone(10000 - (50 * sonar_in), 1000);  // play freq tone for >7.5ft lower the tone the farther away
}
