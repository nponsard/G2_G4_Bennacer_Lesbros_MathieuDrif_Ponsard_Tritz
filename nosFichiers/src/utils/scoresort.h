#ifndef SCORESORT_H
#define SCORESORT_H

#include <vector>
#include <string>

void scoreSort(std::vector<std::pair<std::string, unsigned> > &scores);
void insertScore(std::vector<std::pair<std::string, unsigned>> &scores, const std::string & nom, const unsigned & score, const bool & popBack);

#endif // SCORESORT_H
