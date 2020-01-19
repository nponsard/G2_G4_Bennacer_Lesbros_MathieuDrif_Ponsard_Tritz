#ifndef POS_H
#define POS_H

struct pos
{
  unsigned abs, ord;

  //constructeurs
  pos (const unsigned & abs_ = 0, const unsigned & ord_ = 0) : abs(abs_), ord (ord_) {}
  pos (const pos & pos_) : abs (pos_.abs), ord (pos_.ord){}

  //décalage
  pos operator + (const pos & pos_) const {return pos (abs + pos_.abs, ord + pos_.ord);}

  //reduction
  pos operator * (const float & reductionRation) const {return pos (abs*reductionRation, ord*reductionRation);}
  friend pos operator *(const float & reductionRation, const pos & pos_) {return pos_*(reductionRation);}
  //pos operator *(const pos & pos_) const {return pos (abs*pos_.abs, ord*pos_.ord);}

  //egalite
  bool operator == (const pos & pos_) const {return pos_.abs == abs && pos_.ord == ord;}

  //le min
  static pos min (const pos & p1, const pos & p2) {
      if (p1.abs < p2.abs) return p1;
      else if (p1.abs == p2.abs && p1.ord < p2.ord) return p1;
      return p2;
  }
  //ptr de fonction sur min
  static bool minf (const pos & p1, const pos & p2) {
      return (p1 == min (p1, p2));
  }

  unsigned & getAbs() {
      return abs;
  }

  unsigned & getOrd() {
      return ord;
  }


};

#endif // POS_H
