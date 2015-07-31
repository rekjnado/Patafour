#include <iostream>
#include "savecontainer.h"
#include <map>
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}

int toInt(string str)
{
int i;
istringstream iss(str);
iss >> i;
return i;
}

string toString(int i)
{
    ostringstream ss;
    ss << i;
    string str = ss.str();
    return str;
}

SaveContainer::SaveContainer()
{
    demopass = 3;

    kaching = 120;
    hatapon[0] = "1";
    hatapon[1] = "Hatapon";
    hatapon[2] = "100";
    hatapon[3] = "100";
    hatapon[4] = "0";
    hatapon[5] = "4000";
    hatapon[6] = "1";
    hatapon[7] = "2";

    hero[0] = "1";
    hero[1] = "Hero";
    hero[2] = "100";
    hero[3] = "100";
    hero[4] = "0";
    hero[5] = "4000";
    hero[6] = "1";
    hero[7] = "2";
    hero[8] = "1"; /// mask slot

    yaripons[0][0]="1"; /// lvl
    yaripons[1][0]="1";
    yaripons[2][0]="1";
    yaripons[0][1]="Yaripon"; /// nazwa
    yaripons[1][1]="Yaripon";
    yaripons[2][1]="Yaripon";
    yaripons[0][2]="100"; /// current hp
    yaripons[1][2]="100";
    yaripons[2][2]="100";
    yaripons[0][3]="100"; /// max hp
    yaripons[1][3]="100";
    yaripons[2][3]="100";
    yaripons[0][4]="0"; /// current exp
    yaripons[1][4]="0";
    yaripons[2][4]="0";
    yaripons[0][5]="1000"; /// exp to next lvl
    yaripons[1][5]="1000";
    yaripons[2][5]="1000";
    yaripons[0][6]="1"; /// weapon slot
    yaripons[1][6]="1";
    yaripons[2][6]="1";
    yaripons[0][7]="1"; /// helm slot
    yaripons[1][7]="1";
    yaripons[2][7]="1";
    yaripons[0][8]="0"; /// spear modifier
    yaripons[1][8]="0";
    yaripons[2][8]="0";
    yaripons[0][9]="0"; /// helm modifier
    yaripons[1][9]="0";
    yaripons[2][9]="0";
    yaripons[0][10]="0"; /// vanity spear
    yaripons[1][10]="0";
    yaripons[2][10]="0";
    yaripons[0][11]="0"; /// vanity helm
    yaripons[1][11]="0";
    yaripons[2][11]="0";
    yaripons[0][12]="0"; /// vanity boots
    yaripons[1][12]="0";
    yaripons[2][12]="0";
    yaripons[0][13]="0"; /// vanity cape
    yaripons[1][13]="0";
    yaripons[2][13]="0";
    yaripons[0][14]="0"; /// vanity gloves
    yaripons[1][14]="0";
    yaripons[2][14]="0";
}

void SaveContainer::Save(std::string path)
{

}

void SaveContainer::Load(std::string path)
{

}

/// 0 = receive
/// 1 = send to server
void SaveContainer::Synchronize(string nick, string pass, int option)
{

if(option==0)
{
    cout << "Synchronizowanie danych z serwerem Patafour (serwer->gra)" << endl;
    CURL *curl;
    CURLcode res;

    string itemsheet;

    string url = "http://patafour.xaa.pl/community/synchronizein.php?nick="+nick;

    curl = curl_easy_init();
    if(curl)
    {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &itemsheet);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    res = curl_easy_perform(curl);

    ofstream tempsave("data.psf");

    if(tempsave.is_open())
    {
        tempsave << itemsheet;
        tempsave.close();
    }

    ifstream readsave("data.psf");
    string receivesave;

    bool infodone = false;
    int linecount = 1;

    int itemamount=0;
    int armoramount=0;
    int specialamount=0;

    while(getline(readsave,receivesave))
    {

    if(infodone==true)
    {
    if(linecount <= itemamount)
    {
        int temp = toInt(receivesave);
        items[linecount] = temp;
        cout << "item " << linecount << " " << temp << endl;
        cout << items[linecount] << endl;
    }

    if(linecount > itemamount)
    {
    if(linecount <= armoramount)
    {
        armor[linecount-itemamount] = toInt(receivesave);
        //cout << "armor " << linecount-itemamount << " " << receivesave << endl;
    }
    }

    if(linecount > itemamount)
    {
    if(linecount > armoramount)
    {
    if(linecount <= specialamount)
    {
        special[linecount - itemamount - armoramount] = toInt(receivesave);
        cout << "special " << linecount-itemamount-armoramount << " " << receivesave << endl;
    }
    }
    }

    linecount++;
    }

    if(receivesave.find("[")<5)
    {
    cout << receivesave.find("[") << endl;
    string pre = receivesave.substr(receivesave.find("[")+1);
    string pre2 = pre.substr(0,pre.size()-2);
    itemamount = toInt(pre2.substr(0,pre2.find_first_of(":")));
    string pre3 = pre2.substr(pre2.find_first_of(":")+1);
    armoramount = toInt(pre3.substr(0,pre3.find_first_of(":")));
    specialamount = toInt(pre3.substr(pre3.find_first_of(":")+1));

    cout << itemamount << armoramount << specialamount << endl;
    infodone = true;
    }

    }
    readsave.close();

    curl_easy_cleanup(curl);
    }


}

if(option==1)
{
  CURL *curl;
  CURLcode res;
  char *url = "http://patafour.tk/community/synchronizein.php?mode=amount&type=items";

  string amount;

  cout << "Synchronizowanie danych z serwerem Patafour (gra->serwer)" << endl;

  curl_global_init(CURL_GLOBAL_ALL);

  curl = curl_easy_init();
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &amount);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    res = curl_easy_perform(curl);
    cout << amount << endl;

    for(int i=1; i<=toInt(amount); i++)
    {
    string response;

    string number = toString(i);
    string url = "http://patafour.tk/community/synchronizeout.php";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    string postfields="type=items&id="+number+"&amount="+toString(items[i])+"&login="+nick+"&password="+pass;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    res = curl_easy_perform(curl);
    cout << response << endl;
    }

    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();

}

}
