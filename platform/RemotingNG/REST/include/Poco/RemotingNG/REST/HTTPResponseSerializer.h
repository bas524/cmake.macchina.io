#ifndef RemotingNG_HTTPResponseSerializer_INCLUDED
#define RemotingNG_HTTPResponseSerializer_INCLUDED

#include "REST.h"

#include <Poco/RemotingNG/Serializer.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/JSON/Object.h>
#include <Poco/Mutex.h>

namespace Poco
{
namespace RemotingNG
{
namespace REST
{

/// @brief HTTPResponse serializer
/// @see Poco::RemotingNG::Serializer
class RemotingNGREST_API HTTPResponseSerializer : public Serializer
{
public:
    explicit HTTPResponseSerializer(Poco::Net::HTTPServerResponse& httpResponse);
    /// @see Poco::RemotingNG::Serializer
    void serializeMessageBegin(const std::string& name, SerializerBase::MessageType type) override;
    /// @see Poco::RemotingNG::Serializer
    void serializeMessageEnd(const std::string& name, SerializerBase::MessageType type) override;
    /// @see Poco::RemotingNG::Serializer
    void serializeFaultMessage(const std::string& name, Poco::Exception& exc) override;
    /// @see Poco::RemotingNG::Serializer
    void serializeStructBegin(const std::string& name) override;
    /// @see Poco::RemotingNG::Serializer
    void serializeStructEnd(const std::string& name) override;
    /// @see Poco::RemotingNG::Serializer
    void serializeSequenceBegin(const std::string& name, Poco::UInt32 length) override;
    /// @see Poco::RemotingNG::Serializer
    void serializeSequenceEnd(const std::string& name) override;
    /// @see Poco::RemotingNG::Serializer
    void serializeNullableBegin(const std::string& name, bool isNull) override;
    /// @see Poco::RemotingNG::Serializer
    void serializeNullableEnd(const std::string& name) override;
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, Poco::Int8 value) override;
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, Poco::UInt8 value) override;
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, Poco::Int16 value) override;
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, Poco::UInt16 value) override;
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, Poco::Int32 value) override;
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, Poco::UInt32 value) override;
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, long value) override;
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, unsigned long value) override;
#ifndef POCO_INT64_IS_LONG
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, Poco::Int64 value) override;
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, Poco::UInt64 value) override;
#endif
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, float value) override;
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, double value) override;
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, bool value) override;
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, char value) override;
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, const std::string& value) override;
    /// @see Poco::RemotingNG::Serializer
    void serialize(const std::string& name, const std::vector<char>& value) override;

protected:
    void resetImpl() override;
    void setupImpl(std::ostream& ostr) override;

private:
    void SetValue(const std::string& name, const Poco::Dynamic::Var& value);

private:
    Poco::Net::HTTPServerResponse& m_httpResponse;
    std::stack<Poco::Dynamic::Var> m_stack;
    Poco::Dynamic::Var m_result;
    Poco::FastMutex m_mutex;
};

}  // namespace REST
}  // namespace RemotingNG
}  // namespace Poco


#endif  // RemotingNG_HTTPResponseSerializer_INCLUDED
