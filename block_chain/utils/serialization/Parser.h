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

/**
 *  An abstract reader.
 *  A reader is a class that generates Elements with a given string. It work in the opposite way as well
 *  @see Element
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ContentReader
{
	public:
		/**
		 *  The entry point of the parser: it reads the text and generate the first element
		 *  according to rules. Calls the corresponding methods for recursive parsing.
		 *  (opposite works as well)
		 *  @see parseContent
		 *  @see Element
		 *
		 * 	@param text a given text
		 * 	@param e the root Element that will be generated (or used)
		 */
		virtual void parse(std::string& text, Element** e) const = 0;

		/**
		 *  Generates an integer from a given string. Calls the method parse with the
		 *  rest of the string.
		 *  (opposite works as well)
		 *  @see parse
		 *  @see ElementInt
		 *
		 * 	@param text a given text
		 * 	@param e the int Element that will be generated (or used)
		 */
		virtual void parseContent(std::string& text, ElementInt* e) const = 0;

		/**
		 *  Generates an string from a given string. it stops with the defined rules of the parser.
		 *  Calls the method parse with the rest of the string.
		 *  (opposite works as well)
		 *  @see parse
		 *  @see ElementString
		 *
		 * 	@param text a given text
		 * 	@param e the string Element that will be generated (or used)
		 */
		virtual void parseContent(std::string& text, ElementString* e) const = 0;

		/**
		 *  Generates an boolean from a given string. Calls the method parse with the
		 *  rest of the string.
		 *  (opposite works as well)
		 *  @see parse
		 *  @see ElementBoolean
		 *
		 * 	@param text a given text
		 * 	@param e the boolean Element that will be generated (or used)
		 */
		virtual void parseContent(std::string& text, ElementBoolean* e) const = 0;

		/**
		 *  Generates an array of Elements from a given string. Calls the method parse with the
		 *  rest of the string and parse each of the found elements of the array.
		 *  (opposite works as well)
		 *  @see parse
		 *  @see Element
		 *  @see ElementArray
		 *
		 * 	@param text a given text
		 * 	@param e the array Element that will be generated (or used)
		 */
		virtual void parseContent(std::string& text, ElementArray* e) const = 0;

		/**
		 *  Generates an object of <key (string), Elements> from a given string. Calls the method parse with the
		 *  rest of the string and parse each of the found elements of the object.
		 *  (opposite works as well)
		 *  @see parse
		 *  @see Element
		 *  @see ElementObject
		 *
		 * 	@param text a given text
		 * 	@param e the object Element that will be generated (or used)
		 */
		virtual void parseContent(std::string& text, ElementObject* e) const = 0;

		/**
		 *  Generates an double from a given string. Calls the method parse with the
		 *  rest of the string.
		 *  (opposite works as well)
		 *  @see parse
		 *  @see ElementDouble
		 *
		 * 	@param text a given text
		 * 	@param e the double Element that will be generated (or used)
		 */
		virtual void parseContent(std::string& text, ElementDouble* e) const = 0;
};

/**
 *  An abstract parser.
 *  A parser is a particular reader that only works in the string to Element way.
 *  @see ContentReader
 *  @see Element
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ContentParser: public ContentReader
{
	public:
		ContentParser() = default;
};

/**
 *  An abstract creator.
 *  A creator is a particular reader that only works in the Element to string way.
 *  @see ContentReader
 *  @see Element
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ContentCreator: public ContentReader
{
	public:
		ContentCreator() = default;
};

/**
 *  The Element creator class is a static factory that can generates Elements for
 *  different primitive types.
 *  @see ElementInt
 *  @see ElementDouble
 *  @see ElementString
 *  @see ElementBoolean
 *  @see ElementArray
 *  @see ElementObject
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ElementCreator
{
	public:

		/**
		 *  Generates an Element representing a int
		 *  @see ElementInt
		 *
		 *  @param value the int value
		 *  @return the generated Element representation
		 */
		static ElementInt* create(int value);

		/**
		 *  Generates an Element representing a long long int
		 *  @see ElementInt
		 *
		 *  @param value the int value
		 *  @return the generated Element representation
		 */
		static ElementInt* create(long long int value);

		/**
		 *  Generates an Element representing a double
		 *  @see ElementDouble
		 *
		 *  @param value the double value
		 *  @return the generated Element representation
		 */
		static ElementDouble* create(double value);

		/**
		 *  Generates an Element representing a string
		 *  @see ElementString
		 *
		 *  @param value the const char* value
		 *  @return the generated Element representation
		 */
		static ElementString* create(const char* value);

		/**
		 *  Generates an Element representing a string
		 *  @see ElementString
		 *
		 *  @param value the string value
		 *  @return the generated Element representation
		 */
		static ElementString* create(std::string value);

		/**
		 *  Generates an Element representing a boolean
		 *  @see ElementBoolean
		 *
		 *  @param value the boolean value
		 *  @return the generated Element representation
		 */
		static ElementBoolean* create(bool value);

		/**
		 *  Generates an Element representing an array
		 *  @see ElementArray
		 *
		 *  @return the generated Element representation
		 */
		static ElementArray* array();

		/**
		 *  Generates an Element representing an object
		 *  @see ElementObject
		 *
		 *  @return the generated Element representation
		 */
		static ElementObject* object();

		/**
		 *  Add an Element to the given ElementArray.
		 *  Can be used as a builder.
		 *  @see ElementArray
		 *  @see Element
		 *
		 *  @param e ElementArray that will be updated
		 *  @param value the value that will be appended
		 *  @return the given ElementArray to be used as a builder.
		 */
		static ElementArray* add(ElementArray* e, Element* value);

		/**
		 *  Add a key and an Element to the given ElementObject.
		 *  Can be used as a builder.
		 *  @see ElementObject
		 *  @see Element
		 *
		 *  @param e ElementObject that will be updated
		 *  @param key the name of the field
		 *  @param value the value of the field
		 *  @return the given ElementObject to be used as a builder.
		 */
		static ElementObject* put(ElementObject* e, const char* key, Element* value);
};
#endif //PARSING_FRAMEWORK_H
