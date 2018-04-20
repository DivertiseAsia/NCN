#ifndef BLOCK_CHAIN_JSON_PARSER_H
#define BLOCK_CHAIN_JSON_PARSER_H

#include "../Parser.h"
#include <functional>
#include <map>

/**
 *  A parser conceived to parse any json file in an Element representation
 *  @see ContentParser
 *  @see Element
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
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
        const char* get_encoding() const override;

        /**
         * The parser constructor: initialize the map of different
         * possible elements
         */
        JsonParser();

        /**
         * The parser destructor: frees the map of elements
         */
        ~JsonParser();
    private:
        /**
         * The map of elements: its goal is to generate
         * corresponding element for a given situation.
         *
         * It is a small builder.
         */
        std::map<const char, std::function<Element*()>> elements;
};
#endif //BLOCK_CHAIN_JSON_PARSER_H
