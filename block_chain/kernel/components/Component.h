#ifndef COMPONENT_H
#define COMPONENT_H

#include "../../utils/serialization/Element.h"
class Serializer;
class Component
{
    public:
        virtual ~Component();
        Component();
        virtual Element* toElement() const = 0;
        void __init__(ElementObject* element, const Serializer* s, const char* encoding) { if(!initialized) this->fromElement(element, s, encoding); initialized = true; delete element;}
    protected:
        virtual void fromElement(ElementObject*, const Serializer*, const char* encoding) = 0;
    private:
        bool initialized = false;
};

#endif // COMPONENT_H
