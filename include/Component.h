#ifndef COMPONENT_H
#define COMPONENT_H

#include "../block_chain/utils/serialization/Element.hpp"
class Component
{
    public:
        virtual ~Component() {}
        Component() {}
        virtual Element* toElement() = 0;
        void __init__(ElementObject* element) { if(!initialized) this->fromElement(element); initialized = true; delete element;}
    protected:
        virtual void fromElement(ElementObject*) = 0;
    private:
        bool initialized = false;
};

#endif // COMPONENT_H
