#pragma once

#include "service.hpp"

namespace hotel
{

    class ServiceOrder
    {
    private:
        const Service* m_service;
        int m_quantity;
        int m_unitPrice;

    public:
        ServiceOrder(const Service& service, int quantity);
        ~ServiceOrder();

        bool AddQuantity(int quantity);
        int CalculateCost() const;

        void PrintInfo() const;
    };

} // namespace hotel