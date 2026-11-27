#pragma once

#include <string>

namespace hotel
{

    class ServiceOrder;

    enum class ServiceType
    {
        eOther,
        eBreakfast,
        eParking,
        eLaundry
    };

    class Service
    {
    private:
        std::string m_name;
        std::string m_unit;
        int m_price;
        ServiceType m_type;

    public:
        Service(const std::string& name,
            const std::string& unit,
            int price,
            ServiceType type = ServiceType::eOther);

        ~Service();

        int CalculateCost(int quantity) const;
        ServiceOrder* CreateOrder(int quantity) const;

        const std::string& GetName() const;
        const std::string& GetUnit() const;
        int GetPrice() const;
        ServiceType GetType() const;

        void PrintInfo() const;
    };

} // namespace hotel