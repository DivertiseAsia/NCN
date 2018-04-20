#ifndef COMPONENT_H
#define COMPONENT_H

#include "../../utils/serialization/Element.h"
class Serializer;

/**
 *  The main abstract class for serialization.
 *  All possible classes that can be serialized
 *  need to implement this interface.
 *  @see Serializer
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class Component
{
    public:

        /**
         *  A default virtual destructor
         */
        virtual ~Component();

        /**
         *  A default constructor for initialization
         */
        Component();

        /**
         *  The method used by the serializer to transform
         *  an object into an Element representation.
         *  @see Element
         *
         *  @return The Element representation of the object
         */
        virtual Element* toElement() const = 0;

        /**
         *  The function called by the serializer to initialize
         *  the object if it is empty
         *  @see ElementObject
         *  @see Serializer
         *
         *  @param element The Element representation of the object
         *  @param s The serializer (Can be used if serialization of some elements is needed)
         *  @param encoding The encoding that has been used to create the Element representation of the object (Can be used if serialization of some elements is needed)
         */
        void __init__(ElementObject* element, const Serializer* s, const char* encoding) { if(!initialized) this->fromElement(element, s, encoding); initialized = true; delete element;}
    protected:

        /**
         *  The function used to build the object from
         *  its element representation.
         *  the object if it is empty
         *  @see ElementObject
         *  @see Serializer
         *
         *  @param element The Element representation of the object
         *  @param s The serializer (Can be used if serialization of some elements is needed)
         *  @param encoding The encoding that has been used to create the Element representation of the object (Can be used if serialization of some elements is needed)
         */
        virtual void fromElement(ElementObject*, const Serializer*, const char* encoding) = 0;
    private:

        /**
         *  The boolean to check if the object has already been built.
         */
        bool initialized = false;
};

#endif // COMPONENT_H
