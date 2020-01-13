#ifndef SCORESORT_H
#define SCORESORT_H

#include <vector>
#include <string>

void scoreSort(std::vector<std::pair<std::string, unsigned> > &scores);
void scoreInsertion(std::vector<std::pair<std::string, unsigned>> &scores, const std::string & nom, const unsigned & score);

#endif // SCORESORT_H
