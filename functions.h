#include <iostream>

using namespace std;

// [Log]
int log(string l);

//Changes any value to string
template <typename T>
std::string to_string(T value);

//Changes string to int
int to_int(string s);

//Check if file exists
inline bool exists(const std::string& name);

//Loads all files need to load
int loadAllFiles();

//Encryption/decryption
std::string encrypt(std::string key, const char* input, const char* output);
std::string decrypt(std::string key, const char* input, const char* output);
