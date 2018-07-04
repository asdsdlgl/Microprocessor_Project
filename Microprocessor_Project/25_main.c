#include <xc.h>
#include <pic18f4520.h>
#include <stdlib.h>
#include <stdint.h>

#pragma config OSC = INTIO67   // Oscillator Selection bits (HS oscillator)
#pragma config WDT = OFF  // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRT = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON  // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF   // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF   // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config PBADEN = OFF
#pragma config MCLRE = ON

//////////////////////////////////////////////

//////////////////////////////////////////////

 #define _XTAL_FREQ 20000000
uint8_t arr[8][8] = {};
uint8_t over_dis[8][78] = {
    {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,0,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,1,1,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,1,1,1,1,1,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,1,1,1,1,1,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,0,0,1,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,1,0,0,0,1,0,0,1,0,0,0,0,0,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0}};
uint8_t temper[8][24] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
};
uint8_t one[8][4] = {
    {0,0,0,0},
    {0,0,1,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,0},
    {0,1,1,1}
};
uint8_t two[8][4] = {
    {0,0,0,0},
    {0,1,1,1},
    {0,0,0,1},
    {0,0,0,1},
    {0,1,1,1},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,1,1}
};
uint8_t three[8][4] = {
    {0,0,0,0},
    {0,1,1,1},
    {0,0,0,1},
    {0,0,0,1},
    {0,1,1,1},
    {0,0,0,1},
    {0,0,0,1},
    {0,1,1,1}
};
uint8_t four[8][4] = {
    {0,0,0,0},
    {0,1,0,1},
    {0,1,0,1},
    {0,1,0,1},
    {0,1,1,1},
    {0,0,0,1},
    {0,0,0,1},
    {0,0,0,1}
};
uint8_t five[8][4] = {
    {0,0,0,0},
    {0,1,1,1},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,1,1},
    {0,0,0,1},
    {0,0,0,1},
    {0,1,1,1}
};
uint8_t six[8][4] = {
    {0,0,0,0},
    {0,1,1,1},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,1,1},
    {0,1,0,1},
    {0,1,0,1},
    {0,1,1,1}
};
uint8_t seven[8][4] = {
    {0,0,0,0},
    {0,1,1,1},
    {0,1,0,1},
    {0,1,0,1},
    {0,0,0,1},
    {0,0,0,1},
    {0,0,0,1},
    {0,0,0,1}
};
uint8_t eight[8][4] = {
    {0,0,0,0},
    {0,1,1,1},
    {0,1,0,1},
    {0,1,0,1},
    {0,1,1,1},
    {0,1,0,1},
    {0,1,0,1},
    {0,1,1,1}
};
uint8_t nine[8][4] = {
    {0,0,0,0},
    {0,1,1,1},
    {0,1,0,1},
    {0,1,0,1},
    {0,1,1,1},
    {0,0,0,1},
    {0,0,0,1},
    {0,1,1,1}
};
uint8_t zero[8][4] = {
    {0,0,0,0},
    {0,1,1,1},
    {0,1,0,1},
    {0,1,0,1},
    {0,1,0,1},
    {0,1,0,1},
    {0,1,0,1},
    {0,1,1,1}
};
int k= 0;

void move_up(int x, int y);
void move_down(int x, int y);
void move_left(int x, int y);
void move_right(int x, int y);
void init();
void select();
void game1();
void game2();
void game3();
void gameover();
void score_tens(int s);
void score_digit(int s);

void MyadcInit();
void MyadcRead();
void game3_adc_temperature();
void print_temper();
int tmp = 0, record = 0,tmp1 = 0, choose, score = 0;
int up = 1, down = 0, right = 0, left = 0;
int head_i, head_j, tail_i, tail_j, length;
int food_i, food_j;
int food_num = 1;
int game_mode = 0, game_over = 0;
unsigned int MyadcValue;
unsigned int t;
int count;
int center_i,center_j;
void main(void) {
    RCONbits.IPEN = 0x01;
    PIE1bits.TMR1IE = 1;
    IPR1bits.TMR1IP = 1;
    PIR1bits.TMR1IF = 0;
    INTCONbits.GIE = 1;
    INTCONbits.GIEL = 1;
    T1CON = 0x95;
    TMR1 = 3035;
    ////////////////////////////INT0
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    TRISBbits.RB2 = 1;
    RCONbits.IPEN = 1;
    INTCONbits.INT0IE = 1;
    INTCONbits.INT0IF = 0;
    INTCON2bits.INTEDG0 = 1;
    //////////////////////
    INTCON3bits.INT1IE = 1;
    INTCON3bits.INT1IF = 0;
    INTCON2bits.INTEDG1 = 1;
    INTCON3bits.INT1IP = 1;

    INTCON3bits.INT2IE = 1;
    INTCON3bits.INT2IF = 0;
    INTCON2bits.INTEDG2 = 1;
    INTCON3bits.INT2IP = 1;
    //////////////////////
    //TRISB = 0b00100000; 
    TRISBbits.RB5 = 1;
    INTCONbits.RBIE = 1;
    INTCON2bits.RBIP = 1;
    INTCONbits.RBIF = 0;
    INTCON2bits.RBPU = 1;
    
    MyadcInit();
    //===============================================================================
    int p = 0;
    int i = 0;
    int j = 0;
    TRISD = 0;
    TRISC = 0;
    //=================================================================================
    srand(1);
    init();
    while (1) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if (arr[i][j] != 0) {
                    LATC = 1 << i;
                    LATD = ~(1 << j);
                    __delay_us(1);
                    LATC = 0;
                    LATD = 0xff;
                }
            }
        }
        if (game_mode ==1 && food_num == 0) {
            while (1) {
                food_i = rand() % 8;
                food_j = rand() % 8;
                if (arr[food_i][food_j] == 0) {
                    arr[food_i][food_j] = 6;
                    food_num = 1;
                    break;
                }
            }
        }
    }
    //return;
}

void interrupt tc_int(void) {

    int b = PORTBbits.RB4;
    
    b = PORTBbits.RB0;
    b = PORTBbits.RB1;
    b = PORTBbits.RB2;
    if (game_mode == 0) {
        select();
    }
    if (game_mode == 1) {
        game1();
    }
    if (game_mode == 2) {
        game2();
    }
    if(game_mode == 3) {
        print_temper();
    }
    INTCONbits.RBIF = 0;
    INTCONbits.INT0IF = 0;
    INTCON3bits.INT1IF = 0;
    INTCON3bits.INT2IF = 0;
}

void init() {
    //init
    LATC = 0x00;
    LATD = 0xff;
    // int up,down,right,left;
    int i, j;
    for(i = 0; i < 8; i++)
       for(j = 0; j < 8; j++)
           arr[i][j] = 0;
    score = 0;
    if (game_mode == 0) {
        choose = 1;
        tmp = 0;
    } else if (game_mode == 1) {
        PIE1bits.TMR1IE = 1;
        food_num = 0;
        arr[0][0] = 5;
        head_i = 0;
        head_j = 0;
        tail_i = 0;
        tail_j = 0;
    } else if (game_mode == 2){
        PIE1bits.TMR1IE = 1;
        arr[7][3] = 1;
        arr[7][4] = 1;
        arr[7][5] = 1;
        arr[6][4] = 1;
        center_i = 7;
        center_j = 4;
        for(int j = 0;j<8;j++) {
            arr[0][j] = 2;
        }
    } else if (game_mode == 3){
        game3_adc_temperature();
    }
    //gameover();
    //game_mode = 0;
    
}

void select(){
    int i ,j;
    PIE1bits.TMR1IE = 0;
    if (INTCONbits.INT0IF == 1) {
        game_mode = choose;
        init();
        return;
    } else if (INTCON3bits.INT1IF == 1) {
        choose = (choose + 3) % 4;
        if (choose == 0)
            choose = 3;
    } else if (INTCON3bits.INT2IF == 1) {
        choose = (choose + 1) % 4;
        if (choose == 0)
            choose = 1;
    }
    if (choose == 0)
        choose++;
    if(choose != tmp){
        if (choose == 1) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j + 2] = one[i][3 - j];
        } else if (choose == 2) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j + 2] = two[i][3 - j];
        } else if (choose == 3) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j + 2] = three[i][3 - j];
        }
        tmp = choose;
    }
    //arr[0][choose] = 1;
    TMR1 = 3035;
    PIE1bits.TMR1IE = 1;
    PIR1bits.TMR1IF = 0;
}

void game1() {
    int i, j;
    if (PIR1bits.TMR1IF) {
        PIE1bits.TMR1IE = 0;
        if (game_over == 1) { 
            tmp++;
            if (tmp > 71) {
                if(tmp == 72){
                    score_tens(score/10);
                    score_digit(score%10);
                }else if(tmp > 85){
                    game_over = 0;
                    game_mode = 0;
                    init();
                    tmp = 0;
                    record = 0;
                }
                TMR1 = 33035;
                PIE1bits.TMR1IE = 1;
                PIR1bits.TMR1IF = 0;
                return;
            } else {
                gameover();
            }
            TMR1 = 53035;
            PIE1bits.TMR1IE = 1;
            PIR1bits.TMR1IF = 0;
            return;
        }
        if (up == 1) { //up
            arr[head_i][head_j] = 1;
            head_i = (head_i + 7) % 8;
        } else if (down == 1) { //down
            arr[head_i][head_j] = 2;
            head_i = (head_i + 1) % 8;
        } else if (left == 1) { //left
            arr[head_i][head_j] = 3;
            head_j = (head_j + 1) % 8;
        } else if (right == 1) { //right
            arr[head_i][head_j] = 4;
            head_j = (head_j + 7) % 8;
        }
        if (arr[head_i][head_j] == 6) { //eat food
            score++;
            arr[head_i][head_j] = 5;
            food_num = 0;
            TMR1 = 3035;
            PIE1bits.TMR1IE = 1;
            PIR1bits.TMR1IF = 0;
            return;
        }
        if (arr[head_i][head_j] >= 1 && arr[head_i][head_j] <= 5) { //dead
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                    arr[i][j] = 7;
                }
            }
            TMR1 = 3035;
            game_over = 1;
            PIE1bits.TMR1IE = 1;
            PIR1bits.TMR1IF = 0;
            return;
        }
        arr[head_i][head_j] = 5;
        tmp = arr[tail_i][tail_j];
        arr[tail_i][tail_j] = 0;
        if (tmp == 1) { //up
            tail_i = (tail_i + 7) % 8;
        } else if (tmp == 2) { //down
            tail_i = (tail_i + 1) % 8;
        } else if (tmp == 3) { //left
            tail_j = (tail_j + 1) % 8;
        } else if (tmp == 4) { //right
            tail_j = (tail_j + 7) % 8;
        }

        TMR1 = 3035;
        PIE1bits.TMR1IE = 1;
        PIR1bits.TMR1IF = 0;
        return;
    } else if (INTCONbits.INT0IF == 1) {
        up = 1;
        down = 0;
        right = 0;
        left = 0;
        tmp++;
    } else if (INTCON3bits.INT1IF == 1 && right != 1) {
        up = 0;
        down = 0;
        right = 0;
        left = 1;
    } else if (INTCON3bits.INT2IF == 1 && left != 1) {
        up = 0;
        down = 0;
        right = 1;
        left = 0;
    }
}

void game2(){
    int i,j,temp;
    if (PIR1bits.TMR1IF) {
        PIE1bits.TMR1IE = 0;
        count++;
        if (game_over == 1) { 
            tmp++;
            if (tmp > 71) {
                if(tmp == 72){
                    score_tens(score/10);
                    score_digit(score%10);
                }else if(tmp > 85){
                    game_over = 0;
                    game_mode = 0;
                    count = 0;
                    init();
                    tmp = 0;
                    record = 0;
                }
                TMR1 = 33035;
                PIE1bits.TMR1IE = 1;
                PIR1bits.TMR1IF = 0;
                return;
            } else {
                gameover();
            }
            TMR1 = 53035;
            PIE1bits.TMR1IE = 1;
            PIR1bits.TMR1IF = 0;
            return;
        }
        if(count==5) {
            for(j=0;j<8;j++){
                if(arr[5][j]==2) {
                    game_over = 1;
                    TMR1 = 3035;
                    PIE1bits.TMR1IE = 1;
                    PIR1bits.TMR1IF = 0;
                    return;
                }
            }
            for(i=4;i>=0;i--) {
                for(j=0;j<8;j++) {
                    temp = arr[i][j];
                    arr[i+1][j] = temp;
                }
            }
            for(j = 0;j<8;j++) {
                if(rand()%2==1)
                    arr[0][j] = 2;
                else
                    arr[0][j] = 0;
            }
            count = 0;
        }
        TMR1 = 3035;
        PIE1bits.TMR1IE = 1;
        PIR1bits.TMR1IF = 0;
        return;
    } else if (INTCONbits.INT0IF == 1) {
        for(i = 6;i >= 0;i--) {
                if(arr[i][center_j]==2) {
                    score++;
                    arr[i][center_j] = 0;
                    break;
                }
            }
        return;
    } else if (INTCON3bits.INT1IF == 1) {
        arr[center_i-1][center_j] = 0;
        arr[center_i][(center_j+7)%8] = 0;
        center_j = (center_j+1)%8;
        arr[center_i][(center_j+1)%8] = 1;
        arr[center_i-1][center_j] = 1;
        return;
    } else if (INTCON3bits.INT2IF == 1) {
        arr[center_i-1][center_j] = 0;
        arr[center_i][(center_j+1)%8] = 0;
        center_j = (center_j+7)%8;
        arr[center_i][(center_j+7)%8] = 1;
        arr[center_i-1][center_j] = 1;
        return;
    }
    
}

void game3_adc_temperature() {
    int i,j;
    TMR1 = 23035;
    for(i=0;i<5;i++) {
        MyadcRead();
    }
    t = (MyadcValue*500)/1023;
    
    if( 20>t){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][4+j] =one[i][j];
            }
        }
    }
    else{
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][4+j] =two[i][j];
            }
        }
    }
    ////////////////////////////////////////////////////////////////////
    if(15.5>t&&t>=14.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =five[i][j];
                temper[i][4+j] =one[i][j];
            }
        }
    }
    else if(16.5>t&&t>=15.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =six[i][j];
                temper[i][4+j] =one[i][j];
            }
        }
    }
    else if(17.5>t&&t>=16.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =seven[i][j];
                temper[i][4+j] =one[i][j];
            }
        }
    }
    else if(18.5>t&&t>=17.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =eight[i][j];
                temper[i][4+j] =one[i][j];
            }
        }
    }
    else if(19.5>t&&t>=18.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =nine[i][j];
                temper[i][4+j] =one[i][j];
            }
        }
    }
    else if(20.5>t&&t>=19.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =zero[i][j];
                temper[i][4+j] = two[i][j];
            }
        }
    }
    else if(21.5>t&&t>=20.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =one[i][j];
                temper[i][4+j] =two[i][j];
            }
        }
    }
    else if(22.5>t&&t>=21.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =two[i][j];
                temper[i][4+j] =two[i][j];
            }
        }
    }
    else if(23.5>t&&t>=22.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =three[i][j];
                temper[i][4+j] =two[i][j];
            }
        }
    }
    else if(24.5>t&&t>=23.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =four[i][j];
                temper[i][4+j] =two[i][j];
            }
        }
    }
    else if(25.5>t&&t>=24.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =five[i][j];
                temper[i][4+j] =two[i][j];
            }
        }
    }
    else if(26.5>t&&t>=25.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =six[i][j];
                temper[i][4+j] =two[i][j];
            }
        }
    }
    else if(27.5>t&&t>=26.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =seven[i][j];
                temper[i][4+j] =two[i][j];
            }
        }
    }
    else if(28.5>t&&t>=27.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =eight[i][j];
                temper[i][4+j] =two[i][j];
            }
        }
    }
    else if(29.5>t&&t>=28.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =nine[i][j];
                temper[i][4+j] =two[i][j];
            }
        }
    }
    else if(30.5>t&&t>=29.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =zero[i][j];
                temper[i][4+j] =three[i][j];
            }
        }
    }
    else if(31.5>t&&t>=30.5){
        for(i=0;i<8;i++){
            for(j=0;j<4;j++){
                temper[i][8+j] =one[i][j];
                temper[i][4+j] =three[i][j];
            }
        }
    }
}

void print_temper(){
    if (PIR1bits.TMR1IF) {
        PIE1bits.TMR1IE = 0;
        tmp1++;
        int i, j;
        if(game_mode == 3){
            for(i = 0; i < 8; i++)
                for(j = 0; j < 8; j++)
                    arr[i][7 - j] = temper[i][j + tmp1];
        }
         if (tmp1 == 20) {
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                arr[i][j] = 0;
                }
            }
            tmp1 = 0;
            game_mode = 0;
            init();
        }
        
        TMR1 = 23035;
            PIE1bits.TMR1IE = 1;
            PIR1bits.TMR1IF = 0;
            return;
    }
}

void gameover(){
    int i, j;
    if(game_mode == 1||game_mode == 2){
        for(i = 0; i < 8; i++)
            for(j = 0; j < 8; j++)
                arr[i][7 - j] = over_dis[i][j + tmp];
    }
}

void score_tens(int s) {
    int i, j;
    if (s == 1) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j + 4] = one[i][3 - j];
    } else if (s == 2) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j + 4] = two[i][3 - j];
    } else if (s == 3) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j + 4] = three[i][3 - j];
     }else if (s == 4) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j + 4] = four[i][3 - j];
     }else if (s == 5) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j + 4] = five[i][3 - j];
     }else if (s == 6) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j + 4] = six[i][3 - j];
     }else if (s == 7) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j + 4] = seven[i][3 - j];
     }else if (s == 8) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j + 4] = eight[i][3 - j];
     }else if (s == 9) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j + 4] = nine[i][3 - j];
     }else if (s == 0) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j + 4] = zero[i][3 - j];
     }
}

void score_digit(int s) { 
    int i, j;
    if (s == 1) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j ] = one[i][3 - j];
    } else if (s == 2) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j ] = two[i][3 - j];
    } else if (s == 3) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j ] = three[i][3 - j];
    }else if (s == 4) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j ] = four[i][3 - j];
    }else if (s == 5) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j ] = five[i][3 - j];
    }else if (s == 6) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j ] = six[i][3 - j];
    }else if (s == 7) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j ] = seven[i][3 - j];
    }else if (s == 8) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j ] = eight[i][3 - j];
    }else if (s == 9) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j ] = nine[i][3 - j];
    }else if (s == 0) {
            for(i = 0; i < 8; i++)
                for(j = 0; j < 4; j++)
                    arr[i][j ] = zero[i][3 - j];
     }
}

void move_up(int x, int y) {
    arr[(x + 7) % 8][y] = arr[x][y];
}

void move_down(int x, int y) {
    arr[(x + 1) % 8][y] = arr[x][y];
}

void move_left(int x, int y) {
    arr[x][(y + 1) % 8] = arr[x][y];
}

void move_right(int x, int y) {
    arr[x][(y + 7) % 8] = arr[x][y];
}

void MyadcInit(){
    //TODO
    ADCON1bits.VCFG1 = 0 ;  //setting vref-
    ADCON1bits.VCFG0 = 0 ;  //setting vref+
    ADCON1bits.PCFG  = 0x0F ;  //Setting A/D Port Configuration Control
    ADCON0bits.CHS = 0 ;    //setting input channel
    TRISA =  0x01   ;         //setting port as input 
    ADCON2bits.ADFM = 0 ;    //setting ??? justified
    
    //setting acquisition time (ADCON2) ACQT 2:0
    //setting conversion time (ADCON2))
    ADCON2bits.ACQT = 0X001;
    ADCON2bits.ADCS = 0X000;
    ADCON0bits.ADON = 1;    //turn on ad module 
    /*setting adc interrupt 
     * 1.clear ADIF
     * 2.set ADIE
     * 3.SET GIE
    */
    return ;
}

void MyadcRead(){
    //waitting acquistion time
    /*start conversion 
     * 1.Set GO/DONE ADCON0
     * 2.ckeck GO/DONE (clear is setting finish)
     * 3.result in ADRESH"ADRESL
     */
    ADCON0bits.GO=1;
    while(ADCON0bits.GO)
    {
        MyadcValue = ADRESH*4 + ADRESL/64;
       
    }
}
