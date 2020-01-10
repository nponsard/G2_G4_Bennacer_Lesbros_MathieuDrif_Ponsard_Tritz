#include "loadScores.h"
#include "scoresort.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

vector<pair<string, unsigned>> loadScores(const string & fileName)
{
    vector<pair<string, unsigned>> scores;
    unsigned nb(0);
    ifstream ifs(fileName);
    string line;
    string name;
    unsigned value;
    char sep;

    if(ifs.is_open())
    {
        while(nb < 3)
        {
            getline(ifs, line);

            if (ifs.eof())
                break;

            istringstream istr;
            istr.str(line);
            istr >> name;

            istr >> sep;
            istr >> value;
            if(!istr.fail())
            {
                if(name.size() > 3)
                    name = string(name, 0, 3);

                for(char & c : name)
                    c = toupper(c);

                scores.push_back(make_pair(name, value));
            }

            ++nb;
        }
    }
    scoreSort(scores);
    return scores;
}
