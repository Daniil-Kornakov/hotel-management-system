#include "service.hpp"
#include "service_order.hpp"

#include <iostream>
#include <limits>

namespace hotel
{

    Service::Service(const std::string& name,
        const std::string& unit,
        int price)
        : m_name{ name }
        , m_unit{ unit }
        , m_price{ price }
    {
        if (m_price < 0)
        {
            std::cout << "Ошибка: цена не может быть отрицательной. "
                << "Установлена цена 0.\n";
            m_price = 0;
        }

        std::cout << "Создана услуга: " << m_name << '\n';
    }

    Service::~Service()
    {
        std::cout << "Уничтожена услуга: " << m_name << '\n';
    }

    int Service::CalculateCost(int quantity) const
    {
        if (quantity <= 0)
        {
            std::cout << "Ошибка: количество должно быть положительным.\n";
            return -1;
        }

        if (m_price > std::numeric_limits<int>::max() / quantity)
        {
            std::cout << "Ошибка: слишком большая стоимость.\n";
            return -1;
        }

        return m_price * quantity;
    }

    const std::string& Service::GetName() const
    {
        return m_name;
    }

    const std::string& Service::GetUnit() const
    {
        return m_unit;
    }

    int Service::GetPrice() const
    {
        return m_price;
    }

    void Service::PrintInfo() const
    {
        std::cout << "Услуга: " << m_name
            << ", единица учёта: " << m_unit
            << ", цена: " << m_price << " руб.\n";
    }

    ServiceOrder* Service::CreateOrder(int quantity) const
    {
        if (CalculateCost(quantity) < 0)
        {
            return nullptr;
        }

        return new ServiceOrder(*this, quantity);
    }

} // namespace hotel