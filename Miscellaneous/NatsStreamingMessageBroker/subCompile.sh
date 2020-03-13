g++ -g subscriber.cpp -o subscriber -std=c++11 -I natslib/include/ -DNATS_HAS_STREAMING -L natslib/lib/ -lnats
