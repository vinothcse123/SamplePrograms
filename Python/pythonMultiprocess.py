from multiprocessing import Process
import os
import time


def myFunction(name):
    time.sleep(1)
    print('hello', name)


if __name__ == '__main__':

    processList = []
    for i in range(0,2):
        print("started ",i)
        p = Process(target=test1038)

        p.start()
        processList.append(p)
    
    print("Waiting to join...")
    for p in processList:
        p.join()
