
#ifndef IBEHAVIOUR_H
#define IBEHAVIOUR_H

// Interface to implement the behaviour of an object.
// It is included in Enemy.h making it an interface, so
// a derived class in needed to implement an enemy.

class IBehaviour
{
public:
    virtual void RunBehaviour() = 0;
};

#endif /* IBEHAVIOUR_H */
