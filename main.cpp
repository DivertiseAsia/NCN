#include <iostream>

#include "serializer/CustomSerializer.h"
#include "block_chain/Node.h"
#include "block_chain/TransactionManager.h"
#include "block_chain/proof/Proof.h"
#include "transactions/StatusTransaction.h"
#include "transactions/MessagesTransaction.h"
#include "transactions/MoneyTransaction.h"
/*
 * ls -R ./block_chain | awk '
/:$/&&f{s=$0;f=0}
/:$/&&!f{sub(/:$/,"");s=$0;f=1;next}
NF&&f{ print s"/"$0 }'| sed ':a;N;$!ba;s/\n/ /g'
 */

int main() {
    srand (time(NULL));
    //Custom block chain
    Serializer* serial = new CustomSerializer();
    TransactionManager manager;
    manager.put(new StatusTransaction);
    manager.put(new MoneyTransaction);
    manager.put(new MessagesTransaction);

    //initialization of the block chain
    Node client(serial, /*rand() % 1000+3000*/3400, "json", Proof::WORK, true);
    //launching the software
    client.start(manager);
    return 0;
}