#!/usr/bin/env python3
from ev3dev2.motor import OUTPUT_A, OUTPUT_B, SpeedPercent, MoveTank, LargeMotor
from ev3dev2.sensor import INPUT_1, INPUT_2, INPUT_3, INPUT_4
from ev3dev2.sensor.lego import LightSensor, UltrasonicSensor
from ev3dev2.sound import Sound
import math
from time import sleep

drive = MoveTank(OUTPUT_A, OUTPUT_B)    # Motorsteuerung
#arm = LargeMotor(OUTPUT_C)              # arm
us = UltrasonicSensor(INPUT_2)    
ls1 = LightSensor(INPUT_1)              # linker Lichtsensor
ls2 = LightSensor(INPUT_3)              # mittlerer Lichtsensor
ls3 = LightSensor(INPUT_4)              # rechter Lichtsensor
sound = Sound()
last_action = ""                        # letzte Fahraktion
active = True
speed = 100
wenden_speed = 60
middle_val = (ls1.reflected_light_intensity + ls2.reflected_light_intensity) / 2  # Initialisierung von middle value weil wir davor 40 hatten


def wenden():  # Wenden
    # drive.on_for_rotations(SpeedPercent(50), SpeedPercent(50), 1) # Rückwärts
    drive.on(SpeedPercent(-50), SpeedPercent(50))  # 180° drehen
    sleep(2)


def ziel():  # Ziel- Melodie abspielen
    global active
    drive.off() # anhalten
    # Hier noch einbauen dass er winkt und sich dreht
    # sound.play_file("sound.wav", volume=100)#, play_type=Sound.PLAY_NO_WAIT_FOR_COMPLETE)
    active = False  # Stoppt die  main while loop


def forward(speed: int):  # beide Motoren vorwärts fahren
    drive.on(SpeedPercent(-speed), SpeedPercent(-speed))


def right():  # Rechtskurve
    drive.on(SpeedPercent(-wenden_speed), SpeedPercent(0))


def left():  # Linkskurve
    drive.on(SpeedPercent(0), SpeedPercent(-wenden_speed))


def compare(l, m, r, d, t=5):
    avg = (l + m + r) / 3
    if math.isclose(l, m, abs_tol=5) and math.isclose(m, r, abs_tol=5):
        if d < 20:
            if avg >= middle_val - t:
                return "wenden"
            if avg < middle_val:
                return "ziel"
            else:
                pass
    if m < l - t and m < r - t:
        return "forward"

    if l < r - t:
        return "left"

    if r < l - t:
        return "right"
    return None



def interpret(x: str):
    global last_action
    if x == "forward":
        forward(speed)
        last_action = "forward"
    elif x == "right":
        right()
        last_action = "right"
    elif x == "left":
        left()
        last_action = "left"
    elif x == "ziel":
        drive.off()
        sleep(.5)
        if d < 20:
            ziel()
        else:
            forward()
    elif x == "wenden":
        wenden()
        last_action = "forward"
    else:
        if last_action == "right":
            right()
        elif last_action == "left":
            left()
        if last_action == "forward":
            forward(speed)


while True:
    r = ls1.reflected_light_intensity / 1.2
    m = ls2.reflected_light_intensity * 1.1
    l = ls3.reflected_light_intensity
    d = us.distance_centimeters - 4
    wert = compare(l, m, r, d)
    interpret(wert)
