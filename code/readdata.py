import serial
import struct
import statistics as stat
import matplotlib.pyplot as plt
import matplotlib.animation as anim
from collections import deque

# Connect to the USB serial device
ser = serial.Serial('/dev/ttyUSB0')
ser.baudrate = 115200
ser.flushInput()

# Create the lambda and temp arrays for graphing
lamb = deque([0] * 100);
temp = deque([0] * 100);
pwmv = deque([0] * 100);
x = range(100);

# Create the plots
fig, ax1 = plt.subplots()

# Plot Lambda
ax1.set_xlabel('time (s)')
ax1.set_ylabel('Lambda (mLam)', color='tab:blue')
ax1.plot(x, lamb, color='tab:blue')
ax1.tick_params(axis='y', labelcolor='tab:blue')
ax1.set_ylim(0, 10200)

# Create a second axes
ax2 = ax1.twinx()
# Plot Temperature
ax2.set_ylabel('Temperature (C)', color='tab:red')
ax2.plot(x, temp, color='tab:red')
ax2.tick_params(axis='y', labelcolor='tab:red')
ax2.set_ylim(0, 1200)

# Create a third axes
ax3 = ax1.twinx()
# Plot Temperature
ax3.set_ylabel('PWM Vrms(V)', color='tab:green')
ax3.plot(x, pwmv, color='tab:green')
ax3.tick_params(axis='y', labelcolor='tab:green')
ax3.set_ylim(0, 12)
ax3.spines["right"].set_position(("axes", 1.2))
ax3.spines["right"].set_visible(True)

fig.tight_layout()
fig.show()

# Flush the serial input of buffered data
ser.flushInput()
# Graph data forever
while True:
    # Check for preamble
    while True:
        rdbytes = ser.read(1)
        if rdbytes == b'\xff':
            rdbytes = ser.read(1)
            if rdbytes == b'\xff':
                break
    # Read data
    rdbytes = ser.read(6)
    # Convert bytes to integers
    values = struct.unpack('<HHH', rdbytes)
    # Insert the lambda value into the array
    lamb.popleft()
    lamb.append(values[0]/1000)
    # Insert the temperature value into the array
    temp.popleft()
    temp.append(values[1])
    # Insert the PWM Vrms value into the array
    pwmv.popleft()
    pwmv.append(values[2]/1000)
    # Print the lambda value the temperature and the PWM Vrms
    print(values)
    # Clear the plots and replot
    ax1.cla()
    ax2.cla()
    ax3.cla()
    ax1.set_ylabel('Lambda Value', color='tab:blue')
    ax2.set_ylabel('Temperature (C)', color='tab:red')
    ax3.set_ylabel('PWM Vrms (V)', color='tab:green')
    ax1.plot(x, lamb, color='tab:blue')
    ax2.plot(x, temp, color='tab:red')
    ax3.plot(x, pwmv, color='tab:green')
    # Reset the axes
    ax1.set_ylim(0, max(lamb)+0.5)
    ax2.set_ylim(0, max(temp)+200)
    ax3.set_ylim(0, max(pwmv)+1)
    ax3.spines["right"].set_position(("axes", 1.2))
    ax3.spines["right"].set_visible(True)
    # Print imformation about each plot
    ax1.text(0.01, 0.04, 'Current Lambda: ' + str(lamb[-1]), verticalalignment='bottom', horizontalalignment='left', transform=ax2.transAxes, color='blue', fontsize=12)
    ax1.text(0.01, 0.01, 'Mean Lambda: ' + str(stat.mean(lamb)), verticalalignment='bottom', horizontalalignment='left', transform=ax2.transAxes, color='blue', fontsize=12)
    ax2.text(0.01, 0.13, 'Current Temp: ' + str(temp[-1]) + 'C', verticalalignment='bottom', horizontalalignment='left', transform=ax2.transAxes, color='red', fontsize=12)
    ax2.text(0.01, 0.10, 'Max Temp: ' + str(max(temp)) + 'C', verticalalignment='bottom', horizontalalignment='left', transform=ax2.transAxes, color='red', fontsize=12)
    ax2.text(0.01, 0.07, 'Min Temp: ' + str(min(temp)) + 'C', verticalalignment='bottom', horizontalalignment='left', transform=ax2.transAxes, color='red', fontsize=12)
    ax3.text(0.01, 0.16, 'Current PWM Vrms: ' + str(pwmv[-1]) + 'V', verticalalignment='bottom', horizontalalignment='left', transform=ax2.transAxes, color='green', fontsize=12)
    # Draw the updated plot
    fig.canvas.draw()
    fig.canvas.flush_events()

