#ifndef RemotingNG_HTTPRequestDeserializer_INCLUDED
#define RemotingNG_HTTPRequestDeserializer_INCLUDED

#include "REST.h"

#include <Poco/RemotingNG/Deserializer.h>
#include <Poco/RemotingNG/RemotingException.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/URI.h>
#include <Poco/Mutex.h>

namespace Poco
{
namespace RemotingNG
{
namespace REST
{

/// @brief HTTPRequest deserializer
/// @see Poco::RemotingNG::Deserializer
class RemotingNGREST_API HTTPRequestDeserializer : public Deserializer
{
public:
    explicit HTTPRequestDeserializer(Poco::Net::HTTPServerRequest& httpRequest);

    /// @see Poco::RemotingNG::Deserializer
    SerializerBase::MessageType findMessage(std::string& name) override;
    /// @see Poco::RemotingNG::Deserializer
    void deserializeMessageBegin(const std::string& name, SerializerBase::MessageType type) override;
    /// @see Poco::RemotingNG::Deserializer
    void deserializeMessageEnd(const std::string& name, SerializerBase::MessageType type) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserializeStructBegin(const std::string& name, bool isMandatory) override;
    /// @see Poco::RemotingNG::Deserializer
    void deserializeStructEnd(const std::string& name) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserializeSequenceBegin(const std::string& name, bool isMandatory, Poco::UInt32& lengthHint) override;
    /// @see Poco::RemotingNG::Deserializer
    void deserializeSequenceEnd(const std::string& name) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserializeNullableBegin(const std::string& name, bool isMandatory, bool& isNull) override;
    /// @see Poco::RemotingNG::Deserializer
    void deserializeNullableEnd(const std::string& name) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, Poco::Int8& value) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, Poco::UInt8& value) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, Poco::Int16& value) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, Poco::UInt16& value) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, Poco::Int32& value) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, Poco::UInt32& value) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, long& value) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, unsigned long& value) override;
#ifndef POCO_INT64_IS_LONG
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, Poco::Int64& value) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, Poco::UInt64& value) override;
#endif
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, float& value) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, double& value) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, bool& value) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, char& value) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, std::string& value) override;
    /// @see Poco::RemotingNG::Deserializer
    bool deserialize(const std::string& name, bool isMandatory, std::vector<char>& value) override;

private:
    void setupImpl(std::istream& inStream) override;
    void resetImpl() override;

    template<typename T>
    bool getValue(const std::string& name, bool isMandatory, T& value)
    {
        try
        {
            if (m_stack.empty())
            {
                throw Poco::LogicException("Attempt to set value on an empty stack");
            }

            Poco::Dynamic::Var var;
            Poco::Dynamic::Var parent = m_stack.top().first;
            if (parent.type() == typeid(Poco::JSON::Array::Ptr))
            {
                Poco::JSON::Array::Ptr arr = parent.extract<Poco::JSON::Array::Ptr>();
                var = arr->get(m_stack.top().second++);
            }
            else if (parent.type() == typeid(Poco::JSON::Object::Ptr))
            {
                Poco::JSON::Object::Ptr obj = parent.extract<Poco::JSON::Object::Ptr>();
                var = obj->get(name);
            }
            value = var.extract<T>();
            return true;
        }
        catch (const Poco::Exception&)
        {
            if (isMandatory)
            {
                throw;
            }
            return false;
        }
    }

    template<typename T>
    bool getPathValue(const std::string& name, bool isMandatory, T& value)
    {
        try
        {
            Poco::URI uri{m_httpRequest.getURI()};
            std::vector<std::string> segments;
            uri.getPathSegments(segments);
            if (segments.empty())
            {
                throw Poco::NotFoundException(name);
            }
            /// @todo support non-last values parsing e.g. /api/1.0/events_registry/{path}/events
            Poco::Dynamic::Var var{segments.back()};
            value = var.convert<T>();
            return true;
        }
        catch (const Poco::Exception&)
        {
            if (isMandatory)
            {
                throw;
            }
            return false;
        }
    }

    template<typename T>
    bool getQueryValue(const std::string& name, bool isMandatory, T& value)
    {
        try
        {
            Poco::URI uri(m_httpRequest.getURI());
            URI::QueryParameters queryParameters = uri.getQueryParameters();
            auto iterator = std::find_if(
                std::cbegin(queryParameters),
                std::cend(queryParameters),
                [&name](const std::pair<std::string, std::string>& arg) -> bool { return arg.first == name; });

            if (iterator == std::cend(queryParameters))
            {
                throw Poco::NotFoundException(name);
            }
            Poco::Dynamic::Var var{iterator->second};
            value = var.convert<T>();
            return true;
        }
        catch (const Poco::Exception&)
        {
            if (isMandatory)
            {
                throw;
            }
            return false;
        }
    }

    template<typename T>
    bool deserialize(const std::string& name, bool isMandatory, T& value)
    {
        if (hasProperty(Poco::RemotingNG::SerializerBase::PROP_LOCATION))
        {
            const std::string location{getProperty(Poco::RemotingNG::SerializerBase::PROP_LOCATION)};
            if (location == "path")
            {
                return getPathValue(name, isMandatory, value);
            }
            if (location == "query")
            {
                return getQueryValue(name, isMandatory, value);
            }
            if (isMandatory)
            {
                throw Poco::NotFoundException(name);
            }
            return false;
        }
        else
        {
            return getValue(name, isMandatory, value);
        }
    }

private:
    Poco::Net::HTTPServerRequest& m_httpRequest;
    Poco::JSON::Parser m_parser;
    std::stack<std::pair<Poco::Dynamic::Var, UInt32>> m_stack;
    Poco::Dynamic::Var m_input;
    Poco::FastMutex m_mutex;
};

}  // namespace REST
}  // namespace RemotingNG
}  // namespace Poco


#endif  // RemotingNG_HTTPRequestDeserializer_INCLUDED
