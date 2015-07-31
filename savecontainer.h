#ifndef SAVECONTAINER_H
#define SAVECONTAINER_H
#include <vector>
#include <map>

using namespace std;

class SaveContainer
{
    public:
    string hero[16];
    string hatapon[16];
    string yaripons[6][16];
    string tatepons[6][16];
    string yumipons[6][16];

    int demopass;

    map<int,int> items,armor,special;

    int kaching;

    SaveContainer();
    void Save(std::string path);
    void Load(std::string path);
    void Synchronize(string nick, string pass, int option);
};
#endif // SAVECONTAINER_H
