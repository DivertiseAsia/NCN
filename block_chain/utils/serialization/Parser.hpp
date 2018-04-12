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
		static ElementCreator creator;
		ElementInt* create(int value) const;
		ElementDouble* create(double value) const;
		ElementString* create(const char* value) const;
		ElementString* create(std::string value) const;
		ElementBoolean* create(bool value) const;

		ElementArray* array() const;
		ElementObject* object() const;
		ElementCreator* add(ElementArray* e, Element* value);
		ElementCreator* put(ElementObject* e, const char* key, Element* value);
	private:
		ElementCreator();
		~ElementCreator();
};
#endif //PARSING_FRAMEWORK_H
