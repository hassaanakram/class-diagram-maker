/*Implementation of container class*/
#include "../Headers/container.h"
using std::string;

//Constructors
Container::Container()
{
    //Default
}
Container::Container(string n, string t) : Variable(n, t)
{
}
