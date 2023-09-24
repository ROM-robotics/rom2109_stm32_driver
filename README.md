# libraries_stm32_driver
ROM2109 ROBOT CONTROLLER
DEVELOPED BY ROM ROBOTICS MYANMAR

- MAX SPEED = 0.36 ms


- jtag debugg pin များကိုသုံးထားပါက jtag disable လုပ်ဖို့လိုမယ်
- * , / operation များအစား logical &,| နဲ့ << , >> တွေသုံးရင် ပိုမြန်မယ်။
- register များကို အမှတ်မထင် = နဲ့ assign လုပ်ခဲ့ခြင်း များကို ပြန်ရှာပါ။
- right motor pid tune ဖို့လို

timer များ <br>

timer8 -> pwm ၄ ခု <br>
timer5 -> motor D encoder<br>
timer4 -> motor C encoder<br>
timer3 -> motor B encoder<br>
timer2 -> motor A encoder<br>
# rom2109_stm32_driver

##### computer မှ velocity ပို့ ရင် L R +CR တွဲပို့ပါ။


<a href="https://www.youtube.com/watch?v=qeWIGDeaKrE"> pid tuning လုပ်ရန် </a>

##### ROS2 HUMBLE အတွက် CONNECTION က ဒီလို
MCU --> "RIGHT_tick_string LEFT_tick_string \r\n" --> ROBOT COMPUTER 
( long to char* (string) --> UART SEND STRING --> I DON'T KNOW)

ROBOT COMPUTER --> "RIGHT_rps_string LEFT_radian_per_string\r" --> MCU 
( double to float, float to string --> UART SEND STRING --> (rps)string to float , rps to rpm, float to int  )