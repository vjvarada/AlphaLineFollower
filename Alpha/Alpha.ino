//---------------------------------------------------------------//
//7 line sensing array PWM from PID algorithm line follower      //
//Written and debugged by Viay Raghav Varada, 2011               //
//MIT Manipal                                                    //
//---------------------------------------------------------------//



//Sesors- digital pin 2-8
//Motors-9-10

long sensor;
int motor_right=10;  //Right motor pin(pwm)
int motor_left=11;    //left motor pin(pwm)
int left_back=6;
int right_back=5;
int right_speed;
int left_speed;
int pos;
int integral;
int derivative;
long proportional;
int last_proportional;
int error_value;
int max_speed=200;
float Kp=25 ; // ~30 main control, keep above 30
float Kd=4; // ~50 of osscillations are too much keep above 50
float Ki=0;  //~0.001  decrease to get more slowtime,calculates error overtime and gives power jerks to th motor aith wincrease with increse in ki

void readsensor()
{
 int single[4];
          sensor =7;
          for(int i=0;i<7;i++)
          { 
              single[i] = digitalRead(i+2);
              sensor = ((sensor*10)+single[i]);
              
          }
          
}   
void condition()
    {
      switch (sensor) 
       {
      
        case 71000000: // Hard Right
              pos=-10;
              break;
              
              
        case 71100000: // Hard Right
              pos=-9;
              break; 
         
        
        case 71111110: // Hard Right
              pos=-8;
              break;
        
        case 71111100: // Hard Right
              pos=-7;
              break;
          
          case 71111000: // Hard Right
              pos=-6;
              break;
          
          case 71111101: // Hard Right
              pos=-5;
              break;
          
          case 71111001: // Hard Right
              pos=-4;
              break;
          
          case 71110001: // Hard Right
              pos=-3;
              break;
          
          case 71111011: // Hard Right
              pos=-2;
              break;
          
          case 71110011: // Hard Right
              pos=-1;
              break;
          
          case 71100011: // Hard Right
              pos=0;
              break;
          
          case 71110111: // Hard Right
              pos=0;
              break;
          
          case 711000111: // Hard Right
              pos=0;
              break;
          
          case 71100111: // Hard Right
              pos=1;
              break;
          
          case 71101111: // Hard Right
              pos=2;
              break;
          
          case 71000111: // Hard Right
              pos=3;
              break;
          
          case 71001111: // Hard Right
              pos=4;
              break;    
              
          case 71011111: // Hard Right
              pos=5;
              break;
                     
         case 70001111: // Hard Right
              pos=6;
              break;   
            
         case 70011111: // Hard Right
              pos=7;
              break;
         
         case 70111111: // Hard Right
              pos=8;
              break;  
           
         case 70000011: // Hard Right
              pos=9;
              break;    
            
        case 70000001: // Hard Right
              pos=10;
              break;  
              
               }
    }
void pid_calc()
    {
          proportional = pos;
          integral = integral + proportional;
          derivative = proportional - last_proportional;
          last_proportional = proportional;
          error_value = int(proportional * Kp + integral * Ki + derivative * Kd);
      }
void calc_turn()   
     { 
          if (error_value< -max_speed)
            {
              error_value = -max_speed;
            }
          if (error_value> max_speed)            //Restricting the error value between +256 and -256.
            {
              error_value = max_speed;
            }
     

          if (error_value< 0)     // If error_value is NEGATIVE calculate right turn speed values
            {
              right_speed = max_speed + error_value;
              left_speed = max_speed;
            }
          
          else    // If error_value is POSITIVE calculate left turn speed  values
            {
              right_speed = max_speed;
              left_speed = max_speed - error_value;
            }
     }
void motor_drive(int right_speed, int left_speed)
      { // Drive motors according to the calculated values for a turn
          analogWrite(motor_right, right_speed);
          analogWrite(motor_left, left_speed);
      }
void setup() {
 
}
void loop() 
{    
     readsensor();
     condition();
     pid_calc();
     calc_turn();
     motor_drive(right_speed,left_speed);

     //}
     }
    
     
