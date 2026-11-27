#include "booking.hpp"
#include "service.hpp"

#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "Лабораторная работа N 2\n";
    std::cout << "Система управления гостиницей\n";

    hotel::Service parking(
        "Парковка", "сутки", 300,
        hotel::ServiceType::eParking);

    hotel::Service breakfast(
        "Завтрак", "порция", 500,
        hotel::ServiceType::eBreakfast);

    std::cout << "\nОсновной сценарий:\n";

    {
        hotel::Booking booking(1, true);

        booking.PrintInfo();

        booking.StartStay();
        booking.AddService(parking, 3);

        // Проверки правил: оба действия будут отклонены.
        booking.AddService(parking, 0);
        booking.AddService(breakfast, 1);

        booking.FinishStay();
        booking.PrintInfo();
    }

    std::cout << "\nБронирование и его заказ уничтожены."
        << "\nУслуга продолжает существовать:\n";

    parking.PrintInfo();

    std::cout << "\nРабота по ссылке:\n";

    hotel::Service& serviceRef = parking;
    serviceRef.PrintInfo();

    std::cout << "\nРабота по указателю:\n";

    const hotel::Service* servicePtr = &parking;
    servicePtr->PrintInfo();

    std::cout << "\nДинамический объект:\n";

    hotel::Service* laundry = new hotel::Service(
        "Стирка", "вещь", 200,
        hotel::ServiceType::eLaundry);

    laundry->PrintInfo();

    delete laundry;
    laundry = nullptr;

    std::cout << "\nДинамический массив объектов:\n";

    hotel::Service* services = new hotel::Service[2]
    {
        hotel::Service(
            "Парковка", "сутки", 300,
            hotel::ServiceType::eParking),

        hotel::Service(
            "Стирка", "вещь", 200,
            hotel::ServiceType::eLaundry)
    };

    for (int i = 0; i < 2; ++i)
    {
        services[i].PrintInfo();
    }

    delete[] services;
    services = nullptr;

    std::cout << "\nМассив динамических объектов:\n";

    hotel::Service** servicePointers =
        new hotel::Service * [2] {};

    servicePointers[0] = new hotel::Service(
        "Парковка", "сутки", 300,
        hotel::ServiceType::eParking);

    servicePointers[1] = new hotel::Service(
        "Стирка", "вещь", 200,
        hotel::ServiceType::eLaundry);

    for (int i = 0; i < 2; ++i)
    {
        servicePointers[i]->PrintInfo();
    }

    for (int i = 0; i < 2; ++i)
    {
        delete servicePointers[i];
        servicePointers[i] = nullptr;
    }

    delete[] servicePointers;
    servicePointers = nullptr;

    std::cout << "\nКонец демонстрации."
        << "\nУничтожаются оставшиеся локальные услуги:\n";

    return 0;
}