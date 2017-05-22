#include <msp430.h> 

/*
 * main.c
 */
int main(void) {

        WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

        P1DIR |= BIT0;          // Marca o LED em P1.0 como saida.
        P1OUT &= ~BIT0;         // Marca o LED como desligado para comessar certo.

        P4DIR |= BIT7;          // Marca o LED em P4.7 como saida.
        P4OUT &= ~BIT7;         // Marca o LED como desligado para comessar certo.

        P1DIR &= ~BIT1;         // Marca o pino P1.1 como entrada para S2.
        P1REN |= BIT1;          // Marca a entrada do pino P1.1 com resistor.
        P1OUT |= BIT1;         // Marca o resistor da entrada P1.1 como pulldown.

        P2DIR &= ~BIT1;         // Marca o pino P2.1 como entrada para S1.
        P2REN |= BIT1;          // Marca a entrada do pino P2.1 com resistor.
        P2OUT |= BIT1;         // Marca o resistor da entrada P2.1 como pulldown.

        P1IES &= ~BIT1;
        P1IFG &= ~BIT1;
        P1IE |= BIT1;

        P2IES &= ~BIT1;
        P2IFG &= ~BIT1;
        P2IE |= BIT1;

        __no_operation();
        __bis_SR_register( LPM4_bits+GIE );
        __no_operation();

    return 0;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
    switch ( __even_in_range( P1IV, P1IV_P1IFG7 )){
        case P1IV_P1IFG1:
            P1OUT ^= BIT0;
            __delay_cycles(40000);
            P1IFG &= ~BIT1;
            break;
        default:
            _never_executed();
    }
}
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void){
    switch (__even_in_range( P2IV, P2IV_P2IFG7 )){
            case P2IV_P2IFG1:
                P4OUT ^= BIT7;
                __delay_cycles(40000);
                P2IFG &= ~BIT1;
                break;
            default:
                _never_executed();
    }
}
