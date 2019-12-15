#ifndef POS_H
#define POS_H

struct pos
{
  unsigned abs, ord;

  pos (const unsigned & abs_ = 0, const unsigned & ord_ = 0) : abs(abs_), ord (ord_) {}
  pos operator + (const pos & pos_) const {return pos (abs + pos_.abs, ord + pos_.ord);}
  bool operator == (const pos & pos_) const {return pos_.abs == abs && pos_.ord == ord;}
  pos operator * (const float & reductionRation) const {return pos (abs*reductionRation, ord*reductionRation);}
  pos operator *(const pos & pos_) const {return pos (abs*pos_.abs, ord*pos_.ord);}
  friend pos operator *(const float & reductionRation, const pos & pos_) {return pos_*(reductionRation);}
};

#endif // POS_H
