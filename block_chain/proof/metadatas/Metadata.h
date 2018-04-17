//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_METADATA_H
#define BLOCK_CHAIN_METADATA_H


#include "../../utils/serialization/Element.hpp"
#include "../../chain/block/Component.h"

class Metadata:public Component{
public:
    virtual ~Metadata();
    virtual bool operator==(Metadata& m) const{
        return false;
    }
    //virtual Element* toElement() const;
    //virtual void fromElement(ElementObject* e, const Serializer* serializer, const char* encoding);
    
};
#endif //BLOCK_CHAIN_METADATA_H
