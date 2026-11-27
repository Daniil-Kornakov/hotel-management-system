#pragma once

#include "service_order.hpp"

#include <vector>

namespace hotel
{

    class Booking
    {
    public:
        enum class Status
        {
            eConfirmed,
            eStaying,
            eCompleted,
            eCancelled
        };

    private:
        int m_id;
        bool m_isluxuryroom;
        Status m_status;
        std::vector<ServiceOrder*> m_orders;

    public:
        Booking(int id, bool isluxuryroom);
        ~Booking();

        Booking(const Booking&) = delete;
        Booking& operator=(const Booking&) = delete;

        bool StartStay();
        bool FinishStay();
        bool Cancel();

        bool AddService(const Service& service, int quantity);

        int CalculateServicesCost() const;
        void PrintInfo() const;
    };

} // namespace hotel