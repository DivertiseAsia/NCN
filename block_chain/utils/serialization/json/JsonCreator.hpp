#ifndef JSONCREATOR_H
#define JSONCREATOR_H
#include "../Parser.hpp"
#include <functional>
#include <map>

class JsonCreator: public ContentCreator
{
    public:
        void parse(std::string& text, Element** e) const override;
        void parseContent(std::string& text, ElementInt* e) const override;
        void parseContent(std::string& text, ElementString* e) const override;
        void parseContent(std::string& text, ElementBoolean* e) const override;
        void parseContent(std::string& text, ElementArray* e) const override;
        void parseContent(std::string& text, ElementObject* e) const override;
        void parseContent(std::string& text, ElementDouble* e) const override;
        JsonCreator();
        ~JsonCreator();
    private:
};
#endif //JSONCREATOR_H
