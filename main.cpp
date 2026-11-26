// Курсовой проект по ООП.
// Студент: Корнаков Д. Р., группа ПИ-53.
#include <iostream>
#include <windows.h>

#include "service.hpp"
#include "service_order.hpp"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "Курсовой проект.\n";
    cout << "Автор: Корнаков Д. Р., ПИ-53\n";
    cout << "Система управления гостиницей\n";

    hotel::Service parking("Парковка", "сутки", 300);

    parking.PrintInfo();

    cout << "Стоимость за 3 суток: "
        << parking.CalculateCost(3) << " руб.\n";

    // Попытка нарушить правило.
    parking.CalculateCost(0);

    hotel::ServiceOrder* order = parking.CreateOrder(3);

    if (order != nullptr)
    {
        order->PrintInfo();

        // Добавляем ещё одни сутки.
        order->AddQuantity(1);
        order->PrintInfo();

        // Некорректное действие: количество не изменится.
        order->AddQuantity(0);
        order->PrintInfo();

        delete order;
        order = nullptr;
    }

    // Услуга существует после уничтожения заказа.
    parking.PrintInfo();

    return 0;
}