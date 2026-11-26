#pragma once

#include <string>

namespace hotel
{

    class ServiceOrder;

    class Service
    {
    private:
        std::string m_name;
        std::string m_unit;
        int m_price;

    public:
        Service(const std::string& name,
            const std::string& unit,
            int price);

        ~Service();

        int CalculateCost(int quantity) const;
        ServiceOrder* CreateOrder(int quantity) const;

        const std::string& GetName() const;
        const std::string& GetUnit() const;
        int GetPrice() const;

        void PrintInfo() const;
    };

} // namespace hotel