#include QMK_KEYBOARD_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "halconf.h"
#include "tm1638.h"
#include "usb_util.h"
#include "wait.h"
#include "calc.h"


// calculate the number of whole digits and decimal digits in a double
void countDigitsAndDecimalPlaces(double input, int *wholeDigits, int *decimalPlaces) {
    // Convert double to string
    char inputString[32];  // Adjust the size based on your needs
    snprintf(inputString, sizeof(inputString), "%f", input);

    // Remove trailing zeros
    char* end = inputString + strlen(inputString) - 1;
    while (*end == '0') {
        *end-- = '\0';
    }

    // Initialize counts
    *wholeDigits = 0;
    *decimalPlaces = 0;
    int decimalFound = 0;

    // Skip the negative sign if present
    int startIdx = (inputString[0] == '-') ? 1 : 0;

    // Iterate through each character in the modified input string
    for (int i = startIdx; i < strlen(inputString); i++) {
        if (isdigit((unsigned char)inputString[i])) {
            if (!decimalFound) {
                (*wholeDigits)++; // Increment count of whole digits
            } else {
                (*decimalPlaces)++; // Increment count of decimal places
            }
        } else if (inputString[i] == '.') {
            decimalFound = 1; // Decimal point is found
        } else {
            // Break the loop if a non-digit or non-decimal point character is encountered
            break;
        }
    }
}

enum custom_keycodes {
  KC_cl = QK_USER,   
  KC_div, 
  KC_times, 
  KC_minus,
  KC_seven,   
  KC_eight,   
  KC_nine,
  KC_four,   
  KC_five,   
  KC_six,   
  KC_plus,
  KC_one,   
  KC_two,   
  KC_three,
  KC_zero,   
  KC_dot,          
  KC_equals
};

typedef struct{
    double accumulator;
    char current_input[8];
} results;

results number = {0, ""};

typedef struct{
    bool dp_pressed;
    bool operator_pressed;
    bool input_start;
    bool negative_number;
    bool nonzero_pressed;
    bool waiting_for_operator;
    bool plus_operator_pressed;
    bool minus_operator_pressed;
    bool multiplication_operator_pressed;
    bool division_operator_pressed;
    bool operator_pressed_first_time;
    bool enter_pressed;
} operations;

operations operation_state = {false, false, true, false, false, false, false, false, false, false, true, false};

void reset_states(void){
    number.accumulator = 0;
    number.current_input[0] = '\0';


    operation_state.dp_pressed = false;
    operation_state.operator_pressed = false;
    operation_state.input_start = true;
    operation_state.negative_number = false;
    operation_state.nonzero_pressed = false;
    operation_state.waiting_for_operator = false;
    operation_state.plus_operator_pressed = false;
    operation_state.minus_operator_pressed = false;
    operation_state.multiplication_operator_pressed = false;
    operation_state.division_operator_pressed = false;
    operation_state.operator_pressed_first_time = true;
    operation_state.enter_pressed = false;
};

void reset_states_after_enter(void){
    number.current_input[0] = '\0';

    operation_state.dp_pressed = false;
    operation_state.operator_pressed = false;
    operation_state.input_start = true;
    operation_state.negative_number = false;
    operation_state.nonzero_pressed = false;
    operation_state.waiting_for_operator = true;
    operation_state.plus_operator_pressed = false;
    operation_state.minus_operator_pressed = false;
    operation_state.multiplication_operator_pressed = false;
    operation_state.division_operator_pressed = false;
    operation_state.enter_pressed = false;
};

// display a char on the 7seg display
void display_result(const char* text){
    reset();

    int x;
    sscanf(text, "%d", &x);
    print(text);

    if ((strcmp(text, "inf")==0) || ((x > 99999999))){
        displayText("Error   ");
        reset_states();
        return;
    }

    if (strchr(text, '.') == NULL) {
        displayTextRight(text);
    } else {
        displayTextRightFloat(text);
    }
}

void display_final_result(void){
    char output[10];
    int wholeDigits, decimalPlaces;
    countDigitsAndDecimalPlaces(number.accumulator, &wholeDigits, &decimalPlaces);
    snprintf(output, 10, "%*.*f", wholeDigits, decimalPlaces, number.accumulator);
    display_result(output);
}

void into_current_input(double input){

    char input_char[11];
    snprintf(input_char, sizeof(input_char), "%.0f", input);

    // limiting input to 8 digits
    if (strlen(number.current_input) + strlen(input_char) <= 8 && strchr(number.current_input, '.') == NULL) {
        strcat(number.current_input, input_char);
        display_result(number.current_input);
    }
    else if (strlen(number.current_input) + strlen(input_char) <= 9 && strchr(number.current_input, '.') != NULL){
        strcat(number.current_input, input_char);
        display_result(number.current_input);
    }
};

// equals
void equals_operation(void){
    if ((operation_state.plus_operator_pressed == true)){
        number.accumulator += atof(number.current_input);
        display_final_result();
        reset_states_after_enter();
    }
    else if ((operation_state.minus_operator_pressed == true)){
        number.accumulator -= atof(number.current_input);
        display_final_result();
        reset_states_after_enter();
    }
    else if ((operation_state.multiplication_operator_pressed == true)){
        number.accumulator *= atof(number.current_input);
        display_final_result();
        reset_states_after_enter();
    }
    else if ((operation_state.division_operator_pressed == true)){
        number.accumulator /= atof(number.current_input);
        display_final_result();
        reset_states_after_enter();
    }
};

void plus_operation(void){
    if (number.current_input[0] != '\0'){
        equals_operation();
        number.accumulator = number.accumulator + atof(number.current_input);
    }else{
        operation_state.operator_pressed_first_time = true;
    }
    reset();
    
    operation_state.plus_operator_pressed = true;
    operation_state.minus_operator_pressed = false;
    operation_state.multiplication_operator_pressed = false;
    operation_state.division_operator_pressed = false;
    number.current_input[0] = '\0';
    
    if (operation_state.operator_pressed_first_time == true){
        display_result("\0");
    }else{
        display_final_result();
    }

    operation_state.operator_pressed_first_time = false;

};

void minus_operation(void){
    if (number.current_input[0] != '\0'){
        equals_operation();
        number.accumulator = number.accumulator + atof(number.current_input);
    }else{
        operation_state.operator_pressed_first_time = true;
    }
    reset();
    operation_state.plus_operator_pressed = false;
    operation_state.minus_operator_pressed = true;
    operation_state.multiplication_operator_pressed = false;
    operation_state.division_operator_pressed = false;
    number.current_input[0] = '\0';
    
    if (operation_state.operator_pressed_first_time == true){
        display_result("\0");
    }else{
        display_final_result();
    }

    operation_state.operator_pressed_first_time = false;
};

void multiply_operation(void){
    if (number.current_input[0] != '\0'){
        equals_operation();
        number.accumulator = number.accumulator + atof(number.current_input);
    }else{
        operation_state.operator_pressed_first_time = true;
    }
    reset();
    operation_state.plus_operator_pressed = false;
    operation_state.minus_operator_pressed = false;
    operation_state.multiplication_operator_pressed = true;
    operation_state.division_operator_pressed = false;
    number.current_input[0] = '\0';
    
    if (operation_state.operator_pressed_first_time == true){
        display_result("\0");
    }else{
        display_final_result();
    }

    operation_state.operator_pressed_first_time = false;
};

void divide_operation(void){
    if (number.current_input[0] != '\0'){
        equals_operation();
        number.accumulator = number.accumulator + atof(number.current_input);
        
    }else{
        operation_state.operator_pressed_first_time = true;
    }
    reset();
    operation_state.plus_operator_pressed = false;
    operation_state.minus_operator_pressed = false;
    operation_state.multiplication_operator_pressed = false;
    operation_state.division_operator_pressed = true;
    number.current_input[0] = '\0';
    
    if (operation_state.operator_pressed_first_time == true){
        display_result("\0");
    }else{
        display_final_result();
    }

    operation_state.operator_pressed_first_time = false;
};

// clearing the display
void clear_operation(void){
    reset_states();
    reset();
    displayTextRight("0");
};

// processes input from the process_record_user function
void process_input(double input){

    // Reset states if enter key was pressed and a number is entered
    if (operation_state.enter_pressed == true && input < 10){
        reset_states();
        print("entered new calculations");
    }

    // handle number inputs
    if (input < 10){
        // handle so that multiple zeros can't be pressed at the start of writing
        if (operation_state.input_start == true && input == 0){
            into_current_input(input);
            operation_state.input_start = false;
        }
        else{
            if (input == 0){
                if (operation_state.nonzero_pressed){
                    into_current_input(input);
                    operation_state.waiting_for_operator = true;
                }
            }
            else{
                if ((strcmp(number.current_input, "0")==0)){
                    number.current_input[0] = '\0';
                }
                into_current_input(input);
                operation_state.input_start = false;  
                operation_state.nonzero_pressed = true;
                operation_state.waiting_for_operator = true;
            }
        }

    }

    // handle clearing
    else if (input == 777){
        number.accumulator = 0;
        number.current_input[0] = '\0';
        clear_operation();
        operation_state.enter_pressed = false; // Reset the flag
    }

    // handle decimal point
    else if ((operation_state.input_start == false) && (operation_state.dp_pressed == false) && (input == 111)){
        char buffer[2] = ".";
        strcat(number.current_input, buffer);

        display_result(number.current_input);

        operation_state.dp_pressed = true;
        operation_state.nonzero_pressed = true;
    }

    // handle summation
    else if (input == 333 && operation_state.waiting_for_operator == true){
        reset();
        plus_operation();
        operation_state.nonzero_pressed = false;
        operation_state.dp_pressed = false;
        operation_state.input_start = true;
        operation_state.enter_pressed = false; // Reset the flag
    }

    // handle minus
    else if (input == 444 && operation_state.waiting_for_operator == true){
        reset();
        minus_operation();
        operation_state.nonzero_pressed = false;
        operation_state.dp_pressed = false;
        operation_state.input_start = true;
        operation_state.enter_pressed = false; // Reset the flag
    }

    // handle multiplication
    else if (input == 555 && operation_state.waiting_for_operator == true){
        reset();
        multiply_operation();
        operation_state.nonzero_pressed = false;
        operation_state.dp_pressed = false;
        operation_state.input_start = true;
        operation_state.enter_pressed = false; // Reset the flag
    }

    // handle division
    else if (input == 666 && operation_state.waiting_for_operator == true){
        reset();
        divide_operation();
        operation_state.nonzero_pressed = false;
        operation_state.dp_pressed = false;
        operation_state.input_start = true;
        operation_state.enter_pressed = false; // Reset the flag
    }

    else if (input == 999){
        equals_operation();
        if (!operation_state.waiting_for_operator) {
            operation_state.enter_pressed = true; // Set the flag only if a valid calculation was performed
        }
    }

}


// listens for keypresses
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed){

        switch (keycode) {
 
        case KC_cl:
                process_input(777);
            break;
        case KC_div:
                process_input(666);
            break;
        case KC_times:
                process_input(555);
            break;
        case KC_minus:
                process_input(444);
            break;
        case KC_seven:
                process_input(7);
            break;
        case KC_eight:
                process_input(8);
            break;
        case KC_nine:
                process_input(9);
            break;
        case KC_four:
                process_input(4);
            break;
        case KC_five:
                process_input(5);
            break;
        case KC_six:
                process_input(6);
            break;
        case KC_plus:
                process_input(333);    
            break;
        case KC_one:
                process_input(1);
            break;
        case KC_two:
                process_input(2);
            break;
        case KC_three:
                process_input(3);
            break;
        case KC_zero:
                process_input(0);
            break;
        case KC_dot:
                process_input(111);
            break;
        case KC_equals:
                process_input(999);
                operation_state.enter_pressed = true;

            break;
        }
        return true;
    }

    return true;
};