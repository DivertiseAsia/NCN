#include "JsonCreator.h"
#include "../Element.h"

JsonCreator::JsonCreator() = default;

JsonCreator::~JsonCreator() = default;

const char* JsonCreator::get_encoding() const{
    return "json";
}

void JsonCreator::parse(std::string& text, Element** e) const{
    if(*e)
        (*e)->read(text, this);
}

void JsonCreator::parseContent(std::string& text, ElementDouble* e) const
{
    text.append(std::to_string(e->value));
}

void JsonCreator::parseContent(std::string& text, ElementInt* e) const
{
    text.append(std::to_string(e->value));
}

void escape(std::string& text){
    char c = '\\';
    for(int i = 0; i < text.size(); i++){
        if(text[i] == '"' && (!i || text[i-1] != '\\'))
            text.insert(i, 1, c);
    }
}

void JsonCreator::parseContent(std::string& text, ElementString* e) const
{
    escape(e->value);
    text.append("\"").append(e->value).append("\"");
}

void JsonCreator::parseContent(std::string& text, ElementBoolean* e) const
{
    text.append(e->value ? "true" : "false");
}

void JsonCreator::parseContent(std::string& text, ElementArray* e) const
{
    text.append("[");
    for(std::vector<Element*>::const_iterator it = e->values.begin(); it != e->values.end(); it++)
    {
        if(it != e->values.begin())
            text.append(",");
        (*it)->read(text, this);
    }
    text.append("]");
}

void JsonCreator::parseContent(std::string& text, ElementObject* e) const
{
    text.append("{");
    for(std::map<std::string*, Element*>::const_iterator it = e->values.begin(); it != e->values.end(); it++)
    {
        if(it != e->values.begin())
            text.append(",");
        text.append("\"").append(*(it->first)).append("\":");
        it->second->read(text, this);
    }
    text.append("}");
}

