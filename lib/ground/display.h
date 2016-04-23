#ifndef SNAKE_DISPLAY
#define SNAKE_DISPLAY

#include <Arduino.h>

//IO    
#define LEDARRAY_D 0
#define LEDARRAY_C 1
#define LEDARRAY_B 2
#define LEDARRAY_A 3
#define LEDARRAY_G 4
#define LEDARRAY_DI 5
#define LEDARRAY_CLK 6
#define LEDARRAY_LAT 7

class Display {
public:

    unsigned char Display_Buffer[2];

    const unsigned char  Init_Display[32] = {
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    };

    void Send( unsigned char dat) {
        unsigned char i;
        digitalWrite(LEDARRAY_CLK, LOW);
        delayMicroseconds(1);;  
        digitalWrite(LEDARRAY_LAT, LOW);
        delayMicroseconds(1);;

        for( i = 0 ; i < 8 ; i++ )
        {
            if( dat&0x01 )
            {
                digitalWrite(LEDARRAY_DI, HIGH);    
            }
            else
            {
                digitalWrite(LEDARRAY_DI, LOW);
            }

            delayMicroseconds(1);
            digitalWrite(LEDARRAY_CLK, HIGH);  
                delayMicroseconds(1);
            digitalWrite(LEDARRAY_CLK, LOW);
                delayMicroseconds(1);       
            dat >>= 1;
                
        }           
    }

    void Scan_Line( unsigned char m) {   
        switch(m) {
        case 0:         
            digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, LOW);                    
            break;
        case 1:                 
            digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, HIGH);       
            break;
        case 2:                 
            digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, LOW);       
            break;
        case 3:                 
            digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, HIGH);      
            break;
        case 4:
            digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, LOW);       
            break;
        case 5:
            digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, HIGH);      
            break;
        case 6:
            digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, LOW);      
            break;
        case 7:
            digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, HIGH);         
            break;
        case 8:
            digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, LOW);       
            break;
        case 9:
            digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, HIGH);      
            break;  
        case 10:
            digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, LOW);      
            break;
        case 11:
            digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, HIGH);         
            break;
        case 12:
            digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, LOW);      
            break;
        case 13:
            digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, HIGH);         
            break;
        case 14:
            digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, LOW);         
            break;
        case 15:
            digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, HIGH);        
            break;
        default: break;    
        }
    }


    void print(const unsigned char dat[32]) {
        unsigned char i;

        for( i = 0 ; i < 16 ; i++ )
        {
            digitalWrite(LEDARRAY_G, HIGH);
            
            Display_Buffer[0] = dat[i];      
            Display_Buffer[1] = dat[i+16];

            Send(Display_Buffer[1]);
            Send(Display_Buffer[0]);

            digitalWrite(LEDARRAY_LAT, HIGH);  
            delayMicroseconds(1);
        
            digitalWrite(LEDARRAY_LAT, LOW);
            delayMicroseconds(1);

            Scan_Line(i);

            digitalWrite(LEDARRAY_G, LOW);
            
            delayMicroseconds(100);                  
        }   
    }

    Display() {
        pinMode(LEDARRAY_D, OUTPUT); 
        pinMode(LEDARRAY_C, OUTPUT);
        pinMode(LEDARRAY_B, OUTPUT);
        pinMode(LEDARRAY_A, OUTPUT);
        pinMode(LEDARRAY_G, OUTPUT);
        pinMode(LEDARRAY_DI, OUTPUT);
        pinMode(LEDARRAY_CLK, OUTPUT);
        pinMode(LEDARRAY_LAT, OUTPUT);

        print(Init_Display);
    }
};

#endif