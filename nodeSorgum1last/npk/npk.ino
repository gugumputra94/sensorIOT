import time
import serial
from serial import rs485

from gpiozero import OutputDevice

#import RPi.GPIO as GPIO
#GPIO.setmode(GPIO.BCM)

ser = serial.Serial('/dev/ttyUSB0', baudrate=4800)
#ser.rs485_mode = rs485.RS485Settings(rts_level_for_tx=False, rts_level_for_rx=True)
print(ser)

rxData=[]
index=0
max_index=7
tim_ready=0

all = b'\x01\x03\x00\x1e\x00\x03\x65\xcd'
nitro = b'\x01\x03\x00\x1e\x00\x01\xe4\x0c'
phos = b'\x01\x03\x00\x1f\x00\x01\xb5\xcc'
kal = b'\x01\x03\x00\x20\x00\x01\x85\xc0'

#GPIO.setup(17, GPIO.OUT)
#GPIO.output(17, GPIO.LOW)

#GPIO.setup(27, GPIO.OUT)
#GPIO.output(27, GPIO.LOW)
#re = OutputDevice(17)
#de = OutputDevice(27)
while True:
    print("call",all)
#    GPIO.output(17, GPIO.HIGH)
#    GPIO.output(27, GPIO.HIGH)
#    re.on()
#    de.on()
    ser.write(all)
#    re.off()
#    de.off()
#    GPIO.output(17, GPIO.LOW)
#    GPIO.output(27, GPIO.LOW)
#    print("ser : ", ser.read(1))
    vals = []
    print(ser.inWaiting())
    for i in range(0,11):
        vals.append(ser.read(1))
        print(i, vals[i])
#    GPIO.output(17, GPIO.HIGH)
#    GPIO.output(27, GPIO.HIGH)
    print(vals)
    n = ((int.from_bytes(vals[3],'big')) << 8 ) + (int.from_bytes(vals[4],'big'))
    p = ((int.from_bytes(vals[5],'big')) << 8 ) + (int.from_bytes(vals[6],'big'))
    k = ((int.from_bytes(vals[7],'big')) << 8 ) + (int.from_bytes(vals[8],'big'))
    print("N:", n)
    print("P:",p)
    print("K:",k)
#    ser.flush()
#    GPIO.output(17, GPIO.LOW)
#    GPIO.output(27, GPIO.LOW)
    time.sleep(1)
