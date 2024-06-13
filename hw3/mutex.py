import threading
import time

class BankAccount:
    def __init__(self, initial_balance):
        self.balance = initial_balance
        self.mutex = threading.Lock()

    def withdraw(self, amount):
        with self.mutex:
            if amount > self.balance:
                raise ValueError("Insufficient funds")
            self.balance -= amount
            return self.balance

    def deposit(self, amount):
        with self.mutex:
            self.balance += amount
            return self.balance

account = BankAccount(1000)  # Initial balance of $1000

def perform_transactions():
    # Simulate multiple concurrent withdrawals and deposits
    for _ in range(100):
        amount = random.randint(1, 100)
        transaction_type = random.choice(["withdraw", "deposit"])

        if transaction_type == "withdraw":
            try:
                with account.mutex:  # Acquire mutex before accessing balance
                    balance = account.withdraw(amount)
                    print(f"Withdrawal: ${amount}, Remaining balance: ${balance}")
            except ValueError:
                print("Withdrawal failed: Insufficient funds")

        else:
            with account.mutex:  # Acquire mutex before accessing balance
                balance = account.deposit(amount)
                print(f"Deposit: ${amount}, Remaining balance: ${balance}")

        # Verify balance consistency
        expected_balance = account.initial_balance + sum(transactions)
        if expected_balance != balance:
            print("** Error: Balance inconsistency! **")
            print(f"Expected balance: ${expected_balance}, Actual balance: ${balance}")

transactions = []  # Track transactions for balance verification

start_time = time.time()

# Create and start multiple threads
threads = []
for _ in range(10):
    thread = threading.Thread(target=perform_transactions)
    threads.append(thread)
    thread.start()

# Wait for all threads to finish
for thread in threads:
    thread.join()

end_time = time.time()
print(f"Total execution time: {end_time - start_time:.2f} seconds")

