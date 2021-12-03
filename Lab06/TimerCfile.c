#include <stdio.h>
#include <stdint.h>

int main(){

    //PORT configuration for general-purpose PIN

        // LDR  R0, =0x41004400 //PORT Base Address
        uint32_t R0 = 0x41004400;

        // LDR  R1, =0b00000000 //config value
        uint32_t R1 = 0b00000000;

        // LDR  R2, =0x4E
        uint32_t R2 = 0x0000004E;

        uint32_t *ptrR0, *ptrR1, *ptrR2; // Pointer to R0, R1 and R2

        //Obtain the address of each variable
        ptrR0 = &R0;
        ptrR1 = &R1;
        ptrR2 = &R2;

        //Addresses
        printf("Adress of pointer R0 = %x \n", ptrR0);
        printf("Adress of pointer R2 = %x \n", ptrR2);

        // STRB R1, [R0, R2]	//PINCFG14
        // Mem[R0 + R2] = R1 
        uint8_t *ptrR0R2; //Pointer with not direction (1 byte = 2 Nibbles = 8 bits)
        ptrR0R2 = (uint8_t)ptrR0 + (uint8_t)ptrR2;
        printf("Adress of pointer R3 = R0 + R2 = %x \n", ptrR0R2);
        // LDR  R2, =0x00004000 //PA14 bit set position
        R2 = 0x00004000;
        printf("Adress of pointer R2 = %x \n", ptrR2);

        // STR  R2, [R0, #0x08] //DIRSET -- data direction as output
        ptrR0 = (uint32_t)ptrR0 + (uint32_t)0x08; //Update pointer R0
        printf("Adress of pointer R0 = R0 + 0x08 = %x \n", ptrR0);

        // Store R2 into prtR0 address
        *ptrR2 = R2;
        printf("Value of R2 = %x \n", *ptrR2);

    //TIMER configuration

        printf("    TEST CONFIGURATION \n");

        //Configure the POWER MANAGER to enable the TC3 module
        // LDR  R3, =0x40000400 //PM Base Address
        uint32_t R3 = 0x40000400;
        printf("Value of R3 = %x \n", R3);

        // LDR  R1, [R3, #0x20] //read register APBCMASK
        R1 = R3 + (uint32_t)0x20;
        printf("Value of R1 = %x \n", R1);

        // LDR  R4, =0x00000800 //mask value
        uint32_t R4 = 0x00000800;
        printf("Value of R4 = %x \n", R4);

        // ORRS R1, R1, R4  	//to set desired bit(s)
        // Bitwise OR operarion between R1 and R4, store in R1 < TURN ON FLAGS -STATUS- >
        R1 = R1 | R4;
        printf("Value of R1 = %x \n", R1);

        // STR  R1, [R3, #0x20] //APBCMASK
        // Save R1 into the (R3 + 20) Address
        uint32_t *ptrR3;
        ptrR3 = &R3; 
        printf("Address of R3 = %x \n", ptrR3);
        
        ptrR3 = (uint32_t)ptrR3 + (uint32_t)0x20;   // ptrR3 updated
        printf("New Address of R3 = R3 + 20 = %x \n", ptrR3);

        *ptrR3 = R1;    // Save the value of R1 into the address of R3 pointer 
        printf("Pointer ptrR3 value = %x, R1 = %x \n", *ptrR3, R1);


    //Configure the GENERIC CLOCK CONTROL used by the TC3 module

        // LDR  R3, =0x40000C00 //GCLK Base Address
        R3 = 0x40000C00;
        printf("Value of R3 = %x \n", R3);

        // LDR  R1, =0      	//config value
        R1 = 0;
        printf("Value of R1 = %x \n", R1);

        // STR  R1, [R3, #0x08] //GENDIV
        ptrR3 = (uint32_t)ptrR3 + (uint32_t)0x08; // Update Pointer R3
        printf("Value of Pointer R3 = %x \n", ptrR3);
        *ptrR3 = R1;    // Update the pointing value by ptrR3 with R1
        printf("Value of Pointing value by R3 = %x \n", *ptrR3);

        // LDR  R1, =0x10600	//config value
        R1 = 0x10600;
        printf("Value of R1 = %x \n", R1);

        // STR  R1, [R3, #0x04] //GENCTRL
        ptrR3 = (uint32_t)ptrR3 + (uint32_t)0x04;
        printf("Updated pointer R3 = %x \n", ptrR3);
        *ptrR3 = R1;    // Update the value pointed by ptrR3
        printf("Value pointed by R3 = %x \n", *ptrR3);

        // LDR  R1, =0x401B 	//config value
        R1 = 0x401B;
        printf("Value of R1 = %x \n", R1);

        // STRH R1, [R3, #0x02] //CLKCTRL
        // Store 16 bits, 4 Nibbles = 2 Bytes.
        ptrR3 = (uint32_t)ptrR3 + (uint32_t)0x02;
        printf("Updated pointer R3 = %x \n", ptrR3);
        *ptrR3 = (uint16_t)R1;
        printf("Value of pointed R3 = %x \n", *ptrR3);

    //Determine the initial count
    //Time = Toscillator * (2^TIMERMODE - COUNT) * Prescaler
    
        // LDR  R3, =0x42002C00 //TC3 Base Address
        R3 = 0x42002C00;
        printf("Value of R3 = %x \n", R3);

        // LDR  R6, =65307  	//initial count of the timer + 27 cycles
        uint32_t R6 = 65307;
        printf("Value of R6 = %x \n", R6);

        // STRH R6, [R3, #0x10] //COUNT          	
        ptrR3 = (uint32_t)ptrR3 + (uint32_t)0x10;
        printf("Value of ptrR3 = %x \n", ptrR3);

        *ptrR3 = (uint16_t)R6;
        printf("Value of pointer R3 = %x ", *ptrR3);

    //Configure the TC3 peripheral
        
        // LDR  R1, =0      	//config value
        R1 = 0;
        printf("Value of R1 = %x \n", R1);

        // STRH R1, [R3]    	//CTRLA
        *ptrR3 = (uint16_t)R1;
        printf("Value pointed by ptrR3 = %x \n", *ptrR3);


        // STRB R1, [R3, #0x05] //CTRLBSET
        ptrR3 = ptrR3 + 0x05;
        printf("*Value of ptrR3 = %x \n", ptrR3);
        *ptrR3 = (uint16_t)R1;
        printf("Value of *ptrR3 = %x \n", *ptrR3);

        // LDR  R5, =0x1    	//to clear OVF flag
        uint32_t R5 = 0x1;
        printf("Value of R5 = %x \n", R5);

        // STRB R5, [R3, #0x0E] //INTFLAG
        ptrR3 = ptrR3 + 0x0E;
        printf("Value of Address ptrR3 = %x \n", ptrR3);
        *ptrR3 = (uint8_t)R5;
        printf("Value of *ptrR3 = %x \n", *ptrR3);

    //Enabling the TC3 peripheral
       	// LDR  R1, [R3]    	//reads CTRLA
        R1 = R3;            // Store the address of the variable of R3
       	
        // LDR  R4, =0x2    	//mask value
        R4 = 0x2;
           
       	// ORRS R1, R1, R4  	//to set desired bit(s)
        R1 = R1 | R4;
        printf("Value of R1 = %x \n", R1);
       	
        // STRH R1, [R3]    	//CTRLA
        *ptrR3 = (uint16_t)R1;
}