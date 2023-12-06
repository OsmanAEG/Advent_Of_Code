def decoder(line):
  digits = ''.join([c for c in line if c.isdigit()])
  final  = digits[0] + digits[-1]
  return int(final)

calibration_file = open('input.txt', 'r')
calibration_vals = calibration_file.readlines()

sum = 0

for line in calibration_vals:
  sum += decoder(line)

print(sum)