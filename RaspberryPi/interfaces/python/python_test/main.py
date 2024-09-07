import time
from testfile import print_test

if __name__ == "__main__":
  while True:
    print_test()
    print("Hello From the Python Interface.", flush = True)
    time.sleep(1)