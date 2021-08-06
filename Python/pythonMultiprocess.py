from multiprocessing import Process
import os
import time


def myFunction(name):
    time.sleep(1)
    print('hello', name)


if __name__ == '__main__':

    processList = []

    for i in range(0,4):
        print("started ",i)
        p = Process(target=myFunction, args=(i,))
        p.start()
        processList.append(p)
    
    print("Waiting to join...")
    for p in processList:
        p.join()

