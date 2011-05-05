#!/bin/bash
    
gcc prog.c -o 1.bin
                                                
time ./1.bin & 
                                                                            
PID=$(pidof -s "1.bin")            
j=1;    
while [[ -z $PID ]]; 
do                                 
(taskset -p $j $PID) > /dev/null                                        
j=$(($j^1));                                    
PID=$(pidof -s "1.bin")                                                                            
done       
                                                                                             
time./1.bin   
                                                                            
rm 1.bin      