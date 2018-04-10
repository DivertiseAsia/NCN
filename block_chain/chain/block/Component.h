#ifndef COMPONENT_H
#define COMPONENT_H

#include "../../utils/serialization/Element.hpp"
class Component
{
    public:
        virtual ~Component();
        Component();
        virtual Element* toElement() = 0;
        void __init__(ElementObject* element) { if(!initialized) this->fromElement(element); initialized = true; delete element;}
        virtual std::string to_string() const = 0;
    protected:
        virtual void fromElement(ElementObject*) = 0;
    private:
        bool initialized = false;
};

#endif // COMPONENT_H
