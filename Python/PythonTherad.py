
import threading
import time


## Without class model

# Define a function for the thread
def threadRun( threadName):
    print("%s" % ( threadName ))
    time.sleep(2.4)
    print("End of threadRun")

# Create two threads as follows
try:
   x = threading.Thread(target=threadRun, args=("MyThread",))
   x.start()
   print("Main Thread processing...")
   x.join()
   print("Main Thread ends")
except:
   print("Error: unable to start thread")


#With class type
#https://www.geeksforgeeks.org/joining-threads-in-python/
