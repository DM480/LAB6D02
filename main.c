
//***************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

//***************************

#ifdef DEBUG
void
_error_(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

//***************************
// Laboratorio 6 Semaforo
//***************************
int main(void){

    SysCtlClockSet(SYSCTL_SYSDIV_64|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    volatile uint32_t ui32Loop;
    int i, ban;

    // CONFIGURACIONES DE PINES

    //
    // Habilitamos el puerto GPIO que utilizamos para la LED (PUERTO F)
    //

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Verificamos que el acceso del periferico este habilitado
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    //
    // Habilitamos el pin GPIO para el LED
    // Se coloca como salida y habilitamos el pin DPIO como digital
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    while(1){

        // Antirebote

        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0){
            ban = 1;
        }
        else if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 16) {
            if(ban == 1){
                ban = 0;
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_3);
                SysCtlDelay(1000000);

                for (i = 0; i<5; i++){
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_3);
                    SysCtlDelay(200000);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
                    SysCtlDelay(200000);
                }

                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_1 | GPIO_PIN_3);
                SysCtlDelay(4000000);

                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_1);
                SysCtlDelay(4000000);
            }
        }
    }
}

