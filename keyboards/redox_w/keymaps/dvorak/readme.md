### fork from default layout，and support dvorak layout[defalut layer]

##### only use 3 layers

```
Keymap: 3 Layers                   
-----------------                  
stack of layers                     
       ____________ precedence      
      /           / | high                 
  31 /___________// |                           
   :   _:_:_:_:_:__ |           
   3 /___________// | --- adjust   
   2 /___________// | --- qwerty         
   1 /___________// | --- symb
   0 /___________/  | --- dvorak[default]        
```

defalut LED indicators

RED --------- CAPS LOCK

BLUE ------- SYMB layer

GREEN----- QWERTY layer

WHITE------ NUM LOCK *in my test case,this is inefficient on mac os*

> BLUE and GREEN as a bit flag
> 
> 0                    0

| BLUE(0) | GREEN(0) | STATUS | DESCRIBE                                            |
|:-------:|:--------:|:------:|:--------------------------------------------------- |
| 0       | 0        | 0      | layer 0[dvorak] is active,and blue,green led is off |
| 1       | 0        | 1      | layer1[symb] is active, and blue led is on          |
| 0       | 1        | 2      | layer 2[qwerty] is active,and green led is on       |
| 1       | 1        | 3      | layer 3[adjust] is active,and blue,green led is on  |
