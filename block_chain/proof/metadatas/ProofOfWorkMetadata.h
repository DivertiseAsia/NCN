//
// Created by default on 17/4/2561.
//

#ifndef BLOCK_CHAIN_PROOF_OF_WORK_METADATA_H
#define BLOCK_CHAIN_PROOF_OF_WORK_METADATA_H


#include "Metadata.h"

class ProofOfWorkMetadata: public Metadata {
    friend class ProofOfWork;
public:
    ProofOfWorkMetadata();
    ProofOfWorkMetadata(double, double);
    bool operator==(Metadata& m) const override {
        auto pwm = dynamic_cast<ProofOfWorkMetadata*>(&m);
        return pwm->first == first && pwm->second == second;
    }
    Element* toElement() const override;
protected:
    void fromElement(ElementObject* e, const Serializer* s, const char* encoding) override;
private:
    double first;
    double second;
};


#endif //BLOCK_CHAIN_PROOF_OF_WORK_METADATA_H
