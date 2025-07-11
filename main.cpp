// C++ Implementation

#include <iostream>
#include <vector>
#include <string>
#include <memory> // For std::unique_ptr
#include <iomanip> // For std::fixed and std::setprecision

// 1. Ride Class (Base Class)
class Ride {
protected:
    std::string rideID;
    std::string pickupLocation;
    std::string dropoffLocation;
    double distance; // in miles
    double fare;

public:
    Ride(const std::string& id, const std::string& pickup, const std::string& dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist), fare(0.0) {}

    // Virtual destructor: Essential for correct polymorphic deletion
    // Ensures that derived class destructors are called when
    // a base class pointer (like unique_ptr<Ride>) deletes a derived object.
    virtual ~Ride() {
        // Optional: Add debug messages here if needed for tracking object destruction.
        // For example: std::cout << "Ride destructor called for ID: " << rideID << std::endl;
    }

    // Virtual method for fare calculation - demonstrates polymorphism
    virtual void calculateFare() = 0; // Pure virtual function, makes Ride an abstract class

    // Method to display ride information
    void rideDetails() const {
        std::cout << "Ride ID: " << rideID << std::endl;
        std::cout << "  Pickup: " << pickupLocation << std::endl;
        std::cout << "  Dropoff: " << dropoffLocation << std::endl;
        std::cout << "  Distance: " << std::fixed << std::setprecision(1) << distance << " miles" << std::endl;
        std::cout << "  Fare: $" << std::fixed << std::setprecision(2) << fare << std::endl;
    }

    double getFare() const {
        return fare;
    }

    std::string getRideID() const {
        return rideID;
    }
};

// 2. StandardRide subclass
class StandardRide : public Ride {
private:
    static constexpr double RATE_PER_MILE = 2.0; // Example rate

public:
    StandardRide(const std::string& id, const std::string& pickup, const std::string& dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {
        calculateFare(); // Calculate fare upon construction
    }

    // Override calculateFare method
    void calculateFare() override {
        fare = distance * RATE_PER_MILE;
    }
    // No explicit destructor needed here unless it manages its own unique resources.
    // The base class virtual destructor handles proper destruction.
};

// 3. PremiumRide subclass
class PremiumRide : public Ride {
private:
    static constexpr double RATE_PER_MILE = 3.5; // Example premium rate
    static constexpr double PREMIUM_SURCHARGE = 5.0; // Additional flat fee

public:
    PremiumRide(const std::string& id, const std::string& pickup, const std::string& dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {
        calculateFare(); // Calculate fare upon construction
    }

    // Override calculateFare method
    void calculateFare() override {
        fare = (distance * RATE_PER_MILE) + PREMIUM_SURCHARGE;
    }
};

// 4. Driver Class
class Driver {
private:
    std::string driverID;
    std::string name;
    double rating;
    std::vector<std::unique_ptr<Ride>> assignedRides; // Encapsulated: private access

public:
    Driver(const std::string& id, const std::string& n, double r)
        : driverID(id), name(n), rating(r) {}

    // Method to add rides to the driver's list
    // Takes ownership of the unique_ptr
    void addRide(std::unique_ptr<Ride> ride) {
        assignedRides.push_back(std::move(ride)); // Ownership transferred
    }

    // Method to display driver details
    void getDriverInfo() const {
        std::cout << "\n--- Driver Details ---" << std::endl;
        std::cout << "Driver ID: " << driverID << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Rating: " << std::fixed << std::setprecision(1) << rating << "/5.0" << std::endl;
        std::cout << "Completed Rides (" << assignedRides.size() << "):" << std::endl;
        if (assignedRides.empty()) {
            std::cout << "  No rides completed yet." << std::endl;
        } else {
            for (const auto& ride : assignedRides) {
                // Polymorphic call: correct rideDetails (from Standard or Premium) is invoked
                ride->rideDetails();
                std::cout << "--------------------" << std::endl;
            }
        }
    }
};

// 5. Rider Class
class Rider {
private:
    std::string riderID;
    std::string name;
    std::vector<std::unique_ptr<Ride>> requestedRides; // Using unique_ptr for ownership

public:
    Rider(const std::string& id, const std::string& n)
        : riderID(id), name(n) {}

    // Method to request a ride
    // Takes ownership of the unique_ptr
    void requestRide(std::unique_ptr<Ride> ride) {
        std::cout << "\n" << name << " requested a ride." << std::endl;
        ride->rideDetails(); // Show requested ride details
        requestedRides.push_back(std::move(ride)); // Ownership transferred
    }

    // Method to display ride history
    void viewRides() const {
        std::cout << "\n--- " << name << "'s Ride History ---" << std::endl;
        if (requestedRides.empty()) {
            std::cout << "  No rides requested yet." << std::endl;
        } else {
            for (const auto& ride : requestedRides) {
                // Polymorphic call: correct rideDetails is invoked
                ride->rideDetails();
                std::cout << "--------------------" << std::endl;
            }
        }
    }
};

// 6. System Functionality (Demonstrates Polymorphism)
void demonstrateSystemFunctionality() {
    std::cout << "--- C++ Ride Sharing System Demonstration ---" << std::endl;

    // Create a Rider
    Rider sandesh("R001", "Sandesh Shrestha");

    // Create some rides using std::make_unique for automatic memory management and clear ownership
    // std::make_unique correctly constructs the object and wraps it in a unique_ptr
    std::unique_ptr<Ride> ride1 = std::make_unique<StandardRide>("S001", "Downtown", "Suburb A", 10.5);
    std::unique_ptr<Ride> ride2 = std::make_unique<PremiumRide>("P002", "Airport", "City Center", 25.0);
    std::unique_ptr<Ride> ride3 = std::make_unique<StandardRide>("S003", "Park", "Museum", 3.2);

    // Rider requests rides - ownership is moved from the temporary unique_ptr to the rider's vector
    sandesh.requestRide(std::move(ride1));
    sandesh.requestRide(std::move(ride2));
    sandesh.requestRide(std::move(ride3));

    // Create a Driver
    Driver alice("D001", "Alice Smith", 4.8);

    // Simulate assigning rides to a driver
    // In a real system, you'd manage ride assignment more dynamically,
    // potentially passing shared_ptrs or raw pointers if appropriate.
    // For this simple demo, new unique_ptrs are created to represent "completed" rides
    // for the driver, as the original ones are now owned by `sandesh.requestedRides`.
    std::unique_ptr<Ride> completedRide1_driver = std::make_unique<StandardRide>("S001-C", "Downtown", "Suburb A", 10.5);
    std::unique_ptr<Ride> completedRide2_driver = std::make_unique<PremiumRide>("P002-C", "Airport", "City Center", 25.0);
    std::unique_ptr<Ride> completedRide3_driver = std::make_unique<StandardRide>("S003-C", "Park", "Museum", 3.2);

    alice.addRide(std::move(completedRide1_driver));
    alice.addRide(std::move(completedRide2_driver));
    alice.addRide(std::move(completedRide3_driver));


    // View driver information
    alice.getDriverInfo();

    // View rider's ride history
    sandesh.viewRides();

    // Demonstrate polymorphism by storing different ride types in a generic collection
    std::cout << "\n--- Polymorphism Demonstration (List of All Rides in System) ---" << std::endl;
    std::vector<std::unique_ptr<Ride>> systemRides;
    systemRides.push_back(std::make_unique<StandardRide>("SysR01", "Library", "Cafe", 7.0));
    systemRides.push_back(std::make_unique<PremiumRide>("SysR02", "Mall", "Home", 4.5));
    systemRides.push_back(std::make_unique<StandardRide>("SysR03", "Gym", "Cafe", 2.0));
    systemRides.push_back(std::make_unique<PremiumRide>("SysR04", "School", "Park", 12.0));


    for (const auto& ride : systemRides) {
        // Even though 'ride' is a unique_ptr<Ride> (base class pointer),
        // the virtual functions `calculateFare()` and `rideDetails()`
        // correctly invoke the overridden methods in the derived classes
        // (StandardRide or PremiumRide) at runtime.
        ride->calculateFare();
        ride->rideDetails();
        std::cout << "--------------------" << std::endl;
    }

    std::cout << "\n--- Demonstration Complete ---" << std::endl;
}

int main() {
    demonstrateSystemFunctionality();
    return 0;
}