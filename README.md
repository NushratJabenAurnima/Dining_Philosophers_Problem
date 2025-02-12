# 📌 **Dining Philosophers Problem**
A multi-threaded simulation of the **Dining Philosophers Problem** using **POSIX threads and semaphores** to ensure proper synchronization and avoid deadlock. This implementation handles an **odd number of philosophers**, preventing resource starvation and maintaining fairness.

---

## 🚀 **Project Overview**
The **Dining Philosophers Problem** illustrates the challenges of resource allocation among multiple concurrent processes. Each philosopher alternates between **thinking** and **eating** but requires two forks to eat. The challenge is to design a synchronization mechanism that prevents **deadlock** and ensures that all philosophers get a chance to eat.

This program uses:
- **Semaphores** for resource allocation.
- **POSIX threads** for concurrency.
- **Randomized eating behavior** to simulate real-world scheduling.

---

## 🔹 **Key Features**
- **✅ Philosopher States** – Each philosopher transitions between **thinking, hungry, and eating**.
- **✅ Deadlock Prevention** – The program ensures an **odd number of philosophers** to minimize circular wait conditions.
- **✅ Randomized Eating Time** – Simulates unpredictable eating durations.
- **✅ Semaphore-Based Synchronization** – Prevents race conditions.
- **✅ Dynamic Input Handling** – Accepts **user-defined** (odd) number of philosophers.

---

## 📜 **Functionality**
### **1️⃣ Philosopher Lifecycle**
Each philosopher follows this sequence:
1. **Thinking** – The philosopher spends some time thinking.
2. **Hungry** – The philosopher tries to acquire two forks.
3. **Eating** – If both forks are available, the philosopher eats for a random duration.
4. **Releasing Forks** – Once done, the philosopher puts the forks down.

### **2️⃣ Deadlock Avoidance**
- The number of philosophers is restricted to **odd values** to minimize circular wait conditions.
- A **probabilistic mechanism** ensures forks are not held indefinitely.

### **3️⃣ Semaphore Usage**
- **Mutex Semaphore (`mutex`)** – Ensures mutual exclusion during critical operations.
- **Array of Semaphores (`s[i]`)** – Controls access to forks for each philosopher.

---

## 🏛 **Code Structure**
### 📌 **Core Functions**
- **`philosopher(void* arg)`** – Controls each philosopher’s behavior.
- **`take_forks(int i)`** – Attempts to pick up forks.
- **`put_forks(int i)`** – Releases forks with a fairness check.
- **`test(int i)`** – Checks if a philosopher can eat.
- **`main()`** – Initializes the system, creates philosopher threads, and cleans up resources.

### 📌 **Synchronization Mechanisms**
- **Mutex Lock (`sem_wait` and `sem_post`)** – Prevents race conditions.
- **Randomized Fork Release** – Ensures a philosopher does not hold onto forks indefinitely.

---

## 📖 **Usage Guide**
### 📌 **Compiling the Program**
Use `gcc` to compile the program:
```sh
gcc -pthread -o dining_philosophers p2.c
```

### 📌 **Running the Program**
Execute the program and provide an **odd number** of philosophers:
```sh
./dining_philosophers
```
**Example Output:**
```
Enter the number of philosophers: 5
Philosopher 1 is thinking.
Philosopher 2 is thinking.
Philosopher 3 is thinking.
Philosopher 4 is thinking.
Philosopher 5 is thinking.
Philosopher 3 is eating.
Philosopher 1 is eating.
Philosopher 5 is hungry.
...
```

---


## 🛠 **Technologies Used**
- **🔹 Programming Language:** C
- **🔹 Libraries:** `pthread.h`, `semaphore.h`, `unistd.h`
- **🔹 Synchronization:** Semaphores, Mutex

---

## ⚠️ **Limitations and Considerations**
- Only **odd numbers** of philosophers are allowed for optimal synchronization.
- Philosophers eat for a **random duration**, preventing indefinite holding of forks.
- No starvation is ensured, but delays can still occur based on execution order.
