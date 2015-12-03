#!/opt/local/bin/python
import time
import serial
import sys

# configure the serial connections (the parameters differs on the device you are connecting to)
ser=serial.Serial(port="/dev/ttyACM0",baudrate=9600) # common usb port on mac
time.sleep(1.3)
ser.isOpen()

# print 'Enter your commands below.\nType "exit" to leave prompt.'
def arduino_input(input=None, sendCmd = False):
    if (sendCmd == True):
        # input = raw_input('>') # For Python 3 use input = input(">> ")
        if input == 'exit':
            ser.close()
            return "Closing..."
            exit()
        elif input != '':
	    print "Writing data to serial."
            ser.write(input + '\n')

    out = ''
    # let's wait 1 seconds before reading output (gives device time to return reply)
    time.sleep(1)
    while ser.inWaiting() > 0:
        out += ser.read(1)
    if out != '':
        return out.strip()
    else:
        return arduino_input()

ran=False
while 1:
    if ran == True:
	   sys.exit()
    if len(sys.argv) > 1:
        input = sys.argv[1]
	    ran=True
    else:
    	input = raw_input('>')
    if input.strip() == '':
        continue
    arduino_response = arduino_input(input,sendCmd = True)
    if arduino_response:
        if arduino_response == "exit":
            exit()
        elif arduino_response == "404":
            print "Invalid Command"
            sys.stdout.flush() # Without this constantly buffers and does not go to next line
        else:
            print arduino_response
            sys.stdout.flush()
