#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "../Parser.hpp"
#include <functional>
#include <map>

class JsonParser: public ContentParser
{
    public:
        void parse(std::string& text, Element** e) const override;
        void parseContent(std::string& text, ElementInt* e) const override;
        void parseContent(std::string& text, ElementString* e) const override;
        void parseContent(std::string& text, ElementBoolean* e) const override;
        void parseContent(std::string& text, ElementArray* e) const override;
        void parseContent(std::string& text, ElementObject* e) const override;
        void parseContent(std::string& text, ElementDouble* e) const override;
        JsonParser();
        ~JsonParser();
    private:
        std::map<const char, std::function<Element*()>> elements;
};
#endif //JSON_PARSER_H
