import RPi.GPIO as GPIO
from time import sleep
import sys

# Assign GPIO pins for motor
motor_channel = (29, 31, 33, 35)

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)

# Set up the GPIO channels for output
GPIO.setup(motor_channel, GPIO.OUT)

# Ask user for motor direction
motor_direction = input('Select motor direction (a=anticlockwise, c=clockwise): ')

while True:
    try:
        if motor_direction == 'c':  # Clockwise
            print('Motor running clockwise\n')
            GPIO.output(motor_channel, (GPIO.HIGH, GPIO.LOW, GPIO.LOW, GPIO.HIGH))
            sleep(0.02)
            GPIO.output(motor_channel, (GPIO.HIGH, GPIO.HIGH, GPIO.LOW, GPIO.LOW))
            sleep(0.02)
            GPIO.output(motor_channel, (GPIO.LOW, GPIO.HIGH, GPIO.HIGH, GPIO.LOW))
            sleep(0.02)
            GPIO.output(motor_channel, (GPIO.LOW, GPIO.LOW, GPIO.HIGH, GPIO.HIGH))
            sleep(0.02)

        elif motor_direction == 'a':  # Anticlockwise
            print('Motor running anticlockwise\n')
            GPIO.output(motor_channel, (GPIO.HIGH, GPIO.LOW, GPIO.LOW, GPIO.HIGH))
            sleep(0.02)
            GPIO.output(motor_channel, (GPIO.LOW, GPIO.LOW, GPIO.HIGH, GPIO.HIGH))
            sleep(0.02)
            GPIO.output(motor_channel, (GPIO.LOW, GPIO.HIGH, GPIO.HIGH, GPIO.LOW))
            sleep(0.02)
            GPIO.output(motor_channel, (GPIO.HIGH, GPIO.HIGH, GPIO.LOW, GPIO.LOW))
            sleep(0.02)

    # Handle keyboard interrupt (Ctrl+C)
    except KeyboardInterrupt:
        motor_direction = input('Select motor direction (a=anticlockwise, c=clockwise, q=exit): ')
        
        # Check for exit condition
        if motor_direction == 'q':
            print('Motor stopped')
            sys.exit(0)
