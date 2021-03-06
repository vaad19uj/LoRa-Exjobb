import re
import statistics
import functools
import operator
from itertools import chain

def convertTuple(tup):
    st = ''.join(map(str, tup))
    return st

def rssitodistance(rssi, dr):
    k = 0
    m = 0

    if dr == 11:
        k = -0.2864 
        m = -18.117
    elif dr == 12:
        k = -0.3211
        m = -20.813
    elif dr == 13:
        k = -0.3161
        m = -20.166
    elif dr == 14:
        k = -0.3233
        m = -20.753
    elif dr == 15:
        k = -0.3343
        m = -21.729
    elif dr == 16:
        k = -0.3174
        m = -20.488
    elif dr == 17:
        k = -0.3125
        m = -19.761
    elif dr == 18:
        k = -0.3109
        m = -19.088
    elif dr == 19:
        k = -0.3053
        m = -18.181
    elif dr == 20:
        k = -0.2813
        m = -15.888
    elif dr == 21:
        k = -0.2961
        m = -18.204
    elif dr == 22:
        k = -0.3064
        m = -18.313
    elif dr == 23:
        k = -0.3253
        m = -20.01
    elif dr == 24:
        k = -0.308
        m = -18.803
    elif dr == 25:
        k = -0.2691
        m = -15.914
    elif dr == 26:
        k = -0.2834
        m = -17.013
    elif dr == 27:
        k = -0.2804
        m = -16.88
    elif dr == 28:
        k = -0.3056
        m = -18.531
    elif dr == 29:
        k = -0.3021
        m = -19.273
    elif dr == 30:
        k = -0.2901
        m = -17.131
    elif dr == 31:
        k = -0.2775
        m = -15.637
    return(k*rssi+m)

#def rssitodistance(rssi, dr):
#    k = 0
#    m = 0

#    if dr == 0:
#        k = -0.3238
#        m = -21.35
#    elif dr == 1:
#        k = -0.3254
#        m = -21.34
#    elif dr == 2:
#        k = -0.3279
#        m = -21.414
#    elif dr == 3:
#        k = -0.3077
#        m = -19.833
#    elif dr == 4:
#        k = -0.3028
#        m = -19.287
#    elif dr == 5:
#        k = -0.2952
#        m = -18.428
#    elif dr == 6:
#        k = -0.2832
#        m = -17.128
#    elif dr == 7:
#        k = -0.2707
#        m = -16.23
#    elif dr == 8:
#        k = -0.2854
#        m = -17.045
#    elif dr == 9:
#        k = -0.2794
#        m = -16.067
#    elif dr == 10:
#        k = -0.2808
#        m = -15.69
#    return(k*rssi+m)

regex = '.*\s.*\s*.*(-\d+)' + (49 * '.*\s.*(-\d+)')

f_new_pos1 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\Distances\\Position1_DistanceAndMean.txt", "w")
f_new_pos2 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\Distances\\Position2_DistanceAndMean.txt", "w")
f_new_pos3 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\Distances\\Position3_DistanceAndMean.txt", "w")

frec1pos1 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\Position1\\Testbed2_data_rec1.txt")
frec2pos1 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\Position1\\Testbed2_data_rec2.txt")
frec3pos1 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\Position1\\Testbed2_data_rec3.txt")

frec1pos2 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\Position2\\Testbed2_data_rec1.txt")
frec2pos2 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\Position2\\Testbed2_data_rec2.txt")
frec3pos2 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\Position2\\Testbed2_data_rec3.txt")

frec1pos3 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\Position3\\Testbed2_data_rec1.txt")
frec2pos3 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\Position3\\Testbed2_data_rec2.txt")
frec3pos3 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\Position3\\Testbed2_data_rec3.txt")

txtrec1pos1 = frec1pos1.read()
txtrec2pos1 = frec2pos1.read()
txtrec3pos1 = frec3pos1.read()

txtrec1pos2 = frec1pos2.read()
txtrec2pos2 = frec2pos2.read()
txtrec3pos2 = frec3pos2.read()

txtrec1pos3 = frec1pos3.read()
txtrec2pos3 = frec2pos3.read()
txtrec3pos3 = frec3pos3.read()

extracted_data_rec1pos1 = re.findall(regex, txtrec1pos1)
extracted_data_rec2pos1 = re.findall(regex, txtrec2pos1)
extracted_data_rec3pos1 = re.findall(regex, txtrec3pos1)

extracted_data_rec1pos2 = re.findall(regex, txtrec1pos2)
extracted_data_rec2pos2 = re.findall(regex, txtrec2pos2)
extracted_data_rec3pos2 = re.findall(regex, txtrec3pos2)

extracted_data_rec1pos3 = re.findall(regex, txtrec1pos3)
extracted_data_rec2pos3 = re.findall(regex, txtrec2pos3)
extracted_data_rec3pos3 = re.findall(regex, txtrec3pos3)

f_new_pos1.write("rec 1" + "\n")
dr = 11
for tup in extracted_data_rec1pos1:
    combined_mean = 0.0
    f_new_pos1.write("DR " + str(dr) + "\n")
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    mean = combined_mean/len(tup)
    distance = rssitodistance(mean, dr)
    f_new_pos1.write("Mean: " + str(mean) + "\n")
    f_new_pos1.write("Distance: " + str(distance) + "\n")
    dr += 1

f_new_pos1.write("rec 2" + "\n")
dr = 11
for tup in extracted_data_rec2pos1:
    combined_mean = 0.0
    f_new_pos1.write("DR " + str(dr) + "\n")
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    mean = combined_mean/len(tup)
    distance = rssitodistance(mean, dr)
    f_new_pos1.write("Mean: " + str(mean) + "\n")
    f_new_pos1.write("Distance: " + str(distance) + "\n")
    dr += 1

f_new_pos1.write("rec 3" + "\n")
dr = 11
for tup in extracted_data_rec3pos1:
    combined_mean = 0.0
    f_new_pos1.write("DR " + str(dr) + "\n")
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    mean = combined_mean/len(tup)
    distance = rssitodistance(mean, dr)
    f_new_pos1.write("Mean: " + str(mean) + "\n")
    f_new_pos1.write("Distance: " + str(distance) + "\n")
    dr += 1

f_new_pos2.write("rec 1" + "\n")
dr = 11
for tup in extracted_data_rec1pos2:
    combined_mean = 0.0
    f_new_pos2.write("DR " + str(dr) + "\n")
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    mean = combined_mean/len(tup)
    distance = rssitodistance(mean, dr)
    f_new_pos2.write("Mean: " + str(mean) + "\n")
    f_new_pos2.write("Distance: " + str(distance) + "\n")
    dr += 1

f_new_pos2.write("rec 2" + "\n")
dr = 11
for tup in extracted_data_rec2pos2:
    combined_mean = 0.0
    f_new_pos2.write("DR " + str(dr) + "\n")
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    mean = combined_mean/len(tup)
    distance = rssitodistance(mean, dr)
    f_new_pos2.write("Mean: " + str(mean) + "\n")
    f_new_pos2.write("Distance: " + str(distance) + "\n")
    dr += 1

f_new_pos2.write("rec 3" + "\n")
dr = 11
for tup in extracted_data_rec3pos2:
    combined_mean = 0.0
    f_new_pos2.write("DR " + str(dr) + "\n")
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    mean = combined_mean/len(tup)
    distance = rssitodistance(mean, dr)
    f_new_pos2.write("Mean: " + str(mean) + "\n")
    f_new_pos2.write("Distance: " + str(distance) + "\n")
    dr += 1

f_new_pos3.write("rec 1" + "\n")
dr = 11
for tup in extracted_data_rec1pos3:
    combined_mean = 0.0
    f_new_pos3.write("DR " + str(dr) + "\n")
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    mean = combined_mean/len(tup)
    distance = rssitodistance(mean, dr)
    f_new_pos3.write("Mean: " + str(mean) + "\n")
    f_new_pos3.write("Distance: " + str(distance) + "\n")
    dr += 1

f_new_pos3.write("rec 2" + "\n")
dr = 11
for tup in extracted_data_rec2pos3:
    combined_mean = 0.0
    f_new_pos3.write("DR " + str(dr) + "\n")
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    mean = combined_mean/len(tup)
    distance = rssitodistance(mean, dr)
    f_new_pos3.write("Mean: " + str(mean) + "\n")
    f_new_pos3.write("Distance: " + str(distance) + "\n")
    dr += 1

f_new_pos3.write("rec 3" + "\n")
dr = 11
for tup in extracted_data_rec3pos3:
    combined_mean = 0.0
    f_new_pos3.write("DR " + str(dr) + "\n")
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    mean = combined_mean/len(tup)
    distance = rssitodistance(mean, dr)
    f_new_pos3.write("Mean: " + str(mean) + "\n")
    f_new_pos3.write("Distance: " + str(distance) + "\n")
    dr += 1

##############################################################################################3

#f_new_pos1.write("rec 1" + "\n")
#dr = 0
#for tup in extracted_data_rec1pos1:
#    combined_mean = 0.0
#    print("DR " + str(dr))
#    f_new_pos1.write("DR " + str(dr) + "\n")
#    dr += 1
#    for tuptup in tup:
#        print(tuptup)
#        combined_mean += int(tuptup)

#    print("Mean: " + str(combined_mean/len(tup)))
#    mean = str(combined_mean/len(tup))
#    f_new_pos1.write("Mean: " + mean + "\n")

#f_new_pos1.write("rec 2" + "\n")
#dr = 0
#for tup in extracted_data_rec2pos1:
#    combined_mean = 0.0
#    print("DR " + str(dr))
#    f_new_pos1.write("DR " + str(dr) + "\n")
#    dr += 1
#    for tuptup in tup:
#        print(tuptup)
#        combined_mean += int(tuptup)

#    print("Mean: " + str(combined_mean/len(tup)))
#    mean = str(combined_mean/len(tup))
#    f_new_pos1.write("Mean: " + mean + "\n")

#f_new_pos1.write("rec 3" + "\n")
#dr = 0
#for tup in extracted_data_rec3pos1:
#    combined_mean = 0.0
#    print("DR " + str(dr))
#    f_new_pos1.write("DR " + str(dr) + "\n")
#    dr += 1
#    for tuptup in tup:
#        print(tuptup)
#        combined_mean += int(tuptup)

#    print("Mean: " + str(combined_mean/len(tup)))
#    mean = str(combined_mean/len(tup))
#    f_new_pos1.write("Mean: " + mean + "\n")

#f_new_pos2.write("rec 1" + "\n")
#dr = 0
#for tup in extracted_data_rec1pos2:
#    combined_mean = 0.0
#    print("DR " + str(dr))
#    f_new_pos2.write("DR " + str(dr) + "\n")
#    dr += 1
#    for tuptup in tup:
#        print(tuptup)
#        combined_mean += int(tuptup)

#    print("Mean: " + str(combined_mean/len(tup)))
#    mean = str(combined_mean/len(tup))
#    f_new_pos2.write("Mean: " + mean + "\n")

#f_new_pos2.write("rec 2" + "\n")
#dr = 0
#for tup in extracted_data_rec2pos2:
#    combined_mean = 0.0
#    print("DR " + str(dr))
#    f_new_pos2.write("DR " + str(dr) + "\n")
#    dr += 1
#    for tuptup in tup:
#        print(tuptup)
#        combined_mean += int(tuptup)

#    print("Mean: " + str(combined_mean/len(tup)))
#    mean = str(combined_mean/len(tup))
#    f_new_pos2.write("Mean: " + mean + "\n")

#f_new_pos2.write("rec 3" + "\n")
#dr = 0
#for tup in extracted_data_rec3pos2:
#    combined_mean = 0.0
#    print("DR " + str(dr))
#    f_new_pos2.write("DR " + str(dr) + "\n")
#    dr += 1
#    for tuptup in tup:
#        print(tuptup)
#        combined_mean += int(tuptup)

#    print("Mean: " + str(combined_mean/len(tup)))
#    mean = str(combined_mean/len(tup))
#    f_new_pos2.write("Mean: " + mean + "\n")


#f_new_pos3.write("rec 1" + "\n")
#dr = 0
#for tup in extracted_data_rec1pos3:
#    combined_mean = 0.0
#    print("DR " + str(dr))
#    f_new_pos3.write("DR " + str(dr) + "\n")
#    dr += 1
#    for tuptup in tup:
#        print(tuptup)
#        combined_mean += int(tuptup)

#    print("Mean: " + str(combined_mean/len(tup)))
#    mean = str(combined_mean/len(tup))
#    f_new_pos3.write("Mean: " + mean + "\n")

#f_new_pos3.write("rec 2" + "\n")
#dr = 0
#for tup in extracted_data_rec2pos3:
#    combined_mean = 0.0
#    print("DR " + str(dr))
#    f_new_pos3.write("DR " + str(dr) + "\n")
#    dr += 1
#    for tuptup in tup:
#        print(tuptup)
#        combined_mean += int(tuptup)

#    print("Mean: " + str(combined_mean/len(tup)))
#    mean = str(combined_mean/len(tup))
#    f_new_pos3.write("Mean: " + mean + "\n")

#f_new_pos3.write("rec 3" + "\n")
#dr = 0
#for tup in extracted_data_rec3pos3:
#    combined_mean = 0.0
#    print("DR " + str(dr))
#    f_new_pos3.write("DR " + str(dr) + "\n")
#    dr += 1
#    for tuptup in tup:
#        print(tuptup)
#        combined_mean += int(tuptup)

#    print("Mean: " + str(combined_mean/len(tup)))
#    mean = str(combined_mean/len(tup))
#    f_new_pos3.write("Mean: " + mean + "\n")


#################################################################################3


#f_new_pos1.write("rec 2")
#for tup in extracted_data_rec2pos1:
#    f_new_pos1.write("\n")
#    for tuptup in tup:
#        f_new_pos1.write("\n")
#        f_new_pos1.write(tuptup)

#f_new_pos1.write("rec 3")
#for tup in extracted_data_rec3pos1:
#    f_new_pos1.write("\n")
#    for tuptup in tup:
#        f_new_pos1.write("\n")
#        f_new_pos1.write(tuptup)

#f_new_pos2.write("rec 1")
#for tup in extracted_data_rec1pos2:
#    f_new_pos2.write("\n")
#    for tuptup in tup:
#        f_new_pos2.write("\n")
#        f_new_pos2.write(tuptup)

#f_new_pos2.write("rec 2")
#for tup in extracted_data_rec2pos2:
#    f_new_pos2.write("\n")
#    for tuptup in tup:
#        f_new_pos2.write("\n")
#        f_new_pos2.write(tuptup)

#f_new_pos2.write("rec 3")
#for tup in extracted_data_rec3pos2:
#    f_new_pos2.write("\n")
#    for tuptup in tup:
#        f_new_pos2.write("\n")
#        f_new_pos2.write(tuptup)

#f_new_pos3.write("rec 1")
#for tup in extracted_data_rec1pos3:
#    f_new_pos3.write("\n")
#    for tuptup in tup:
#        f_new_pos3.write("\n")
#        f_new_pos3.write(tuptup)

#f_new_pos3.write("rec 2")
#for tup in extracted_data_rec2pos3:
#    f_new_pos3.write("\n")
#    for tuptup in tup:
#        f_new_pos3.write("\n")
#        f_new_pos3.write(tuptup)

#f_new_pos3.write("rec 3")
#for tup in extracted_data_rec3pos3:
#    f_new_pos3.write("\n")
#    for tuptup in tup:
#        f_new_pos3.write("\n")
#        f_new_pos3.write(tuptup)


