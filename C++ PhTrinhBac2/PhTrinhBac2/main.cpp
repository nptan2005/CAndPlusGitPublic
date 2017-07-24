//
//  main.cpp
//  PhTrinhBac2
//
//  Created by Nguyen Phuoc Tan on 4/27/15.
//  Copyright (c) 2015 Nguyen Phuoc Tan. All rights reserved.
//

#include <iostream>
//#incllude <cmath>

using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    double a,b,c;
    cout << "nhap phuong trinh bac 2 damh: a^2+bx = c \n";
    cout << "\t nhap a="; cin >> a;
    cout << "\t nhap b="; cin >> b;
    cout << "\t nhap c="; cin >> c;
    string C;
    if(c< 0) C= "-" ; else C = "+";
    cout << "\n Phuong trinh vua nhap la: " <<  a << "x^2 + " << b << "x " <<  C << c << "= 0" << "\n" ;
    //double d = b*b - 4*a*c;
    //double sqrtd = sqrt(d);
    
    
    return 0;
}
