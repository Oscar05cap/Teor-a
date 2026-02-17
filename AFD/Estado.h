#ifndef ESTADO_H
#define ESTADO_H

#include <string>

class Estado 
{
private:
    std::string id;

public:
    Estado() = default;
    explicit Estado(const std::string& id) : id(id) {}

    const std::string& getId() const{
        return id;
    }

    bool operator==(const Estado& other) const{
        return id == other.id;
    }
};

namespace std{
    template<>
    struct hash<Estado> {
        size_t operator()(const Estado& e) const noexcept{
            return hash<std::string>()(e.getId());
        }
    };
}

#endif
