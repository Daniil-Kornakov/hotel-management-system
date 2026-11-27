#include "service_order.hpp"
#include "service.hpp"

#include <iostream>
#include <limits>

namespace hotel
{

    ServiceOrder::ServiceOrder(const Service& service, int quantity)
        : m_service{ &service }
        , m_quantity{ 1 }
        , m_unitPrice{ service.GetPrice() }
    {
        if (service.CalculateCost(quantity) >= 0)
        {
            m_quantity = quantity;
        }
        else
        {
            std::cout << "В заказе установлено количество 1.\n";
        }

        std::cout << "Создан заказ услуги: "
            << m_service->GetName() << '\n';
    }

    ServiceOrder::~ServiceOrder()
    {
        std::cout << "Уничтожен заказ услуги: "
            << m_service->GetName() << '\n';
    }

    bool ServiceOrder::AddQuantity(int quantity)
    {
        if (quantity <= 0)
        {
            std::cout << "Ошибка: добавляемое количество должно быть положительным.\n";
            return false;
        }

        const int maxValue = std::numeric_limits<int>::max();

        if (quantity > maxValue - m_quantity)
        {
            std::cout << "Ошибка: слишком большое количество.\n";
            return false;
        }

        const int newQuantity = m_quantity + quantity;

        if (m_unitPrice > maxValue / newQuantity)
        {
            std::cout << "Ошибка: слишком большая стоимость.\n";
            return false;
        }

        m_quantity = newQuantity;
        return true;
    }

    int ServiceOrder::CalculateCost() const
    {
        return m_unitPrice * m_quantity;
    }

    void ServiceOrder::PrintInfo() const
    {
        std::cout << "Заказ: " << m_service->GetName()
            << ", количество: " << m_quantity
            << ", единица учёта: " << m_service->GetUnit()
            << ", цена единицы: " << m_unitPrice
            << " руб., стоимость: " << CalculateCost()
            << " руб.\n";
    }

} // namespace hotel