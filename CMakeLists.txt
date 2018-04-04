cmake_minimum_required(VERSION 3.10)
project(block_chain)

set(CMAKE_CXX_STANDARD 11)

add_executable(block_chain main.cpp block_chain/chain/NodeState.h block_chain/chain/NodeState.cpp block_chain/chain/block/Block.h block_chain/chain/block/Hash.h block_chain/Node.h block_chain/chain/block/transaction/Transaction.cpp block_chain/chain/block/transaction/Transaction.h block_chain/Validator.cpp block_chain/Validator.h block_chain/Node.cpp block_chain/chain/block/Block.cpp block_chain/chain/block/Hash.cpp block_chain/Listener.cpp block_chain/Listener.h block_chain/socket/SocketServer.cpp block_chain/socket/SocketServer.h block_chain/socket/Socket.cpp block_chain/socket/Socket.h block_chain/socket/Peer.cpp block_chain/socket/Peer.h validator/CustomValidator.cpp validator/CustomValidator.h transactions/StatusTransaction.cpp transactions/StatusTransaction.h transactions/MessagesTransaction.cpp transactions/MessagesTransaction.h block_chain/Serializer.cpp block_chain/Serializer.h)