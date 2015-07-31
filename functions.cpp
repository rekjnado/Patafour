#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "functions.h"

//documentation in .h file

int log(string l) {
cout << "[Log] " << l << endl;
return 0;
}

template <typename T>
std::string to_string(T value)
    {
    std::ostringstream os;
    os << value;
    return os.str();
    }

template <typename A>
std::string fix(A value)
    {
    std::ostringstream os;
    os << std::fixed << to_int(value);
    return os.str();
    }

int to_int(string s)
{
     int tmp = 0, i = 0;
     bool m = false;
     if(s[0] == '-') {
      m = true;
      i++;
     }
     for(; i < s.size(); i++)
      tmp = 10 * tmp + s[i] - 48;
     return m ? -tmp : tmp;
}

inline bool exists(const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

std::string encrypt(std::string key, const char* input, const char* output)
{
    std::ifstream file(input);
    std::ofstream file2(output);
    std::string line;
    std::string full;

    if (file.is_open()) {
    while(getline(file,line)) {
    full+=line;
    full+='\n';
    }
    full.erase(full.length()-1,full.length());
    file.close();
    }

    std::string tmp(key);
    while (key.size() < full.size())
        key += tmp;

    for (std::string::size_type i = 0; i < full.size(); ++i)
        full[i] ^= key[i];

    file2 << full;
    file2.close();

    return full;
}

std::string decrypt(std::string key, const char* input, const char* output)
{
    std::string decrypted = encrypt(key,input,output);
    return decrypted;
}

