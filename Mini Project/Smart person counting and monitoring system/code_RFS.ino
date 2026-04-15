
volatile int count = 0;         
volatile int exitQueue = 0;       
volatile int alertFlag = 0;
volatile uint8_t lastActionFlag = 0; 


void lcdCommand(unsigned char cmd)
{
    PORTB &= ~(1 << PB2);  //RS0
    PORTD = (PORTD & 0x0F) | (cmd & 0xF0);
    PORTB |= (1 << PB3); //EN1
  _delay_us(1); 
  PORTB &= ~(1 << PB3);//en0
    _delay_us(200);
    PORTD = (PORTD & 0x0F) | ((cmd << 4) & 0xF0); 
    PORTB |= (1 << PB3);
  _delay_us(1); 
  PORTB &= ~(1 << PB3);
    _delay_ms(2);
}

void lcdData(unsigned char data) {
    PORTB |= (1 << PB2);//1
    PORTD = (PORTD & 0x0F) | (data & 0xF0);//up nibb
    PORTB |= (1 << PB3);
  _delay_us(1); 
  PORTB &= ~(1 << PB3);
    _delay_us(200);
    PORTD = (PORTD & 0x0F) | ((data << 4) & 0xF0);//lower nibb
    PORTB |= (1 << PB3); 
  _delay_us(1); 
  PORTB &= ~(1 << PB3);
    _delay_ms(2);
}

void lcdInit() {
    DDRD |= 0xF0; 
    DDRB |= (1 << PB2) | (1 << PB3); //RS EN o/p
    _delay_ms(20);
    lcdCommand(0x02);
    lcdCommand(0x28);
    lcdCommand(0x0C);
    lcdCommand(0x06);
    lcdCommand(0x01);
}

void lcdPrint(char *str) {
    while (*str) lcdData(*str++);
}

void lcdSetCursor(unsigned char row, unsigned char col) {
    lcdCommand((row == 0 ? 0x80 : 0xC0) + col);
}

void triggerAlert() {
    PORTB |= (1 << PB0) | (1 << PB1);//led buzzer
    _delay_ms(300);
    PORTB &= ~((1 << PB0) | (1 << PB1));
}


ISR(INT0_vect) {
    _delay_ms(50);

    if (exitQueue > 0) {
        
        if (count > 0) count--;
        alertFlag = 1;
        lastActionFlag = 2; 
        exitQueue--;       
    } else {
        
        count++;
        alertFlag = 1;
        lastActionFlag = 1;
    }
}


ISR(INT1_vect) {
    _delay_ms(50); 
    exitQueue++;       
    lastActionFlag = 3;
}


void intToStr(int num, char *buf) {
    int i=0,j,rem;
    char temp[5];
    if(num==0){ buf[0]='0'; 
               buf[1]='\0'; 
               return; }
    while(num!=0){
        rem=num%10;
        temp[i++]=rem+'0';
        num/=10;
    }
    for(j=0;j<i;j++) buf[j]=temp[i-j-1];//rev
    buf[i]='\0';
}

//previo int 
void setup() {
    DDRD &= ~((1 << PD2) | (1 << PD3));
    DDRB |= (1 << PB0) | (1 << PB1);    
    PORTD |= (1 << PD2) | (1 << PD3);   
    EICRA |= (1 << ISC01) | (1 << ISC00); 
    EICRA |= (1 << ISC11) | (1 << ISC10); 
    EIMSK |= (1 << INT0) | (1 << INT1);
    sei();
    lcdInit();
}


void loop() {
    if(alertFlag){
        triggerAlert();
        alertFlag=0;
    }


    lcdSetCursor(0,0);
    lcdPrint("Person Count:");
    lcdSetCursor(0,15);
    char buf[5];
    intToStr(count,buf);//covert to str
    lcdPrint(buf);

    
    lcdSetCursor(1,0);
    lcdPrint("                ");
    lcdSetCursor(1,0);
    if(lastActionFlag==1) lcdPrint("Person Entry G1");
    else if(lastActionFlag==2) lcdPrint("Person Exit G1");
    else if(lastActionFlag==3) lcdPrint("Person left G2");
   
    _delay_ms(200);
}