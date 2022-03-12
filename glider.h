//
//  glider.h
//  CS20a project1
//
//  Created by Ludwig von Schönfeldt  on 11.03.22.
//

#include "life.h"

#ifndef glider_h
#define glider_h

class Glider : public Life {
public:
    // Constructor/destructor
    Glider(int r, int c);
    ~Glider();
};

#endif /* glider_h */
