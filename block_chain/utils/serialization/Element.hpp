#ifndef ELEMENT_H
#define ELEMENT_H
#include <vector>
#include <map>
#include <cstring>
#include "Parser.hpp"

class ContentReader;
class Element
{
    public:
        virtual void read(std::string& text, const ContentReader* parser) {};
        virtual ~Element(){
        }
};

class ElementInt: public Element
{
    public:
        int value;
        void read(std::string& text, const ContentReader* parser);
};

class ElementDouble: public Element
{
    public:
        double value;
        void read(std::string& text, const ContentReader* parser);
};

class ElementString: public Element
{
    public:
        std::string value;
        void read(std::string& text, const ContentReader* parser);
};

class ElementBoolean: public Element
{
    public:
        bool value;
        void read(std::string& text, const ContentReader* parser);
};

class ElementArray: public Element
{
    public:
        std::vector<Element*> values;
        void read(std::string& text, const ContentReader* parser);
        ElementArray* add(Element* value);
        ~ElementArray();
};

class ElementObject: public Element
{
    public:
        std::map<std::string*, Element*> values;
        void getItem(const char* key, int* value);
        void getItem(const char* key, bool* value);
        void getItem(const char* key, double* value);
        void getItem(const char* key, ElementObject** value);
        void getItem(const char* key, ElementArray** value);
        void getItem(const char* key, std::string* value);
        void read(std::string& text, const ContentReader* parser);
        ElementObject* put(const char* key, Element* value);
        ~ElementObject();
};

#endif // ELEMENT_H
