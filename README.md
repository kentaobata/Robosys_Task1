# Robot system science Task1  
 
 LED and Buzzer system  
   
   
 //example of use    
 $ echo b > /dev/myled0  :  blue LED flashes.  
 $ echo p > /dev/myled0  :  sound buzzer.  
 $ echo A > /dev/myled0  :  blue and red LEDs and buzzer work together. 

 //Demo
 https://youtu.be/43xtGDb3VXU
 
 //Usage  
 $git clone
 $sudo insmod myled.ko  
 $sudo chmod 666 /dev/myled0  

