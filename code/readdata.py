import serial
import struct
import statistics as stat
import matplotlib.pyplot as plt
import matplotlib.animation as anim
from collections import deque

ser = serial.Serial('/dev/ttyUSB0')
ser.baudrate = 115200
ser.flushInput()

lamb = deque([0] * 100);
temp = deque([0] * 100);
x = range(100);

fig, ax1 = plt.subplots()

ax1.set_xlabel('time (s)')
ax1.set_ylabel('Lambda (mLam)', color='tab:blue')
ax1.plot(x, lamb, color='tab:blue')
ax1.tick_params(axis='y', labelcolor='tab:blue')
ax1.set_ylim(0, 10200)

ax2 = ax1.twinx()

ax2.set_ylabel('Temperature (C)', color='tab:red')
ax2.plot(x, temp, color='tab:red')
ax2.tick_params(axis='y', labelcolor='tab:red')
ax2.set_ylim(0, 1200)

fig.tight_layout()
fig.show()

ser.flushInput()
while True:
    rdbytes = ser.read(2)
    while rdbytes != b'\xff\xff':
        rdbytes = ser.read(2)
    rdbytes = ser.read(4)
    values = struct.unpack('<HH', rdbytes)
    lamb.popleft()
    lamb.append(values[0]/1000)
    temp.popleft()
    temp.append(values[1])
    print(values)
    ax1.cla()
    ax2.cla()
    ax1.set_ylabel('Lambda Value', color='tab:blue')
    ax2.set_ylabel('Temperature (C)', color='tab:red')
    ax1.plot(x, lamb, color='tab:blue')
    ax2.plot(x, temp, color='tab:red')
    ax1.set_ylim(0, max(lamb)+0.5)
    ax2.set_ylim(0, max(temp)+200)
    ax1.text(0.01, 0.07, 'Current Lambda: ' + str(lamb[-1]), verticalalignment='bottom', horizontalalignment='left', transform=ax2.transAxes, color='blue', fontsize=12)
    ax1.text(0.01, 0.01, 'Mean Lambda: ' + str(stat.mean(lamb)), verticalalignment='bottom', horizontalalignment='left', transform=ax2.transAxes, color='blue', fontsize=12)
    ax2.text(0.01, 0.10, 'Current Temp: ' + str(temp[-1]) + 'C', verticalalignment='bottom', horizontalalignment='left', transform=ax2.transAxes, color='red', fontsize=12)
    ax2.text(0.01, 0.04, 'Mean Temp: ' + str(stat.mean(temp)) + 'C', verticalalignment='bottom', horizontalalignment='left', transform=ax2.transAxes, color='red', fontsize=12)
    fig.canvas.draw()
    fig.canvas.flush_events()

