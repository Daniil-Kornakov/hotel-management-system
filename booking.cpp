#include "booking.hpp"

#include <iostream>
#include <limits>

namespace hotel
{

    Booking::Booking(int id, bool isluxuryroom)
        : m_id{ id }
        , m_isluxuryroom{ isluxuryroom }
        , m_status{ Status::eConfirmed }
    {
        std::cout << "Создано бронирование N " << m_id << '\n';
    }

    Booking::~Booking()
    {
        std::cout << "Уничтожается бронирование N " << m_id << '\n';

        for (ServiceOrder*& order : m_orders)
        {
            delete order;
            order = nullptr;
        }
    }

    bool Booking::StartStay()
    {
        if (m_status != Status::eConfirmed)
        {
            std::cout << "Ошибка: начать проживание можно только "
                << "по подтверждённому бронированию.\n";
            return false;
        }

        m_status = Status::eStaying;

        std::cout << "Начато проживание по бронированию N "
            << m_id << '\n';

        return true;
    }

    bool Booking::FinishStay()
    {
        if (m_status != Status::eStaying)
        {
            std::cout << "Ошибка: завершить можно только "
                << "начатое проживание.\n";
            return false;
        }

        m_status = Status::eCompleted;

        std::cout << "Завершено проживание по бронированию N "
            << m_id << '\n';

        return true;
    }

    bool Booking::Cancel()
    {
        if (m_status != Status::eConfirmed)
        {
            std::cout << "Ошибка: отменить можно только "
                << "подтверждённое бронирование.\n";
            return false;
        }

        m_status = Status::eCancelled;

        std::cout << "Отменено бронирование N " << m_id << '\n';

        return true;
    }

    int Booking::CalculateServicesCost() const
    {
        int total = 0;

        for (const ServiceOrder* order : m_orders)
        {
            total += order->CalculateCost();
        }

        return total;
    }

    void Booking::PrintInfo() const
    {
        std::cout << "\nБронирование N " << m_id << '\n';

        std::cout << "Категория номера: "
            << (m_isluxuryroom ? "люкс" : "стандарт")
            << '\n';

        std::cout << "Состояние: ";

        switch (m_status)
        {
        case Status::eConfirmed:
            std::cout << "подтверждено";
            break;

        case Status::eStaying:
            std::cout << "проживание";
            break;

        case Status::eCompleted:
            std::cout << "завершено";
            break;

        case Status::eCancelled:
            std::cout << "отменено";
            break;
        }

        std::cout << '\n';

        if (m_orders.empty())
        {
            std::cout << "Заказанных услуг нет.\n";
        }
        else
        {
            for (const ServiceOrder* order : m_orders)
            {
                order->PrintInfo();
            }
        }

        std::cout << "Общая стоимость услуг: "
            << CalculateServicesCost()
            << " руб.\n";
    }

    bool Booking::AddService(const Service& service, int quantity)
    {
        if (m_status != Status::eStaying)
        {
            std::cout << "Ошибка: услуги можно добавлять только во время проживания.\n";
            return false;
        }

        const int cost = service.CalculateCost(quantity);

        if (cost < 0)
        {
            return false;
        }

        if (m_isluxuryroom &&
            service.GetType() == ServiceType::eBreakfast)
        {
            std::cout << "Завтрак уже включён в стоимость люкса. Платный заказ не оформлен.\n";
            return false;
        }

        const int total = CalculateServicesCost();

        if (cost > std::numeric_limits<int>::max() - total)
        {
            std::cout << "Ошибка: слишком большая общая стоимость услуг.\n";
            return false;
        }

        m_orders.reserve(m_orders.size() + 1);

        ServiceOrder* order = service.CreateOrder(quantity);

        if (order == nullptr)
        {
            return false;
        }

        m_orders.push_back(order);

        std::cout << "Услуга добавлена к бронированию N " << m_id << '\n';

        return true;
    }

} // namespace hotel