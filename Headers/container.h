#ifndef CONTAINER_H
#define CONTAINER_H

/*Class Container*/

#include <string>
#include "variable.h"
using std::string;

class Container : public Variable
{
public:
    Container();
    Container(string/*name*/, string/*type*/);
};

#endif // CONTAINER_H
