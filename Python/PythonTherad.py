import threading

# Define a function for the thread
def threadRun( threadName):
    print("%s" % ( threadName ))

# Create two threads as follows
try:
   x = threading.Thread(target=threadRun, args=("MyThread",))
   x.start()
except:
   print("Error: unable to start thread")


