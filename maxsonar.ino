void maxsonar()  // maxsonar code based on code from Bruce Allen found at http://www.arduino.cc/playground/Main/MaxSonar
{
  unsigned int sonar_pulse;


  sonar_pulse = pulseIn(sonarpin, HIGH); 
  sonar_in = sonar_pulse / 147;  //147uS per inch
  sonar_cm = sonar_in * 2.54;  //change inches to centimetres
}

