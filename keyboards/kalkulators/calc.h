#ifndef CALC_H
#define CALC_H

void countDigitsAndDecimalPlaces(double input, int *wholeDigits, int *decimalPlaces);
void reset_states(void);
void reset_states_after_enter(void);
void display_result(const char* text);
void display_final_result(void);
void into_current_input(double input);
void equals_operation(void);
void plus_operation(void);
void minus_operation(void);
void multiply_operation(void);
void divide_operation(void);
void clear_operation(void);
void process_input(double input);


#endif