#!/usr/bin/python

import serial
from sys import argv, stdin
import time

tty = argv[1]
commands = argv[2]

def open_connection():
	c = serial.Serial(tty, 9600)
	print "Connection:", c
	time.sleep(3)
	return c

def motor_move(conn, course, leftspeed, rightspeed, delay, sleep=1):
	conn.write('%u,%u,%u,%u\n' % (course, leftspeed, rightspeed, delay))
	print time.asctime(), conn.readline(),
	time.sleep(sleep)

def move_n_times_fw_and_bw(n, sleep=1):
	for i in range(n):
		motor_move(conn, 1, 600, 200, sleep)
		##time.sleep(sleep)
		motor_move(conn, 2, 600, 200, sleep)
		##time.sleep(sleep)

if __name__ == '__main__':
	conn = open_connection()
	print 'commands: "%s"' % (commands)
	if commands == '-':
		inFile = stdin
	else:
		inFile = open(commands)
	for ln in inFile:
		course, left_speed, right_speed, delay = ln.split()
		course, left_speed, right_speed, delay = int(course), int(left_speed), int(right_speed), int(delay)
		motor_move(conn, course, left_speed, right_speed, delay)
		
		
