import re

regex_6 = "( [0-9]+).*(-[0-9]+).+\s.*(-[0-9]+).+\s.*(-[0-9]+).+\s.*(-[0-9]+).+\s.*(-[0-9]+).+\s.*(-[0-9]+).+\s"
regex_5 = "( [0-9]+).*(-[0-9]+).+\s.*.*(-[0-9]+).+\s.*.*(-[0-9]+).+\s.*.*(-[0-9]+).+\s.*.*(-[0-9]+).+\s"

for DRx in range(11,32):
    f = open("C:\\Users\\myran\\Desktop\\Enchipsdatorer\\LoRa-Exjobb\\Calibration2\\Calibration2_Results\\Calibration_Raw_Data\\Calibration_DR" + str(DRx) + ".txt", encoding="utf-8")
    txt = f.read()
    f_new = open("C:\\Users\\myran\\Desktop\\Enchipsdatorer\\LoRa-Exjobb\\Calibration2\\Calibration2_Results\\Calibration_Average_RSSI\\Calibration_DR" + str(DRx) +"_average.txt", "w")
    if DRx < 22:
        extracted_data = re.findall(regex_6, txt)
        for distance in extracted_data:
            dist_in_m = round(int(distance[0]) * 0.01, 1)
            average_rssi = (int(distance[2]) + int(distance[3]) + int(distance[4]) + int(distance[5]) + int(distance[6])) / 5
            f_new.write(str(dist_in_m) + ":" + str(average_rssi) + "\n")
    else:
        extracted_data = re.findall(regex_5, txt)
        for distance in extracted_data:
            dist_in_m = round(int(distance[0]) * 0.01, 1)
            average_rssi = (int(distance[1]) + int(distance[2]) + int(distance[3]) + int(distance[4]) + int(distance[5])) / 5
            f_new.write(str(dist_in_m) + ":" + str(average_rssi) + "\n")


# for DRx in range(11,32):
#     with open('C:\\Users\\myran\\Desktop\\Enchipsdatorer\\LoRa-Exjobb\\Calibration2\\Calibration2_Results\\Calibration_DR' + str(DRx) + '.txt', 'w') as outfile:
#         for index in range(1,4):
#             with open('C:\\Users\\myran\\Desktop\\Enchipsdatorer\\LoRa-Exjobb\\Calibration2\\Calibration2_Results\\' + str(index) + '\\Calibration_DR' + str(DRx)) as infile:
#                 outfile.write(infile.read())