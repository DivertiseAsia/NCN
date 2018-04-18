#ifndef ELEMENT_H
#define ELEMENT_H
#include <vector>
#include <map>
#include <cstring>
#include "Parser.hpp"

class Element
{
    public:
        virtual void read(std::string& text, const ContentReader* parser) {};
        virtual ~Element() = default;
};

class ElementInt: public Element
{
    public:
        long long int value;
        void read(std::string& text, const ContentReader* parser) override;
};

class ElementDouble: public Element
{
    public:
        double value;
        void read(std::string& text, const ContentReader* parser) override;
};

class ElementString: public Element
{
    public:
        std::string value;
        void read(std::string& text, const ContentReader* parser) override;
};

class ElementBoolean: public Element
{
    public:
        bool value;
        void read(std::string& text, const ContentReader* parser) override;
};

class ElementArray: public Element
{
    public:
        std::vector<Element*> values;
        void read(std::string& text, const ContentReader* parser) override;
        ElementArray* add(Element* value);
        ~ElementArray() override;
};

class ElementObject: public Element
{
    struct Comparator {
        bool operator() (const std::string* str1, const std::string* str2) const
        {
                return *str1 < *str2;
        }
    };
    public:
        std::map<std::string*, Element*, Comparator> values;
        void getItem(const char* key, int* value);
        void getItem(const char* key, long long int* value);
        void getItem(const char* key, bool* value);
        void getItem(const char* key, double* value);
        void getItem(const char* key, ElementObject** value);
        void getItem(const char* key, ElementArray** value);
        void getItem(const char* key, std::string* value);
        void read(std::string& text, const ContentReader* parser) override;
        ElementObject* put(const char* key, Element* value);
        ~ElementObject() override;
};

#endif // ELEMENT_H
