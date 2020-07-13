#include <Poco/RemotingNG/REST/HTTPRequestDeserializer.h>

namespace Poco
{
namespace RemotingNG
{
namespace REST
{
HTTPRequestDeserializer::HTTPRequestDeserializer(Poco::Net::HTTPServerRequest& httpRequest) : m_httpRequest(httpRequest)
{}

SerializerBase::MessageType HTTPRequestDeserializer::findMessage(std::string& name)
{
    const std::string method = m_httpRequest.getMethod();
    if (method == Poco::Net::HTTPRequest::HTTP_GET)
    {
        name = "get";
    }
    else if (method == Poco::Net::HTTPRequest::HTTP_POST)
    {
        name = "post";
    }
    else if (method == Poco::Net::HTTPRequest::HTTP_PATCH)
    {
        name = "patch";
    }
    else if (method == Poco::Net::HTTPRequest::HTTP_PUT)
    {
        name = "put";
    }
    else if (method == Poco::Net::HTTPRequest::HTTP_DELETE)
    {
        name = "delete_";
    }
    else
    {
        throw Poco::InvalidArgumentException(name);
    }
    return SerializerBase::MESSAGE_REQUEST;
}

void HTTPRequestDeserializer::deserializeMessageBegin(const std::string& name, SerializerBase::MessageType type)
{
    if (type != Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST)
    {
        throw Poco::InvalidArgumentException(type);
    }
}

void HTTPRequestDeserializer::deserializeMessageEnd(const std::string& name, SerializerBase::MessageType type)
{
    if (type != Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST)
    {
        throw Poco::InvalidArgumentException(type);
    }
}

bool HTTPRequestDeserializer::deserializeStructBegin(const std::string& name, bool isMandatory)
{
    try
    {
        Poco::FastMutex::ScopedLock lock(m_mutex);
        Poco::JSON::Object::Ptr newObj;
        if (m_stack.empty())
        {
            newObj = m_parser.parse(m_httpRequest.stream()).extract<Poco::JSON::Object::Ptr>();
        }
        else
        {
            Poco::Dynamic::Var parent = m_stack.top().first;
            if (parent.type() == typeid(Poco::JSON::Array::Ptr))
            {
                Poco::JSON::Array::Ptr array = parent.extract<Poco::JSON::Array::Ptr>();
                newObj = array->getObject(m_stack.top().second++);
            }
            else if (parent.type() == typeid(Poco::JSON::Object::Ptr))
            {
                Poco::JSON::Object::Ptr obj = parent.extract<Poco::JSON::Object::Ptr>();
                newObj = obj->getObject(name);
            }
        }

        poco_check_ptr(newObj);
        m_stack.emplace(std::move(newObj), 0);
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

void HTTPRequestDeserializer::deserializeStructEnd(const std::string& name)
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

bool HTTPRequestDeserializer::deserializeSequenceBegin(const std::string& name, bool isMandatory, UInt32& lengthHint)
{
    try
    {
        Poco::FastMutex::ScopedLock lock(m_mutex);
        Poco::JSON::Array::Ptr newArr;
        if (m_stack.empty())
        {
            Poco::JSON::Parser parser;
            newArr = parser.parse(m_httpRequest.stream()).extract<Poco::JSON::Array::Ptr>();
        }
        else
        {
            Poco::Dynamic::Var parent = m_stack.top().first;
            if (parent.type() == typeid(Poco::JSON::Array::Ptr))
            {
                Poco::JSON::Array::Ptr arr = parent.extract<Poco::JSON::Array::Ptr>();
                newArr = arr->getArray(m_stack.top().second++);
            }
            else if (parent.type() == typeid(Poco::JSON::Object::Ptr))
            {
                Poco::JSON::Object::Ptr obj = parent.extract<Poco::JSON::Object::Ptr>();
                newArr = obj->getArray(name);
            }
        }
        poco_check_ptr(newArr);
        m_stack.emplace(std::move(newArr), 0);
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

void HTTPRequestDeserializer::deserializeSequenceEnd(const std::string& name)
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

bool HTTPRequestDeserializer::deserializeNullableBegin(const std::string& name, bool isMandatory, bool& isNull)
{
    ///@todo support
    throw Poco::NotImplementedException("nullable are not supported");
}

void HTTPRequestDeserializer::deserializeNullableEnd(const std::string& name)
{
    ///@todo support
    throw Poco::NotImplementedException("nullable are not supported");
}

bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, Int8& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return deserialize<Int8>(name, isMandatory, value);
}

bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, UInt8& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return deserialize<UInt8>(name, isMandatory, value);
}

bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, Int16& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return deserialize<Int16>(name, isMandatory, value);
}

bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, UInt16& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return deserialize<UInt16>(name, isMandatory, value);
}

bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, Int32& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return deserialize<Int32>(name, isMandatory, value);
}

bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, UInt32& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return deserialize<UInt32>(name, isMandatory, value);
}

bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, long& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return deserialize<long>(name, isMandatory, value);
}

bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, unsigned long& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return deserialize<unsigned long>(name, isMandatory, value);
}

#ifndef POCO_INT64_IS_LONG
bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, Int64& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return deserialize<Int64>(name, isMandatory, value);
}

bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, UInt64& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return deserialize<UInt64>(name, isMandatory, value);
}
#endif

bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, float& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return deserialize<float>(name, isMandatory, value);
}

bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, double& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return deserialize<double>(name, isMandatory, value);
}

bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, bool& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return deserialize<bool>(name, isMandatory, value);
}

bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, char& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return deserialize<char>(name, isMandatory, value);
}

bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, std::string& value)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    return deserialize<std::string>(name, isMandatory, value);
}

bool HTTPRequestDeserializer::deserialize(const std::string& name, bool isMandatory, std::vector<char>& value)
{
    /// @todo support
    throw Poco::NotImplementedException("vector<char> are not supported");
}

void HTTPRequestDeserializer::setupImpl(std::istream& inStream) {}

void HTTPRequestDeserializer::resetImpl() {}
}  // namespace REST
}  // namespace RemotingNG
}  // namespace Poco