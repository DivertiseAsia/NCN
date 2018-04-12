#include "JsonCreator.hpp"
#include "../Element.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstring>

/*
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}*/
template<typename Out>
void split(const std::string &s, char lim, Out result, const int limit) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    int i = 0;
    while (i++ < limit || limit < 0 ? std::getline(ss, item, lim) : std::getline(ss, item)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char lim, const int limit = -1) {
    std::vector<std::string> e;
    split(s, lim, std::back_inserter(e), limit);
    return e;
}


JsonCreator::JsonCreator(): ContentCreator(){
}

JsonCreator::~JsonCreator() = default;

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

