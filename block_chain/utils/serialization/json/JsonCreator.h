#ifndef BLOCK_CHAIN_JSON_CREATOR_H
#define BLOCK_CHAIN_JSON_CREATOR_H
#include "../Parser.h"
#include <functional>
#include <map>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstring>


/**
 *  @class JsonCreator "block_chain/utils/serialization/json/JsonCreator.h"
 *  A creator conceived to create any json file for given Elements
 *  @see ContentCreator
 *  @see Element
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
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
        const char* get_encoding() const override;

        /**
         * Default constructor
         */
        JsonCreator();

        /**
         * Default destructor
         */
        ~JsonCreator();
    private:
};
#endif //BLOCK_CHAIN_JSON_CREATOR_H
