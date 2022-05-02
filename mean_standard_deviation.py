import re
import statistics

regex = '.*\s.*\s*.*(-\d+)' + (49 * '.*\s.*(-\d+)')
for position in range(1,4):
    #Address in github repository
    f_new = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\MSD\\Position" + str(position) + "_MSD.txt", "w")
    combined_MSD = [0]*21
    for receiver in range(1,4):
        #Address in github repository
        f = open("C:\\Users\\Adina\\source\\repos\\Exjobb\\LoRa-Exjobb\\Testbed_2\\Testbed2_results\\Position" + str(position) + "\\Testbed2_data_rec" + str(receiver) + ".txt")
        txt = f.read()
        extracted_data = re.findall(regex, txt)
        index = 0
        for datarate in extracted_data:
            array = []
            array.extend(datarate)
            array_int = [int(i) for i in array]
            if index == 0:
                combined_MSD[index]  += statistics.pstdev(array_int[1:])
            else:
                combined_MSD[index]  += statistics.pstdev(array_int)
            print(combined_MSD[index])
            index +=1
    print(combined_MSD)
    index = 11
    for msd in combined_MSD:
        f_new.write("DR" + str(index) + "\t" + str(msd / 3) + "\n")
        index +=1