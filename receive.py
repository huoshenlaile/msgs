from curses import baudrate
import serial
import time

# read binary data from serial port and write it to a file


def receive(ser, file_name):
    with open(file_name, 'wb') as f:
        #        ser = serial.Serial(port, baudrate=baudrate)
        while True:
            data = ser.read(1)
            if data:
                f.write(data)
            else:
                break

# check if a serial port has data to read


def check_serial(ser):
    if ser.in_waiting > 0:
        return True
    else:
        return False


def read_info(ser):
    stream = ''
    while stream[-3:] != 'ACK':
        try:
            stream += ser.read(1).decode('utf-8')
        except Exception as e:
            stream += ' '
    # print(stream)
    s = 'ACK'
    while s[-3:] != 'END':
        s = s + ser.read(1).decode('utf-8')
    return s.strip()


try:
    cam = serial.Serial(port='com3', baudrate=921600, parity=serial.PARITY_NONE,
                        stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=1)
    print('COM open Success')
except Exception as e:
    print(e)
    print('COM open Fail')

print('waiting')
time.sleep(1)
print('start send taking picture signal')

take_photo = b'\x10'
cam.write(take_photo)
cam.flush()

time.sleep(0.5)


info = ''
while info.strip() != 'ACK CMD START TRANSMIT END':
    info = read_info(cam)
    print(info)

# print('number of bytes')
# ll = cam.read(8).decode('utf-8')
# print(ll)

time.sleep(0.5)


receive(cam, 'photo.jpg')
print('photo.jpg saved')
