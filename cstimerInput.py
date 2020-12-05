import serial
import time
import keyboard
import win32gui

ser = serial.Serial('COM3', 9600)
time.sleep(5)
print("Ready!")
while True:
    currentWindow = win32gui.GetWindowText(win32gui.GetForegroundWindow())
    time.sleep(.1)
    input = int(ser.readline().decode()) / 1000

    if currentWindow[:7] == 'csTimer':
        keyboard.write(str(input))
        time.sleep(.25)
        keyboard.press_and_release('enter')

