import re
import statistics
import functools
import operator
from itertools import chain

def convertTuple(tup):
    st = ''.join(map(str, tup))
    return st

regex = '.*\s.*\s*.*(-\d+)' + (49 * '.*\s.*(-\d+)')

f_new_pos1 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_1\\Testbed1_results\\Position1_Mean", "w")
f_new_pos2 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_1\\Testbed1_results\\Position2_Mean", "w")
f_new_pos3 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_1\\Testbed1_results\\Position3_Mean", "w")

frec1pos1 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_1\\Testbed1_results\\Position1\\Testbed1_data_rec1.txt")
frec2pos1 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_1\\Testbed1_results\\Position1\\Testbed1_data_rec2.txt")
frec3pos1 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_1\\Testbed1_results\\Position1\\Testbed1_data_rec3.txt")

frec1pos2 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_1\\Testbed1_results\\Position2\\Testbed1_data_rec1.txt")
frec2pos2 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_1\\Testbed1_results\\Position2\\Testbed1_data_rec2.txt")
frec3pos2 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_1\\Testbed1_results\\Position2\\Testbed1_data_rec3.txt")

frec1pos3 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_1\\Testbed1_results\\Position3\\Testbed1_data_rec1.txt")
frec2pos3 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_1\\Testbed1_results\\Position3\\Testbed1_data_rec2.txt")
frec3pos3 = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_1\\Testbed1_results\\Position3\\Testbed1_data_rec3.txt")

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
dr = 0
for tup in extracted_data_rec1pos1:
    combined_mean = 0.0
    print("DR " + str(dr))
    f_new_pos1.write("DR " + str(dr) + "\n")
    dr += 1
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    print("Mean: " + str(combined_mean/len(tup)))
    mean = str(combined_mean/len(tup))
    f_new_pos1.write("Mean: " + mean + "\n")

f_new_pos1.write("rec 2" + "\n")
dr = 0
for tup in extracted_data_rec2pos1:
    combined_mean = 0.0
    print("DR " + str(dr))
    f_new_pos1.write("DR " + str(dr) + "\n")
    dr += 1
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    print("Mean: " + str(combined_mean/len(tup)))
    mean = str(combined_mean/len(tup))
    f_new_pos1.write("Mean: " + mean + "\n")

f_new_pos1.write("rec 3" + "\n")
dr = 0
for tup in extracted_data_rec3pos1:
    combined_mean = 0.0
    print("DR " + str(dr))
    f_new_pos1.write("DR " + str(dr) + "\n")
    dr += 1
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    print("Mean: " + str(combined_mean/len(tup)))
    mean = str(combined_mean/len(tup))
    f_new_pos1.write("Mean: " + mean + "\n")

f_new_pos2.write("rec 1" + "\n")
dr = 0
for tup in extracted_data_rec1pos2:
    combined_mean = 0.0
    print("DR " + str(dr))
    f_new_pos2.write("DR " + str(dr) + "\n")
    dr += 1
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    print("Mean: " + str(combined_mean/len(tup)))
    mean = str(combined_mean/len(tup))
    f_new_pos2.write("Mean: " + mean + "\n")

f_new_pos2.write("rec 2" + "\n")
dr = 0
for tup in extracted_data_rec2pos2:
    combined_mean = 0.0
    print("DR " + str(dr))
    f_new_pos2.write("DR " + str(dr) + "\n")
    dr += 1
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    print("Mean: " + str(combined_mean/len(tup)))
    mean = str(combined_mean/len(tup))
    f_new_pos2.write("Mean: " + mean + "\n")

f_new_pos2.write("rec 3" + "\n")
dr = 0
for tup in extracted_data_rec3pos2:
    combined_mean = 0.0
    print("DR " + str(dr))
    f_new_pos2.write("DR " + str(dr) + "\n")
    dr += 1
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    print("Mean: " + str(combined_mean/len(tup)))
    mean = str(combined_mean/len(tup))
    f_new_pos2.write("Mean: " + mean + "\n")


f_new_pos3.write("rec 1" + "\n")
dr = 0
for tup in extracted_data_rec1pos3:
    combined_mean = 0.0
    print("DR " + str(dr))
    f_new_pos3.write("DR " + str(dr) + "\n")
    dr += 1
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    print("Mean: " + str(combined_mean/len(tup)))
    mean = str(combined_mean/len(tup))
    f_new_pos3.write("Mean: " + mean + "\n")

f_new_pos3.write("rec 2" + "\n")
dr = 0
for tup in extracted_data_rec2pos3:
    combined_mean = 0.0
    print("DR " + str(dr))
    f_new_pos3.write("DR " + str(dr) + "\n")
    dr += 1
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    print("Mean: " + str(combined_mean/len(tup)))
    mean = str(combined_mean/len(tup))
    f_new_pos3.write("Mean: " + mean + "\n")

f_new_pos3.write("rec 3" + "\n")
dr = 0
for tup in extracted_data_rec3pos3:
    combined_mean = 0.0
    print("DR " + str(dr))
    f_new_pos3.write("DR " + str(dr) + "\n")
    dr += 1
    for tuptup in tup:
        print(tuptup)
        combined_mean += int(tuptup)

    print("Mean: " + str(combined_mean/len(tup)))
    mean = str(combined_mean/len(tup))
    f_new_pos3.write("Mean: " + mean + "\n")


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


