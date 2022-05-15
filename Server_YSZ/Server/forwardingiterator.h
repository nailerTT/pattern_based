#ifndef FORWARDINGITERATOR_H
#define FORWARDINGITERATOR_H

class ForwardingIterator
{
public:
    ForwardingIterator();
    virtual bool HasNext();
    virtual void Next();
};

#endif // FORWARDINGITERATOR_H
