/*
This is the modified version of [calculator by MWWorks](https://github.com/MWWorks/mw_calc_numpad/blob/master/calc.c). Below is the quote from [MWWorks](https://github.com/MWWorks).

   Calculator for QMK-based keyboard by MWWorks, https://mwworks.uk
   This is free, usual disclaimers, don't use it to calculate megaton yields, surgery plans, etc

   I did not plan to reinvent the wheel for this - I figured surely somebody somewhere has working calculator code?
   Found lots but none that actually work like you expect a calculator to, hence DIYing it

   As such, this is probably a bit janky, especially as I am a bit of a hack at C
   Seems to be working well, with occasional glitchs, solved by clearing it
   And some occasional floating-point issues - eg get a long decimal rather than the whole number you were expecting
   Feel free to fix it! I think it needs to detect the precision of the two operands and then figure out what the precision of the result should be

*/
#include <math.h>
#include "rubi.h"

static uint8_t calc_current_operand = 0;
static char calc_operand_0[CALC_DIGITS+1] = "";
static char calc_operand_1[CALC_DIGITS+1] = "";
char calc_result[CALC_DIGITS+1] = "";
static char calc_status[CALC_DIGITS+1] = "";
static char calc_operator = ' ';
static bool calc_reset = false;


void calcBegin(void){
}

//update display
void calcUpdate(void){
    if (calc_display_lines == 2) {
        if((calc_current_operand == 1) || (calc_reset)){
            strcpy(calc_status, calc_operand_0);
            if((strlen(calc_operand_0)>0) || (strlen(calc_operand_1)>0)){
                uint8_t len = strlen(calc_status);
                if (!(calc_operator == 's' || calc_operator == 'r' || calc_operator == 'n')) {
                    calc_status[len] = calc_operator;
                }
                calc_status[len+1] = 0;
                if(calc_reset
                        && !(calc_operator == 's' || calc_operator == 'r' || calc_operator == 'n')){
                    strncat(calc_status, calc_operand_1, CALC_DIGITS-strlen(calc_status));
                    calc_operator = ' ';
                }
            }
            strcpy(calc_status_display, calc_status);
        }
    } else if (calc_display_lines == 1) {
        if(calc_reset
                && !(calc_operator == 's' || calc_operator == 'r' || calc_operator == 'n')){
            calc_operator = ' ';
        }
    }
    calc_operator_display = calc_operator;
    strcpy(calc_result_display, calc_result);
}

//perform calculation on the 2 operands
void calcOperands(void){
    float result = 0;
    switch (calc_operator){

        //standard operators
        case '+':
            result = strtod(calc_operand_0, NULL) + strtod(calc_operand_1, NULL);
            break;

        case '-':
            result = strtod(calc_operand_0, NULL) - strtod(calc_operand_1, NULL);
            break;

        case '/':
            result = strtod(calc_operand_0, NULL) / strtod(calc_operand_1, NULL);
            break;

        case '*':
            result = strtod(calc_operand_0, NULL) * strtod(calc_operand_1, NULL);
            break;

            //single operand operators - these are all in 2
        case 's':
            result = sqrt(strtod(calc_operand_0, NULL));
            break;

        case 'r':
            result = 1/(strtod(calc_operand_0, NULL));
            break;

    }

    //now convert the float result into a string
    //we know the total string size but we need to find the size of the integer component to know how much we have for decimals
    uint8_t magnitude = ceil(log10(result));
    uint8_t max_decimals = CALC_DIGITS-magnitude-1;
    //but max it at 7 because that seems the useful limit of our floats
    if(max_decimals>7){
        max_decimals = 7;
    }
    dtostrf(result, CALC_DIGITS, max_decimals, calc_result);

    //now to clean up the result - we need it clean as it may be the input of next calculation
    //this seems a lot of code to format this string :| note that this c doesn't support float in sprintf
    uint8_t i;

    //first find if theres a dot
    uint8_t dotpos = CALC_DIGITS+1;
    for(i=0; i<strlen(calc_result); i++){
        if(calc_result[i] == '.'){
            dotpos = i;
            break;
        }
    }

    //if there is, work back to it and remove trailing 0 or .
    if(dotpos>=0){
        for(i=strlen(calc_result)-1; i>=dotpos; i--){
            if((calc_result[i] == '0') || (calc_result[i] == '.')){
                calc_result[i] = 0;
            }else{
                break;
            }
        }
    }

    //now find how many leading spaces
    uint8_t spaces = 0;
    for(i=0; i<strlen(calc_result); i++){
        if(calc_result[i] == ' '){
            spaces++;
        }else{
            break;
        }
    }

    //and shift the string
    for(i=0; i<strlen(calc_result)-spaces; i++){
        calc_result[i] = calc_result[i+spaces];
    }
    calc_result[strlen(calc_result)-spaces] = 0;

    calcUpdate();
    //the result is available as the first operand for another calculation
    strcpy(calc_operand_0, calc_result);
    calc_operand_1[0] = 0;

}

void calcInput(char input){
    char *operand = calc_operand_0;
    if(calc_current_operand == 1){
        operand = calc_operand_1;
    }
    uint8_t len = strlen(operand);

    if(
            ((input >= 48) && (input <= 57)) ||
            (input == '.')
      ){
        //if this is following an equals, then we start from scratch as if new calculation
        if(calc_reset == true){
            calc_reset = false;
            calc_current_operand = 0;
            calc_operand_0[0] = 0;
            calc_operand_1[0] = 0;
            operand = calc_operand_0;
            len = 0;
        }

        if(len<CALC_DIGITS){
            operand[len] = input;
            operand[len+1] = 0;
            strcpy(calc_result, operand);
            calcUpdate();
        }

        //special input to backspace
    }else if(input == 'x'){
        operand[len-1] = 0;
        strcpy(calc_result, operand);
        calcUpdate();

        //clear
    }else if(input == 'c'){
        operand[0] = 0;
        calc_operand_0[0] = 0;
        calc_operand_1[0] = 0;
        calc_operator = ' ';
        calc_reset = true;
        strcpy(calc_result, operand);
        calcUpdate();

        //special input switch neg/pos
    }else if((input == 'n') && (len>0)){
        uint8_t i;

        if(operand[0] == '-'){
            for(i=1; i<=len; i++){
                operand[i-1] = operand[i];
            }
        }else if(len<CALC_DIGITS){
            for(i=0; i<=len; i++){
                operand[len-i+1] = operand[len-i];
            }
            operand[0] = '-';
        }
        calc_operator = input;
        strcpy(calc_result, operand);
        calcUpdate();


        //standard 2 operand operators
    }else if((input == '+') || (input == '-') || (input == '*')  || (input == '/')){

        //get ready for second operand
        if(calc_current_operand == 0){
            calc_operator = input;
            calc_current_operand = 1;
            calcUpdate();

            //we pressed = we now expect a new second operand
        }else if(calc_reset){
            calc_operator = input;
            calc_reset = false;
            calc_operand_1[0] = 0;
            calcUpdate();

        }else {
            //if we use this on the second operand, calculate first, then ready for a second operand again
            if (strlen(calc_operand_1)>0){
                calcOperands();
            }
            calc_operand_1[0] = 0;
            calc_operator = input;
            calcUpdate();
        }


    }else if(input == '='){
        //only accept = if we are on the second operand
        if(calc_current_operand == 1){
            //keep the second operand for a subsequent press of =; but flag to reset if start entry of new operand
            calc_reset = true;
            calcOperands();
        }

        //single operands - square root and reciprocal - needs to operate on 0 so it works after a previous = result
    }else if((input == 's') || (input == 'r')){
        //but maybe we started entering 1
        if(calc_current_operand == 1 && !calc_reset){
            strcpy(calc_operand_0, calc_operand_1);
        }
        calc_current_operand = 1;
        calc_operand_1[0] = 0;
        calc_operator = input;
        calc_reset = true; //simulate another =
        calcOperands();

    }

}
