# 🚌 Bus Ticket Management System (C++)

The **Bus Ticket Management System** is a terminal-based application written in **C++** as part of a **Data Structures and Algorithms (DSA)** course project. It offers a full-featured simulation of a bus reservation system where users can add buses, book/cancel tickets, update information, and more — all managed via structured data and menu-driven CLI.

---

## 📌 Features

✅ Add and manage multiple buses  
✅ Show available buses and seat layout  
✅ Book tickets with full passenger information  
✅ Search buses by start time  
✅ Update bus or ticket info  
✅ Cancel booked tickets  
✅ Shutdown (remove) a bus  
✅ Display booked ticket details  
✅ Color-coded seat availability using Windows API  
✅ Fully menu-driven UI for ease of use  

---

## 🧠 Concepts Covered

This project demonstrates a strong grasp of **DSA concepts** and **C++ programming**, including:

- **Linked Lists** – Used to store and manage the list of buses dynamically  
- **Vectors** – Used to store booking records efficiently  
- **Pointers and Dynamic Memory Allocation** – For managing nodes in the linked list  
- **File-less Data Persistence (In-Memory)** – Mimics real-time system operations  
- **Object-Oriented Programming (OOP)** – Custom classes for Bus and Booking  
- **Console UI Formatting** – Includes color-coded seat view using `windows.h`  
- **Searching and Updating Records** – Based on user input  
- **Switch Case & Menu Looping** – Clean CLI navigation system  

---

## 📂 Project Structure

```plaintext
Bus_Ticket_Management/
│── Bus_Ticket_Management.cpp    # Main source code
│── README.md                    # Project documentation
```

---

## 🛠️ How to Compile and Run

### 🖥️ Windows (Using g++)

```sh
g++ Bus_Ticket_Management.cpp -o BusTicketApp
BusTicketApp.exe
```

> 💡 Note: The code uses `windows.h` for seat color formatting, so it runs on Windows-based systems.

---

## 🖼️ Sample Menu UI

```
----------------------------   Menu  ---------------------------------
|                1. Add Bus                                          |
|                2. Show Bus Details                                 |
|                3. Search Bus                                       |
|                4. Book Ticket                                      |
|                5. Show Booked Bus Information                      |
|                6. Update Bus Information                           |
|                7. Update Ticket Information                        |
|                8. Shutdown Bus                                     |
|                9. Cancel Booked Ticket                             |
|                10. Exit                                            |
----------------------------------------------------------------------
```

---

## 👨‍💻 Author

**MD. Tanvir Ahmed Akash**  
📧 tanvir0ah0akash@gmail.com  
🌐 [GitHub](https://github.com/Akash-code-0-1) | [LinkedIn](https://www.linkedin.com/in/md-tanvir-ahmed-akash-8ba50b2b9/)

---

## 📝 License

This project is licensed under the **MIT License** – you are free to use, modify, and distribute it for personal or educational purposes.

---

## 🌟 Support

If you found this project helpful or learned something from it, consider leaving a ⭐ on the repository!
