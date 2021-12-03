@PROBLEMA 1
@Part2E1
.data
.balign 4
y: .word 0	@Direccion objetivo

.text
.global main


main:
push {ip, lr}          @ push return address + dummy register for alignment
@Guardamos el dato 0xAAAAAAAA en Y
ldr r0, =y	       @ Guarda la direccion de Y en R0
ldr r1, =0xAAAAAAAA    @ Guarda en R1 el valor numerico
str r1,[r0]	       @ almacenamiento indirecto
@Guardamos el dato 0xBBBBBBBB en Y
ldr r1, =0xBBBBBBBB    @ Guarda en R1 el valor numerico
str r1,[r0]	       @ almacenamiento indirecto
@Guardamos el dato 0xCCCCCCCC en Y
ldr r1, =0xCCCCCCCC    @ Guarda en R1 el valor numerico
str r1,[r0]	       @ almacenamiento indirecto
pop    {ip, pc}          @ pop return address into pc