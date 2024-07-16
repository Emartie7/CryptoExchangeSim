# CryptoExchangeSim
Terminal-window application that simulates transactions and order books for a crypto-currency exchange.

OS: Ubuntu 22.04  
g++ 11.4.0  
cmake 3.29.3  

1. Build Instructions:  
      In folder checkout location, run the following commands:  
         > cmake -S . -B build  
         > cmake --build build  

2. Run program:  
      Change directories to the build output location  
         > cd build  
      Run the program:  
         > ./MerkleRex 

3. Run unit tests:  
      In same location as (1):  
         > cmake -S . -B build -DBUILD_GTEST=ON  
         > cmake --build build   
         > ./build/MerkleRex_Test  

