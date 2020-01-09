#include "loadconfig.h"
#include <fstream>
#include <algorithm>

using namespace std;

map<string,string> loadConfig(string fileName){
    map<string,string> result;
    ifstream ifs (fileName);
    string key;
    string sep;
    AuthorizedKey AK;

    while (true) {
       ifs >> key;

       //unsigned
       if (find(AK.VParamUnsigned.begin(),AK.VParamUnsigned.end(), key) != AK.VParamUnsigned.end()){
           ifs >> sep ;
           unsigned val;
           ifs >> val;
           result[key] = to_string(val);
       }
       if(ifs.eof()) return result;
       getline(ifs,sep);
    }

}
