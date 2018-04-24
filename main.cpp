#include <iostream>

#include "serializer/CustomSerializer.h"
#include "block_chain/Node.h"
#include "block_chain/TransactionManager.h"
#include "block_chain/chain/block/proof/Proof.h"
#include "transactions/StatusTransaction.h"
#include "transactions/MessagesTransaction.h"
#include "transactions/MoneyTransaction.h"
#include "reward/RewardTransaction.h"
#include "block_chain/kernel/components/Config.h"
/*
 * ls -R ./block_chain | awk '
/:$/&&f{s=$0;f=0}
/:$/&&!f{sub(/:$/,"");s=$0;f=1;next}
NF&&f{ print s"/"$0 }'| sed ':a;N;$!ba;s/\n/ /g'
 */
/*rand() % 1000+3000*/

int main() {
    //Custom block chain
    TransactionManager manager;
    manager.put(new StatusTransaction);
    manager.put(new MoneyTransaction);
    manager.put(new MessagesTransaction);
    Serializer* serial = new CustomSerializer();
    Reward* reward = new RewardTransaction();

    //initialization of the block chain
    Config config("./config.json", serial, Proof::WORK, reward);
    Node client(config);

    //launching the software
    //client.start(manager);
    return 0;
}
