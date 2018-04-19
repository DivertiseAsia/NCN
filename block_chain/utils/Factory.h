#ifndef FACTORY_H
#define FACTORY_H
#include <iostream>
#include <map>
#include <cstring>


/**
 *  A factory is a particular type of map.
 *  it takes a const char* as key and V as values.
 *  It does provide higher level manipulation than
 *  classical map.
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
template<typename V> class Factory
{
    /**
     * Definition of the iterator type
     */
    typedef typename std::map<const char*, V>::const_iterator factory_iterator;
    private:

        /**
         * Compare two strings.
         *
         * @param key the key from the map
         * @param given the given string given for evaluation
         * @return 1 if equals, 0 otherwise
         */
        const int key_cmp(const char* key, const char* given) const{
            int i = 0;
            for(; key[i] != '\0' &&  given[i] != '\0' && key[i] == given[i];i++);
            return key[i] == given[i];
        }

        /**
         * The map in the factory
         */
        std::map<const char*, V> items;
	public:

        /**
         * Add a new value in the map
         *
         * @param key the key of the value
         * @param value the new value
         */
		void put(const char* key, V value);

		/**
		 * Get the value from the map.
		 *
		 * @param key the key the user provides
		 * @return the value the key represents
		 */
		V get(const char* key) const;

        /**
         * Get the begin iterator value from the factory.
         *
         * @return the begin iterator on the factory
         */
		factory_iterator begin(){
            return items.begin();
        }

        /**
         * Get the end iterator value from the factory.
         *
         * @return the end iterator on the factory
         */
        factory_iterator end(){
            return items.end();
        }

        /**
         * Get the visual representation of the factory.
         *
         * @return the visual representation of the factory.
         */
        std::string toString(const char* equal, const char* separator) const {
            std::string str;
            for(typename std::map<const char*, V>::const_iterator it = items.begin(); it != items.end(); ++it) {
                if(it != items.begin())
                    str.append(separator);
                str.append(it->first);
                str.append(equal);
                str.append(it->second);
            }
            return str;
        }
};

template <typename V> V Factory<V>::get(const char* key) const{
    for(typename std::map<const char*, V>::const_iterator it = items.begin(); it != items.end(); ++it) {
        if(key_cmp(it->first, key))
            return it->second;
    }
    return nullptr;
}

template <typename V> void Factory<V>::put(const char* key, const V value){
    items.insert(std::pair<const char*, V>(key, value));
}
#endif //FACTORY_H
