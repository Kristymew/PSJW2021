https://www.youtube.com/watch?v=_almRz0_m9g to see splitting functions into .h and .c files

Distance traveled = Wheel rotations * circumference = 
(encoder ticks / counts per revolution) * circumference
diameter wheel = 39mm

encoders provide a resolution of 12 counts per revolution of the motor shaft when counting both channels.
to compute the counts per revolution of the drive sprockets, multiply the gearboxes' gear ratio by 12.
100:37:1 = 100.37 x 12 = 1204.44 CPR (counts per revolution)

encoder ticks = read from left and right encoder
CPR = 1204.44 ~1204
circumference = pi*3.9cm = 12.2522113490 ~12
Distance = (encoder ticks / 1204.44) * 12

Quadrature encoder transitions are often detected by monitoring both encoder channels directly. However, since
transitions on the Zumo’s encoders can occur at high frequencies (several thousand per second) when its motors
are running, it is necessary to use the AVR’s pin change interrupts or external interrupts to read the encoders.
	
PE6		Reads the right encoder XORed signal		external interrupt INT6				Digital pin 7
PB4		Reads the left encoder XOred signal		pin change interrupt PCINT4			Digital pin 8
PF0		Reads the right encoder channel B												Digital pin 23 (analog pin 5)
PE2		Reads the left encoder channel B
