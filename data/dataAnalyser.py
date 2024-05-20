import numpy as np
import matplotlib.pyplot as plt

np.posCaretsian = []
with open('./data/positionDataCaretsian.txt', 'r') as file:
    for line in file:
        np.posCaretsian.append([float(number) for number in line.split()])

np.posSpherical = []
with open('./data/positionDataCaretsian.txt', 'r') as file:
    for line in file:
        np.posSpherical.append([float(number) for number in line.split()])

np.timeData = []
with open('./data/timeData.txt', 'r') as file:
    for line in file:
        np.timeData.append([float(number) for number in line.split()])

i = 0
np.posCaretsianX = []
np.posCaretsianY = []
np.posCaretsianZ = []
np.posSphericalR = []
for i in range (0, len(np.posCaretsian) - 1):
    if np.posSpherical[i][0] < 10:
        np.posCaretsianX.append(np.posCaretsian[i][0])
        np.posCaretsianY.append(np.posCaretsian[i][1])
        np.posCaretsianZ.append(np.posCaretsian[i][2])
        np.posSphericalR.append(np.posSpherical[i][0])
    else:
        if i % 10 == 0:
            np.posCaretsianX.append(np.posCaretsian[i][0])
            np.posCaretsianY.append(np.posCaretsian[i][1])
            np.posCaretsianZ.append(np.posCaretsian[i][2])
            np.posSphericalR.append(np.posSpherical[i][0])

## XY plot
fig = plt.figure()
ax = fig.add_subplot()

plt.xlabel("X")
plt.ylabel("Y")
ax.set_xlim(-100, 100)
ax.set_ylim(-100, 100)

# ax.axhline(0, color='yellow')
# ax.axvline(0, color='yellow')

eventHorizon = plt.Circle((0, 0), 2, color='b', fill=False)

ax.add_patch(eventHorizon)
ax.plot(np.posCaretsianX, np.posCaretsianY)
plt.savefig("./data/posCaretsianXY")
plt.close()

## XZ plot
fig = plt.figure()
ax = fig.add_subplot()

plt.xlabel("X")
plt.ylabel("Z")
ax.set_xlim(-100, 100)
ax.set_ylim(-100, 100)

# ax.axhline(0, color='yellow')
# ax.axvline(0, color='yellow')
eventHorizon = plt.Circle((0, 0), 2, color='b', fill=False)
ax.add_patch(eventHorizon)
ax.plot(np.posCaretsianX, np.posCaretsianZ)
plt.savefig("./data/posCaretsianXZ")
plt.close()

## YZ plot
fig = plt.figure()
ax = fig.add_subplot()

plt.xlabel("Y")
plt.ylabel("Z")
ax.set_xlim(-100, 100)
ax.set_ylim(-100, 100)
# ax.axhline(0, color='yellow')
# ax.axvline(0, color='yellow')
eventHorizon = plt.Circle((0, 0), 2, color='b', fill=False)

ax.add_patch(eventHorizon)
ax.plot(np.posCaretsianY, np.posCaretsianZ)
plt.savefig("./data/posCaretsianYZ")
plt.close()

# ## TR plot
# fig = plt.figure()
# ax = fig.add_subplot()

# ax.set_xlim(-100, 100)
# ax.set_ylim(-100, 100)
# ax.axhline(1, color='yellow')

# ax.plot(np.posSphericalR, np.timeData)
# plt.savefig("./data/deltaTimeVsRadious")
# plt.close()

