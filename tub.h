//
//  tub.h
//  CS20a project1
//
//  Created by Ludwig von Schönfeldt  on 11.03.22.
//

#ifndef tub_h
#define tub_h

#include <stdio.h>

#include "life.h"

class Tub : public Life {
public:
    // Constructor/destructor
    Tub(int r, int c);
    ~Tub();
};

#endif /* tub_h */
