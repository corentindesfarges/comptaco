/* ***** BEGIN LICENSE BLOCK *****
 * Corentin Desfarges - Copyright (C) 2013 - 2015
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <QSettings>
#include <stdlib.h>
#include <sstream>

#include "utilities.h"

string Utilities::nb2string(int n)
{
    char s[11];
    try{
        snprintf(s, 11, "%d", n);
    } catch (std::exception e){
        cerr << n << " is not a correct nomber.";
    }

    return s;
}

string Utilities::nb2string(double n)
{
    std::ostringstream strs;
    strs << n;
    return strs.str();
}

int Utilities::string2int(string s)
{
    int res;
    try{
        std::istringstream ( s ) >> res;
    } catch (std::exception e){
        res = 0;
    }
    return res;
}

bool Utilities::string2bool(string s)
{
    if(s == "0")
    {
        return false;
    }
    else
    {
        return true;
    }
}

double Utilities::string2double(string s)
{
    return std::stod(s);
}

string Utilities::escapeString(string str)
{
    const string simple_quote = "''";
    for(int i = 0 ; i < str.size() ; ++i){
        if(str[i]=='\''){
            str.replace(i,1,simple_quote);
            i++;
        }
    }
    return str;
}

bool Utilities::checkIsValue(string val)
{
    try{
        string2double(val);
    } catch (std::exception e){
        return false;
    }
    return true;
}

void Utilities::setTheme(QMainWindow *window, QString no)
{
    QSettings settings("Dev", "ComptaCool");
    window->setStyleSheet("#centralWidget{background-image: url(:wp"+no+settings.value("theme","c").toString()+")}");
}


vector<string> Utilities::split(const string &src, const char delim)
{
    vector<string> v;
    string::const_iterator p = src.begin ();
    string::const_iterator q =
            std::find (p, src.end (), delim);
    while (q != src.end ())
    {
        v.push_back (string (p, q));
        p = q;
        q = std::find (++p, src.end (), delim);
    }
    if (p != src.end ())
        v.push_back (string (p, src.end ()));
    return v;
}


int Utilities::toPercent(int pct, int max)
{
    return max*pct/100;
}
