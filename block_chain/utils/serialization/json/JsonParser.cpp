#include "JsonParser.h"
#include "../Element.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstring>

JsonParser::JsonParser(): ContentParser() {
    elements['{'] = []() -> Element*{return new ElementObject();};
    elements['['] = []() -> Element*{return new ElementArray();};
    elements['\"'] = []() -> Element*{return new ElementString();};
    elements['t'] = []() -> Element*{return new ElementBoolean();};
    elements['f'] = []() -> Element*{return new ElementBoolean();};
}
JsonParser::~JsonParser() = default;

const char* JsonParser::get_encoding() const{
    return "json";
}

void JsonParser::parse(std::string& text, Element** e) const
{
    unsigned long i = 0;
    for(i = 0;text[i] == '\t' || text[i] == ' ' || text[i] == ','; i++);
    text = text.substr(i);
    char first = text[0];

    auto it = elements.find(first);
    if(it == elements.end()){
        for(i = 0; text[i] < 0x3A && text[i] > 0x2F ; i++);
        if(text[i] == '.')
            *e = new ElementDouble();
        else
            *e = new ElementInt();
    }
    else
        *e = it->second();
    (*e)->read(text, this);
}

void JsonParser::parseContent(std::string& text, ElementDouble* e) const
{
    double total = 0;
    int div = 0;
    unsigned long i;
    for(i = 0; (text[i] < 0x3A && text[i] > 0x2F) || text[i] == '.' ; i++)
    {
        if(text[i] == '.')
            div = 1;
        else
        {
            total = total*10 + (text[i] - 0x30);
            div *= 10;
        }
    }
    e->value = total/div;
    text = text.substr(i);
}

void JsonParser::parseContent(std::string& text, ElementInt* e) const
{
    long long int total = 0;
    unsigned long i;
    for(i = 0; text[i] < 0x3A && text[i] > 0x2F ; i++)
        total = total*10 + (text[i] - 0x30);
    e->value = total;
    text = text.substr(i);
}

void JsonParser::parseContent(std::string& text, ElementString* e) const
{
    unsigned int cpt = 0;
    std::string value;
    unsigned long i;
    for(i = 1; text[i] != '"' || (cpt&1)  ; i++)
    {
        if(text[i] == '\\')
        {
            cpt++;
            if(!(cpt&1))
                value += (text[i]);
        }
        else if(text[i] == '"' && !(cpt&1))
            break;
        else
        {
            value += (text[i]);
            cpt = 0;
        }
    }
    i++;
    e->value = value;
    text = text.substr(i);
}

void JsonParser::parseContent(std::string& text, ElementBoolean* e) const
{
    unsigned long i;
    for(i = 0; text[i] < 0x7B && text[i] > 0x60 ; i++);
    e->value = text.substr(0, i) == "true";
    text = text.substr(i);
}

void JsonParser::parseContent(std::string& text, ElementArray* e) const
{
    std::string key;
    char end = text[1];
    text = text.substr(1);
    while(end != ']')
    {
        Element* child = nullptr;
        parse(text, &child);
        int i;
        for(i = 0;text[i] == '\t' || text[i] == ' ' || text[i] == ','; i++);
        end = text[0];
        e->values.push_back(child);
    }
    text = text.substr(1);
}

void JsonParser::parseContent(std::string& text, ElementObject* e) const
{
    text = text.substr(1);
    int start, i;
    unsigned int cpt;
    while(text[0] != '}')
    {
        Element* child = nullptr;
        std::string key;
        for(start = -1, cpt = 0, i = 0; ; i++)
        {
            if(start == -1)
            {
                if(text[i] == '"')
                    start = i;
            }
            else
            {
                if(text[i] == '\\')
                {
                    cpt++;
                    if(!(cpt&1))
                        key += (text[i]);
                }
                else if(text[i] == '"' && !(cpt&1)){
                    break;
                }
                else
                {
                    key += (text[i]);
                    cpt = 0;
                }
            }
        }
        int tmp = i;
        while(text[i++] != ':');
        text = text.substr((unsigned long)i);
        parse(text, &child);
        for(i = 0;text[i] == '\t' || text[i] == ' ' || text[i] == ','; i++);
        text = text.substr((unsigned long)i);
        e->values[new std::string(key)] = child;

    }
    text = text.substr(1);
}