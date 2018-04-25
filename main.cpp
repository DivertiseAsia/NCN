#include <iostream>

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

    //Possible transactions
    Transaction* status = new StatusTransaction;
    Transaction* money = new MoneyTransaction;
    Transaction* message = new MessagesTransaction;

    //Update in the manager
    TransactionManager manager;
    manager.put(status);
    manager.put(money);
    manager.put(message);

    //Serializer initialization
    auto serial = new Serializer();
    serial->add_transaction(status->get_type(), []() -> Transaction*{return new StatusTransaction;});
    serial->add_transaction(money->get_type(), []() -> Transaction*{return new MoneyTransaction;});
    serial->add_transaction(message->get_type(), []() -> Transaction*{return new MessagesTransaction;});

    //Reward object
    Reward* reward = new RewardTransaction();

    //Block chain initialization
    Config config("./config.json", serial, Proof::WORK, reward);
    Node client(config);

    //launching the loop
    client.start(manager);
    return 0;
}
