#ifndef PARSING_FRAMEWORK_H
#define PARSING_FRAMEWORK_H
#include <string>

class Element;
class ElementInt;
class ElementString;
class ElementBoolean;
class ElementArray;
class ElementObject;
class ElementDouble;
class ContentReader
{
	public:
		virtual void parse(std::string& text, Element** e) const = 0;
		virtual void parseContent(std::string& text, ElementInt* e) const = 0;
		virtual void parseContent(std::string& text, ElementString* e) const = 0;
		virtual void parseContent(std::string& text, ElementBoolean* e) const = 0;
		virtual void parseContent(std::string& text, ElementArray* e) const = 0;
		virtual void parseContent(std::string& text, ElementObject* e) const = 0;
		virtual void parseContent(std::string& text, ElementDouble* e) const = 0;
};

class ContentParser: public ContentReader
{
	public:
		ContentParser() = default;
};

class ContentCreator: public ContentReader
{
	public:
		ContentCreator() = default;
};

class ElementCreator
{
	public:
		static ElementInt* create(int value);
		static ElementDouble* create(double value);
		static ElementString* create(const char* value);
		static ElementString* create(std::string value);
		static ElementBoolean* create(bool value);

		static ElementArray* array();
		static ElementObject* object();
		static ElementArray* add(ElementArray* e, Element* value);
		static ElementObject* put(ElementObject* e, const char* key, Element* value);
	private:
		ElementCreator();
		~ElementCreator();
};
#endif //PARSING_FRAMEWORK_H
