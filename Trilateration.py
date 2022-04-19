import re
import math

def trilateration(receiver1, receiver2, receiver3, r1, r2, r3):
    unknownPosition = []
    
    #unit vector in a direction from point1 to point 2
    p2p1Distance = pow(pow(receiver2[0] - receiver1[0], 2) + pow(receiver2[1] - receiver1[1], 2), 0.5)
    exx = (receiver2[0] - receiver1[0]) / p2p1Distance
    exy = (receiver2[1] - receiver1[1]) / p2p1Distance
   
    #signed magnitude of the x component
    i = exx*(receiver3[0] - receiver1[0]) + exy*(receiver3[1] - receiver1[1]);

    #the unit vector in the y direction. 
    eyx = (receiver3[0] - receiver1[0] - i * exx) / pow(pow(receiver3[0] - receiver1[0] - i * exx, 2) + pow(receiver3[1] - receiver1[1] - i * exy, 2), 0.5)
    eyy = (receiver3[1] - receiver1[1] - i * exy) / pow(pow(receiver3[0] - receiver1[0] - i * exx, 2) + pow(receiver3[1] - receiver1[1] - i * exy, 2), 0.5)
    
    #the signed magnitude of the y component   
    j = eyx * (receiver3[0] - receiver1[0]) + eyy * (receiver3[1] - receiver1[1])
    
    #coordinates
    x = (pow(r1, 2) - pow(r2, 2) + pow(p2p1Distance, 2)) / (2 * p2p1Distance)
    y = (pow(r1, 2) - pow(r3, 2) + pow(i, 2) + pow(j, 2)) / (2*j) - i * x / j
    
    #result coordinates
    finalX = receiver1[0] + x * exx + y * eyx
    finalY = receiver1[1] + x * exy + y * eyy
    unknownPosition.append(finalX)
    unknownPosition.append(finalY)

    return unknownPosition


finalPos = []
rec1 = [9.07, 0.0] 
rec2 = [0.0, 0.0]
rec3 = [0.0, 3.68]
actualTransmitter1 = [9.07, -2.01]
actualTransmitter2 = [3.425, 0.0]
actualTransmitter3 = [4.945, 4.395]

actualTransmitters = [[9.07, -2.01], [3.425, 0.0], [4.945, 4.395]]

regex = []
distances = [0] * 3

for i in range(11,22):
    regex.append('.*\sDR ' + str(i) + '\s.*\s.* (\d+.\d+)')
for i in range(1,4):
    f = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\Distances\\Position" + str(i) + "_DistanceAndMean.txt")
    f_new = open('C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\Coordinates\\Position' + str(i) + '_AbsError.txt', "w")
    txt = f.read()
    for dr in range(11,22):
        distance = re.findall(regex[dr], txt)
        print("\n")
        f_new.write("DR" + str(dr) + "\n")
        index = 0
        for recdist in distance:
            distances[index] = float(recdist)
            index +=1
        finalPos = trilateration(rec1, rec2, rec3, distances[0], distances[1], distances[2])

        #Pythagoras/absolute error
        x1 = actualTransmitters[i-1][0]
        x2 = finalPos[0]
        y1 = actualTransmitters[i-1][1]
        y2 = finalPos[1]
        absError = math.sqrt((x2 - x1)**2 + (y2 - y1)**2) 
        absErrorInCm = absError * 100
        absErrorInCm = round(absErrorInCm, 3)
        print("x = " + str(finalPos[0]))
        print("y = " + str(finalPos[1]))
        f_new.write("x = " + str(finalPos[0]) + "\n")
        f_new.write("y = " + str(finalPos[1]) + "\n")
        f_new.write("absolute error: " + str(absErrorInCm) + "\n\n")

