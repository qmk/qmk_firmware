/*
 * To run this test program, link p9 to p10 so the Serial loops
 * back and receives characters it sends.
 */
#include "mbed.h"
#include "MODSERIAL.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

MODSERIAL pc(USBTX, USBRX);

/*
 * As experiement, you can define MODSERIAL as show here and see what
 * effects it has on the LEDs.
 *
 * MODSERIAL uart(TX_PIN, RX_PIN, 512);
 *   With this, the 512 characters sent can straight into the buffer
 *   vary quickly. This means LED1 is only on briefly as the TX buffer
 *   fills.
 *
 * MODSERIAL uart(TX_PIN, RX_PIN, 32);
 *   With this, the buffer is smaller than the default 256 bytes and
 *   therefore LED1 stays on much longer while the system waits for
 *   room in the TX buffer.
 */
MODSERIAL uart(p9, p10);

// This function is called when a character goes from the TX buffer
// to the Uart THR FIFO register.
void txCallback(MODSERIAL_IRQ_INFO *q) {
    led2 = !led2;
}

// This function is called when TX buffer goes empty
void txEmpty(MODSERIAL_IRQ_INFO *q) {
    led2 = 0;
    pc.puts(" Done. ");
}

// This function is called when a character goes into the RX buffer.
void rxCallback(MODSERIAL_IRQ_INFO *q) {
    led3 = !led3;
    pc.putc(uart.getc());
}

int main() {
    int c = 'A';

    // Ensure the baud rate for the PC "USB" serial is much
    // higher than "uart" baud rate below. (default: 9600)
    // pc.baud(9600);

    // Use a deliberatly slow baud to fill up the TX buffer
    uart.baud(1200);

    uart.attach(&txCallback, MODSERIAL::ModTxIrq);
    uart.attach(&rxCallback, MODSERIAL::ModRxIrq);
    uart.attach(&txEmpty,    MODSERIAL::ModTxEmpty);

    // Loop sending characters. We send 512
    // which is twice the default TX/RX buffer size.

    led1 = 1; // Show start of sending with LED1.

    for (int loop = 0; loop < 512; loop++) {
        uart.printf("%c", c);
        c++;
        if (c > 'Z') c = 'A';
    }

    led1 = 0; // Show the end of sending by switching off LED1.

    // End program. Flash LED4. Notice how LED 2 and 3 continue
    // to flash for a short period while the interrupt system
    // continues to send the characters left in the TX buffer.

    while(1) {
        led4 = !led4;
        wait(0.25);
    }
}

/*
 * Notes. Here is the sort of output you can expect on your PC/Mac/Linux host
 * machine that is connected to the "pc" USB serial port.
 *
 * ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUV
 * WXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQR
 * STUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMN
 * OPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJ
 * KLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEF
 * GHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZAB
 * CDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQ Done. R
 *
 * Of interest is that last "R" character after the system has said "Done."
 * This comes from the fact that the TxEmpty callback is made when the TX buffer
 * becomes empty. MODSERIAL makes use of the fact that the Uarts built into the
 * LPC17xx device use a 16 byte FIFO on both RX and TX channels. This means that
 * when the TxEmpty callback is made, the TX buffer is empty, but that just means
 * the "last few characters" were written to the TX FIFO. So although the TX
 * buffer has gone empty, the Uart's transmit system is still sending any remaining
 * characters from it's TX FIFO. If you want to be truely sure all the characters
 * you have sent have left the Mbed then call txIsBusy(); This function will
 * return true if characters are still being sent. If it returns false after
 * the Tx buffer is empty then all your characters have been sent.
 *
 * In a similar way, when characters are received into the RX FIFO, the entire
 * FIFO contents is moved to the RX buffer, assuming there is room left in the
 * RX buffer. If there is not, any remaining characters are left in the RX FIFO
 * and will be moved to the RX buffer on the next interrupt or when the running
 * program removes a character(s) from the RX buffer with the getc() method.
 */
