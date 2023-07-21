@Actividad 03
	.data
	.balign 4
string1: .asciz "Give the value of X \n"
string2: .asciz "Result = %d\n"
format:	 .asciz "%d"
x:	.word 0

.text
.global main
.extern printf

main:	push	{ip,lr}

@imprimimos mensaje
	ldr r0,=string1
	bl  printf

@Leemos entrada
	ldr r0,=format	@leemos entrada
	ldr r1,=x
	bl scanf

@Realizamos operacion
	ldr r4,=x	@obtenemos direccion de x
	ldr r1,[r4]	@Obtenemos valor de x
	
    @OP x^2	
	mul r2,r1,r1	@Gardamos el resultado en r0, y multiplicamos r0*r0
	ldr r0,=format
	
    @OP 6*x^2
	ldr r7,=#6	@Damos el valor de 6 a otro registro
	mul r3,r2,r7	@GUardamos en R3
	
    @OP 9*x
	ldr r7,=#9
	mul r5,r7,r1	@Guardamos en R5 el 9*x
	
    @Op 6*x^2+9*x
	add r1, r5,r3  	@GUardamos en r1, la suma de R5 Y R3

    @Añadimos + 2 al resultado
	ldr r9,=#2	@Guardamos el 2 en R9
	add r1,r1,r9

@Desplegamos resultado

	ldr r0,=string2
	@str r1,[r1]
	bl printf

pop	{ip,pc}
