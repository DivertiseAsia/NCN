//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_METADATA_H
#define BLOCK_CHAIN_METADATA_H


#include "../../utils/serialization/Element.hpp"
class Metadata{
public:
    bool operator==(Metadata const& m) const{
        return true;
    }
    Element* toElement() const;
    void fromElement(ElementObject* e);
    
};
#endif //BLOCK_CHAIN_METADATA_H
