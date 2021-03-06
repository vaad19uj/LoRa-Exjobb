import re

regex_DR0 = "( [0-9]+).*(-[0-9]+).+\s.*(-[0-9]+).+\s.*(-[0-9]+).+\s.*(-[0-9]+).+\s.*(-[0-9]+).+\s.*(-[0-9]+).+\s"
regex_DR1_DR10 = "( [0-9]+).*(-[0-9]+).+\s.*.*(-[0-9]+).+\s.*.*(-[0-9]+).+\s.*.*(-[0-9]+).+\s.*.*(-[0-9]+).+\s"

for DRx in range(11):    
    f = open("C:\\Users\\myran\\Desktop\\Enchipsdatorer\\LoRa-Exjobb\\Calibration1_results\\Calibration_DR" + str(DRx), encoding="utf-8")
    txt = f.read();
    f_new = open("C:\\Users\\myran\\Pictures\\Calibration_Average_RSSI\\Calibration_DR" + str(DRx) +"_average.txt", "w")
    if DRx == 0:
        extracted_data = re.findall(regex_DR0, txt)
        for distance in extracted_data:
            dist_in_m = round(int(distance[0]) * 0.01, 1)
            average_rssi = (int(distance[2]) + int(distance[3]) + int(distance[4]) + int(distance[5]) + int(distance[6])) / 5            
            f_new.write(str(dist_in_m) + ":" + str(average_rssi) + "\n")
    else:
        extracted_data = re.findall(regex_DR1_DR10, txt)
        for distance in extracted_data:
            dist_in_m = round(int(distance[0]) * 0.01, 1)
            average_rssi = (int(distance[1]) + int(distance[2]) + int(distance[3]) + int(distance[4]) + int(distance[5])) / 5
            f_new.write(str(dist_in_m) + ":" + str(average_rssi) + "\n")