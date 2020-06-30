#include <EventsRegistry/EventsRegistryService.h>

#include <Poco/Data/TypeHandler.h>

namespace Poco
{
namespace Data
{

template<>
class TypeHandler<struct events_registry::Event>
{
public:
    static std::size_t size()
    {
        constexpr std::size_t EventStructureFieldsCount = 4;
        return EventStructureFieldsCount;
    }

    static void bind(
        std::size_t pos, const events_registry::Event& obj, AbstractBinder::Ptr binder, AbstractBinder::Direction dir)
    {
        TypeHandler<std::string>::bind(pos++, obj.name, binder, dir);
        TypeHandler<std::string>::bind(pos++, obj.product, binder, dir);
        TypeHandler<std::string>::bind(pos++, obj.description, binder, dir);
        TypeHandler<std::string>::bind(pos++, obj.category, binder, dir);
    }

    static void prepare(std::size_t pos, const events_registry::Event& obj, AbstractPreparator::Ptr preparator)
    {
        TypeHandler<std::string>::prepare(pos++, obj.name, preparator);
        TypeHandler<std::string>::prepare(pos++, obj.product, preparator);
        TypeHandler<std::string>::prepare(pos++, obj.description, preparator);
        TypeHandler<std::string>::prepare(pos++, obj.category, preparator);
    }

    static void extract(
        std::size_t pos, events_registry::Event& obj, const events_registry::Event& defVal, AbstractExtractor::Ptr ext)
    {
        std::string name;
        std::string product;
        std::string description;
        std::string category;
        TypeHandler<std::string>::extract(pos++, name, defVal.name, ext);
        TypeHandler<std::string>::extract(pos++, product, defVal.product, ext);
        TypeHandler<std::string>::extract(pos++, description, defVal.description, ext);
        TypeHandler<std::string>::extract(pos++, category, defVal.category, ext);
        obj.name = name;
        obj.product = product;
        obj.description = description;
        obj.category = category;
    }
};

}  // namespace Data
}  // namespace Poco