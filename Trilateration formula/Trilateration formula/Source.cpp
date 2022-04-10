#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h> 
#include <vector>
using namespace std;

std::vector<double> trilateration(double receiver1[], double receiver2[], double receiver3[], double r1, double r2, double r3) {
    std::vector<double> unknownPosition;
    
    //unit vector in a direction from point1 to point 2
    double p2p1Distance = pow(pow(receiver2[0] - receiver1[0], 2) + pow(receiver2[1] - receiver1[1], 2), 0.5);
    double exx = (receiver2[0] - receiver1[0]) / p2p1Distance;
    double exy = (receiver2[1] - receiver1[1]) / p2p1Distance;
   
    //signed magnitude of the x component
    double i = exx*(receiver3[0] - receiver1[0]) + exy*(receiver3[1] - receiver1[1]);

    //the unit vector in the y direction. 
    double eyx = (receiver3[0] - receiver1[0] - i * exx) / pow(pow(receiver3[0] - receiver1[0] - i * exx, 2) + pow(receiver3[1] - receiver1[1] - i * exy, 2), 0.5);
    double eyy = (receiver3[1] - receiver1[1] - i * exy) / pow(pow(receiver3[0] - receiver1[0] - i * exx, 2) + pow(receiver3[1] - receiver1[1] - i * exy, 2), 0.5);
    
    //the signed magnitude of the y component   
    double j = eyx * (receiver3[0] - receiver1[0]) + eyy * (receiver3[1] - receiver1[1]);
    
    //coordinates
    double x = (pow(r1, 2) - pow(r2, 2) + pow(p2p1Distance, 2)) / (2 * p2p1Distance);
    double y = (pow(r1, 2) - pow(r3, 2) + pow(i, 2) + pow(j, 2)) / (2*j) - i * x / j;
    
    //result coordinates
    double finalX = receiver1[0] + x * exx + y * eyx;
    double finalY = receiver1[1] + x * exy + y * eyy;
    unknownPosition.push_back(finalX);
    unknownPosition.push_back(finalY);
    return unknownPosition;
}

int main(int argc, char* argv[]) {
    std::vector<double> finalPose;
    double p1[] = { 4.0,4.0 };
    double p2[] = { 9.0,7.0 };
    double p3[] = { 9.0,1.0 };
    double r1, r2, r3;
    r1 = 4;
    r2 = 3;
    r3 = 3.25;
    finalPose = trilateration(p1, p2, p3, r1, r2, r3);
    cout << "X:::  " << finalPose[0] << endl;
    cout << "Y:::  " << finalPose[1] << endl;
    //x = 8, y = 4.1

}

