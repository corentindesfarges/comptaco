/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <QMainWindow>
#include <stdexcept>
#include <string>

using namespace std;

class Utilities
{
public:
    Utilities() {}
    ~Utilities() {}
    static string nb2string(int n);
    static string nb2string(double n);
    static int string2int(string n);
    static double string2double(string s);
    static bool string2bool(string s);
    static string escapeString(string str);
    static bool checkIsValue(string val);
    static void setTheme(QMainWindow *window, QString no);
    static vector<string> split(const string &src, const char delim);
    static int toPercent(int pct, int max);

};

#endif // UTILITIES_H
