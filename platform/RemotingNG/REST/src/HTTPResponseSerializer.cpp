#include <Poco/RemotingNG/REST/HTTPResponseSerializer.h>
#include <Poco/Net/MediaType.h>

namespace Poco
{
namespace RemotingNG
{
namespace REST
{

HTTPResponseSerializer::HTTPResponseSerializer(Poco::Net::HTTPServerResponse& httpResponse)
    : m_httpResponse(httpResponse)
{}

void HTTPResponseSerializer::serializeMessageBegin(const std::string& name, SerializerBase::MessageType type)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    if (type == SerializerBase::MessageType::MESSAGE_REPLY)
    {
        m_httpResponse.setStatus(Net::HTTPResponse::HTTPStatus::HTTP_OK);
    }
    else
    {
        throw Poco::InvalidArgumentException("unsupported message type");
    }
}

void HTTPResponseSerializer::serializeMessageEnd(const std::string& name, SerializerBase::MessageType type)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    if (type == SerializerBase::MessageType::MESSAGE_REPLY)
    {
        m_httpResponse.setContentType(Poco::Net::MediaType("application", "json"));
        if (m_result.type() == typeid(Poco::JSON::Array::Ptr))
        {
            Poco::JSON::Array::Ptr arr = m_result.extract<Poco::JSON::Array::Ptr>();
            arr->stringify(m_httpResponse.send());
        }
        else if (m_result.type() == typeid(Poco::JSON::Object::Ptr))
        {
            Poco::JSON::Object::Ptr obj = m_result.extract<Poco::JSON::Object::Ptr>();
            obj->stringify(m_httpResponse.send());
        }
        else
        {
            m_httpResponse.send();
        }
    }
    else
    {
        throw Poco::InvalidArgumentException("unsupported message type");
    }
}

void HTTPResponseSerializer::serializeFaultMessage(const std::string& name, Exception& exc)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    m_httpResponse.setStatusAndReason(Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST, exc.displayText());
    m_httpResponse.send();
}

void HTTPResponseSerializer::serializeStructBegin(const std::string& name)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    Poco::JSON::Object::Ptr newObj = new Poco::JSON::Object();
    if (m_stack.empty())
    {
        m_result = newObj;
    }
    else
    {
        Poco::Dynamic::Var parent = m_stack.top();
        if (parent.type() == typeid(Poco::JSON::Array::Ptr))
        {
            Poco::JSON::Array::Ptr array = parent.extract<Poco::JSON::Array::Ptr>();
            array->add(newObj);
        }
        else if (parent.type() == typeid(Poco::JSON::Object::Ptr))
        {
            Poco::JSON::Object::Ptr obj = parent.extract<Poco::JSON::Object::Ptr>();
            obj->set(name, newObj);
        }
    }

    m_stack.push(std::move(newObj));
}

void HTTPResponseSerializer::serializeStructEnd(const std::string& name)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    if (!m_stack.empty())
    {
        m_stack.pop();
    }
    else
    {
        throw Poco::LogicException("Attempt to pop on an empty stack");
    }
}

void HTTPResponseSerializer::serializeSequenceBegin(const std::string& name, Poco::UInt32 length)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    Poco::JSON::Array::Ptr newArr = new Poco::JSON::Array();
    if (m_stack.empty())  // The first array
    {
        m_result = newArr;
    }
    else
    {
        Poco::Dynamic::Var parent = m_stack.top();
        if (parent.type() == typeid(Poco::JSON::Array::Ptr))
        {
            Poco::JSON::Array::Ptr arr = parent.extract<Poco::JSON::Array::Ptr>();
            arr->add(newArr);
        }
        else if (parent.type() == typeid(Poco::JSON::Object::Ptr))
        {
            Poco::JSON::Object::Ptr obj = parent.extract<Poco::JSON::Object::Ptr>();
            obj->set(name, newArr);
        }
    }

    m_stack.push(std::move(newArr));
}

void HTTPResponseSerializer::serializeSequenceEnd(const std::string& name)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    if (!m_stack.empty())
    {
        m_stack.pop();
    }
    else
    {
        throw Poco::LogicException("Attempt to pop on an empty stack");
    }
}

void HTTPResponseSerializer::serializeNullableBegin(const std::string& name, bool isNull)
{
    /// @todo implement
    throw Poco::NotImplementedException("nullable serialization is not implemented");
}

void HTTPResponseSerializer::serializeNullableEnd(const std::string& name)
{
    /// @todo implement
    throw Poco::NotImplementedException("nullable serialization is not implemented");
}

void HTTPResponseSerializer::serialize(const std::string& name, Poco::Int8 value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}

void HTTPResponseSerializer::serialize(const std::string& name, Poco::UInt8 value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}

void HTTPResponseSerializer::serialize(const std::string& name, Poco::Int16 value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}

void HTTPResponseSerializer::serialize(const std::string& name, Poco::UInt16 value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}

void HTTPResponseSerializer::serialize(const std::string& name, Poco::Int32 value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}

void HTTPResponseSerializer::serialize(const std::string& name, Poco::UInt32 value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}

void HTTPResponseSerializer::serialize(const std::string& name, long value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}

void HTTPResponseSerializer::serialize(const std::string& name, unsigned long value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}

#ifndef POCO_INT64_IS_LONG
void HTTPResponseSerializer::serialize(const std::string& name, Poco::Int64 value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}

void HTTPResponseSerializer::serialize(const std::string& name, Poco::UInt64 value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}
#endif

void HTTPResponseSerializer::serialize(const std::string& name, float value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}

void HTTPResponseSerializer::serialize(const std::string& name, double value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}

void HTTPResponseSerializer::serialize(const std::string& name, bool value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}

void HTTPResponseSerializer::serialize(const std::string& name, char value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}

void HTTPResponseSerializer::serialize(const std::string& name, const std::string& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}

void HTTPResponseSerializer::serialize(const std::string& name, const std::vector<char>& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    SetValue(name, value);
}

void HTTPResponseSerializer::resetImpl() {}

void HTTPResponseSerializer::setupImpl(std::ostream& ostr) {}

void HTTPResponseSerializer::SetValue(const std::string& name, const Poco::Dynamic::Var& value)
{
    if (m_stack.size())
    {
        Poco::Dynamic::Var parent = m_stack.top();
        if (parent.type() == typeid(Poco::JSON::Array::Ptr))
        {
            Poco::JSON::Array::Ptr arr = parent.extract<Poco::JSON::Array::Ptr>();
            arr->add(value);
        }
        else if (parent.type() == typeid(Poco::JSON::Object::Ptr))
        {
            Poco::JSON::Object::Ptr obj = parent.extract<Poco::JSON::Object::Ptr>();
            obj->set(name, value);
        }
    }
    else
    {
        throw Poco::LogicException("Attempt to set value on an empty stack");
    }
}

}  // namespace REST
}  // namespace RemotingNG
}  // namespace Poco