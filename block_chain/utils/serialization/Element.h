#ifndef ELEMENT_H
#define ELEMENT_H
#include <vector>
#include <map>
#include <cstring>
#include "Parser.h"

/**
 *  The Element base class for serialization
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class Element
{
    public:
        /**
         *  Used with polymorphism, lead the readers in the right direction for both
         *  text and Element creation.
         *  @see ContentReader
         *
         *  @param text the current used text by the reader
         *  @param reader the current reader used
         */
        virtual void read(std::string& text, const ContentReader* reader) {};

        /**
         * Default destructor
         */
        virtual ~Element() = default;
};

/**
 *  The int Element for serialization
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ElementInt: public Element
{
    public:
        /**
         * The long long int value to be used in serialization
         */
        long long int value;
        void read(std::string& text, const ContentReader* parser) override;
};


/**
 *  The double Element for serialization
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ElementDouble: public Element
{
    public:
        /**
         * The double value to be used in serialization
         */
        double value;
        void read(std::string& text, const ContentReader* parser) override;
};


/**
 *  The string Element for serialization
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ElementString: public Element
{
    public:
        /**
         * The string value to be used in serialization
         */
        std::string value;
        void read(std::string& text, const ContentReader* parser) override;
};


/**
 *  The boolean Element for serialization
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ElementBoolean: public Element
{
    public:
        /**
         * The boolean value to be used in serialization
         */
        bool value;
        void read(std::string& text, const ContentReader* parser) override;
};


/**
 *  The array Element for serialization
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ElementArray: public Element
{
    public:

        /**
         * The list of Elements to be used in serialization
         * @see Element
         */
        std::vector<Element*> values;
        void read(std::string& text, const ContentReader* parser) override;

        /**
         * Add an Element to the array.
         * Works as a builder
         * @see Element
         *
         * @param value the new value to append to the array
         * @return the ElementArray to be used as a builder
         */
        ElementArray* add(Element* value);

        /**
         * Destructor that free all of the values in the array
         */
        ~ElementArray() override;
};


/**
 *  The object Element for serialization
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ElementObject: public Element
{
    /**
     * The comparator to be used to assure the order of the fields
     * Since the keys in the map are string pointers, the map
     * is ordered by address. The comparator prefers an
     * alphabetical order based on the values
     *
     * @param str1 pointer of string
     * @param str2 pointer of string
     * @return true is *str1 should be before *str2
     */
    struct Comparator {
        bool operator() (const std::string* str1, const std::string* str2) const
        {
                return *str1 < *str2;
        }
    };
    public:
        /**
         * The map of <string, Elements> to be used in serialization
         * @see Element
         */
        std::map<std::string*, Element*, Comparator> values;

        /**
         * get an int value from the map
         *
         * @param key the name of the field
         * @param value a pointer of int to be updated
         */
        void getItem(const char* key, int* value);

        /**
         * get a long long int value from the map
         *
         * @param key the name of the field
         * @param value a pointer of long long int to be updated
         */
        void getItem(const char* key, long long int* value);

        /**
         * get a bool value from the map
         *
         * @param key the name of the field
         * @param value a pointer of bool to be updated
         */
        void getItem(const char* key, bool* value);

        /**
         * get a double value from the map
         *
         * @param key the name of the field
         * @param value a pointer of double to be updated
         */
        void getItem(const char* key, double* value);

        /**
         * get an ElementObject value from the map
         *
         * @param key the name of the field
         * @param value a pointer of ElementObject pointer to be updated
         */
        void getItem(const char* key, ElementObject** value);

        /**
         * get an ElementArray value from the map
         *
         * @param key the name of the field
         * @param value a pointer of ElementArray pointer to be updated
         */
        void getItem(const char* key, ElementArray** value);

        /**
         * get a string value from the map
         *
         * @param key the name of the field
         * @param value a pointer of string to be updated
         */
        void getItem(const char* key, std::string* value);
        void read(std::string& text, const ContentReader* parser) override;

        /**
         * Add an Element to the map.
         * Works as a builder
         * @see Element
         *
         * @param key the name of the field
         * @param value the new value to append to the object
         * @return the ElementObject to be used as a builder
         */
        ElementObject* put(const char* key, Element* value);

        /**
         * Destructor that free all of the values in the map
         */
        ~ElementObject() override;
};

#endif // ELEMENT_H
