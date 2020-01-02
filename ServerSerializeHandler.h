#pragma once

#include <wangle/channel/Handler.h>

#include <thrift/test/gen-cpp2/ThriftTest.h>
#include <thrift/lib/cpp2/protocol/Serializer.h>

// Do some serialization / deserialization using thrift.
// A real rpc server would probably use generated client/server stubs
class ServerSerializeHandler : public wangle::Handler<
        std::unique_ptr<folly::IOBuf>, thrift::test::Bonk,
        thrift::test::Xtruct, std::unique_ptr<folly::IOBuf>> {
public:
    void read(Context* ctx, std::unique_ptr<folly::IOBuf> msg) override {
        thrift::test::Bonk received =
                apache::thrift::CompactSerializer::deserialize<thrift::test::Bonk>(
                        msg.get());
        ctx->fireRead(received);
    }

    folly::Future<folly::Unit> write(Context* ctx, thrift::test::Xtruct b)
    override {
        std::string out;
        apache::thrift::CompactSerializer::serialize(b, &out);
        return ctx->fireWrite(folly::IOBuf::copyBuffer(out));
    }
};