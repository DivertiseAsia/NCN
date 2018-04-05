#ifndef JSONPARSER_H
#define JSONPARSER_H
#include "../Parser.hpp"
#include <functional>
#include <map>
class ContentParser;
class JsonParser: public ContentParser
{
    public:
        void parse(std::string& text, Element** e) const;
        void parseContent(std::string& text, ElementInt* e) const;
        void parseContent(std::string& text, ElementString* e) const;
        void parseContent(std::string& text, ElementBoolean* e) const;
        void parseContent(std::string& text, ElementArray* e) const;
        void parseContent(std::string& text, ElementObject* e) const;
        void parseContent(std::string& text, ElementDouble* e) const;
        JsonParser();
        ~JsonParser();
    private:
        std::map<const char, std::function<Element*()>> elements;
};
#endif //JSONPARSER_H
