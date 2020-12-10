# Robot system science Task1  
LED and Buzzer system  
 
# example of use  
~~~
$ echo b > /dev/myled0  :  blue LED flashes.  
$ echo p > /dev/myled0  :  sound buzzer.  
$ echo A > /dev/myled0  :  blue and red LEDs and buzzer work together. 
~~~~
# Demo
https://youtu.be/43xtGDb3VXU

# Operating environment
OS:Linux20.04.1 LTS

# What was used
Raspberry Pi 4 (8GB)  
Universal board  
LED(blue, red)　one for each  
Resistance　220Ω　2pieces  
Jumper wire 4pieces  
圧電スピーカー(SPT08)  

# Usage  
~~~
$git clone https://github.com/kentaobata/robosys_task1.git　  
$cd myled  
$make   
$sudo insmod myled.ko  
$sudo chmod 666 /dev/myled0  　
~~~

# LICENSE  
GPL-3.0  

# Reference　　
https://github.com/ryuichiueda/robosys_device_drivers　　

