#!/usr/bin/python

def convert_raw_xyz(xyz):
  "Error handling included"
  "This converts gyroscope value to direction, speed and delay"
  "xyz: array of integers e.g. xyz = [10000,10000,0]"
  try:
    xyz = convert_xyz(xyz);
  except:
    xyz = [0,0,0,0]
    ##print "Fail";
  return ' '.join(map(str, xyz))
  
def convert_xyz(xyz):
  "This converts gyroscope value to direction, speed and delay"
  "xyz: array of integers e.g. xyz = [10000,10000,0]"
  threshold = 10000
  dir_speed_delay = [0,0,0,0]
  if (abs(xyz[0]) > threshold):
    "Value of x exeeds threshold value"
    if (xyz[0] > 0):
      ##print "Forward"
      dir_speed_delay = [1,100,100,500]
    else:
      ##print "Backward"
      dir_speed_delay = [2,100,100,500]
      
  elif (abs(xyz[1]) > threshold):
    if (xyz[1] > 0):
      ##print "Left"
      dir_speed_delay = [4,100,100,500]
    else:
      ##print "Right"
      dir_speed_delay = [3,100,100,500]
  elif (abs(xyz[2]) > threshold):
    ##print "Z axis: Do nothing"
    dir_speed_delay[2] = 0
  else:
    ##print "No relevantchange in input data"
    dir_speed_delay = [0,0,0,0];
  return dir_speed_delay

def tst():
	testarr = [20000,0,0];
	print convert_raw_xyz(testarr);
	testarr = [-20000,0,0];
	print convert_raw_xyz(testarr);
	testarr = [0,20000,0];
	print convert_raw_xyz(testarr);
	testarr = [0,-20000,0];
	print convert_raw_xyz(testarr);
	testarr = [0,0,20000];
	print convert_raw_xyz(testarr);
	print "\n Test some crap data";
	print convert_raw_xyz("sumcrap");

    
if __name__ == '__main__':
	from sys import stdin, stderr
	for ln in stdin:
		arr = map(int, ln.split())
		print >>stderr, 'ARR: %s' % (arr)
		print convert_raw_xyz(arr)

