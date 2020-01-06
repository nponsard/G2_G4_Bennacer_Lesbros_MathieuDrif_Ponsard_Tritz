#ifndef FIGURE_H
#define FIGURE_H

#include<vector>
#include <memory>
#include <type_traits>

#include "../graph/iminglinjectable.h"
#include "basefig.h"
#include "circle.h"

class figure : /*public IminGlInjectable, */public baseFig
{
protected:
    virtual minGL & _Edit (minGL & Window) const throw (myexception);
    std::vector <std::shared_ptr<baseFig>> vFig;
public:
  //  void Add (const baseFig & val) throw (myexception);

    template <typename T, typename = typename std::enable_if<std::is_base_of<baseFig, T>::value>::type>
    void Add (const T & Val)
    {
        std::shared_ptr<T> ptr (new T (Val));
        vFig.push_back(ptr);

    }
    //operateur de décalage +
    /*virtual*/ figure operator + (const pos & pos_) const;
    friend figure operator + (const pos & p, const figure & f) {return f + p;} //pour la commutativité

    //operateur de reduction *
    /*virtual*/ figure operator * (const float & f) const;
    friend figure operator * (const float & f, const figure & fig) {return fig * f;} //pour la commutativité
};

#endif // FIGURE_H
