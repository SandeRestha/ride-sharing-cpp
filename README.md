# Ride Sharing System (C++)

This repository contains a simple Ride Sharing System implemented in C++. It serves as a practical demonstration of fundamental Object-Oriented Programming (OOP) principles, including encapsulation, inheritance, and polymorphism.

## Features

* **Classes**:
    * `Ride`: An abstract base class defining common ride attributes and behaviors.
    * `StandardRide`: Derived from `Ride`, implementing standard fare calculation.
    * `PremiumRide`: Derived from `Ride`, implementing premium fare calculation.
    * `Driver`: Manages driver details (ID, name, rating) and tracks assigned rides.
    * `Rider`: Manages rider details (ID, name) and tracks requested rides.
* **Core Functionality**: Simulates the process of creating rides, riders requesting rides, drivers being assigned rides, and viewing ride details and history.
* **Demonstration**: The `main()` function provides a complete walkthrough of the system's capabilities.

## How to Compile and Run

To compile and run this C++ project, you will need a C++ compiler (like g++ or clang++).

1.  **Clone the Repository**:
    ```bash
    git clone [YOUR_REPO_URL_HERE]
    cd [YOUR_REPO_NAME_HERE]
    ```
2.  **Compile the Code**:
    Assuming your source code is primarily in `main.cpp` (and any other `.h`/`.cpp` files), you can compile it using a C++ compiler.
    ```bash
    g++ main.cpp -o ride_sharing_system -std=c++11
    # Or for more complex projects with multiple files:
    # g++ *.cpp -o ride_sharing_system -std=c++11
    ```
    * `g++`: The C++ compiler command.
    * `main.cpp`: Your primary source file (adjust if you have multiple source files).
    * `-o ride_sharing_system`: Specifies the output executable file name.
    * `-std=c++11`: Specifies the C++ standard to use (can be `c++14`, `c++17`, `c++20` depending on features used).

3.  **Run the Executable**:
    ```bash
    ./ride_sharing_system
    ```
    The output of the system demonstration will be printed to your console.

## Project Structure (Key Files)

* `main.cpp`: Contains the main demonstration logic and potentially class definitions.
    * *(Add other .h/.cpp files here if you have them, e.g., `Ride.h`, `Ride.cpp`, `Driver.h`, `Driver.cpp`, etc.)*
